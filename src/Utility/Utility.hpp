#pragma once

#include "MergeMapperPluginAPI.h"
#include "Utility/LogInfo.hpp"
#include "Utility/Types/Types.hpp"

namespace flm
{
	/**
	 * \brief Returns a poniter to Form based on mod name and record FromID.
	 * \param pluginName    - Name of the mod with extension.
	 * \param rawFormId     - FormID of the record.
	 * \return              - Form (TESForm) pointer or nullptr if not found.
	 */
	inline RE::TESForm* GetTesForm(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		static const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm(rawFormId, pluginName) : nullptr;
	}

	/**
	 * \brief Returns a poniter to Plugin based on its name.
	 * \param pluginName    - Name of the plugin with extension.
	 * \return              - TESFile pointer or nullptr if not found.
	 */
	inline const RE::TESFile* GetTesFile(const std::string_view& pluginName)
	{
		static const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupModByName(pluginName) : nullptr;
	}

	/**
	 * \brief Returns a poniter to Form based on string.
	 * \param string        - String in the format RecordID~ModName or EditorID.
	 * The mod name must have extension. ~ and ModName can be omitted for base game plugins. RecordID can have a maximum of 8 characters.
	 * \return              - FormList pointer or nullptr if not found.
	 */
	template<typename T = RE::TESForm>
	inline T* FindForm(const std::string& string)
	{
		if(string.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(string, "~");
			auto [plugin, form_id_str] = std::make_pair(split_id.at(1), split_id.at(0));
			if(form_id_str.size() == 10)
				form_id_str.erase(2, 2);
			auto form_id = string::lexical_cast<RE::FormID>(form_id_str, true);

			if(g_mergeMapperInterface)
			{
				const auto [fst, snd] = g_mergeMapperInterface->GetNewFormID(plugin.c_str(), form_id);
				plugin = std::string(fst);
				form_id = snd;
			}

			if(const auto f = GetTesForm(plugin, form_id))
				return f->As<T>();
			else
			{
				if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
					log::Error("Can't find Form with FormID {:X} from plugin {}.", form_id, plugin);
				return nullptr;
			}
		}
		else if(string.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID(string::lexical_cast<RE::FormID>(string, true)))
				return f->As<T>();
			else
			{
				if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
					log::Error("Can't find Form with FormID {}.", string);
				return nullptr;
			}
		if(const auto f = RE::TESForm::LookupByEditorID(string))
			return f->As<T>();

		if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
			log::Error("Can't find Form with EditorID {}.", string);
		return nullptr;
	}

	/**
	 * \brief Removes spaces between | , and leading zeros from string. From https://github.com/powerof3/Spell-Perk-Item-Distributor.
	 * \param string        - String to parse.
	 * \return              - Sanitized string.
	 */
	inline std::string Sanitize(const std::string& string)
	{
		std::string sanitized = string;

		// strip spaces between " | "
		static const boost::regex re_bar(R"(\s*\|\s*)", boost::regex_constants::optimize);
		sanitized = regex_replace(sanitized, re_bar, "|");

		// strip spaces between " , "
		static const boost::regex re_comma(R"(\s*,\s*)", boost::regex_constants::optimize);
		sanitized = regex_replace(sanitized, re_comma, ",");

		// strip leading zeros
		static const boost::regex re_zeros(R"((0x00+)([0-9a-fA-F]+))", boost::regex_constants::optimize);
		sanitized = regex_replace(sanitized, re_zeros, "0x$2");

		// swap dawnguard and dragonborn forms
		// VR apparently does not load masters in order so the lookup fails
		static const boost::regex re_dawnguard(R"((0x0*2)([0-9a-f]{6}))", static_cast<int>(boost::regex_constants::optimize) | static_cast<int>(boost::regex::icase));
		sanitized = regex_replace(sanitized, re_dawnguard, "0x$2~Dawnguard.esm");

		static const boost::regex re_dragonborn(R"((0x0*4)([0-9a-f]{6}))", static_cast<int>(boost::regex_constants::optimize) | static_cast<int>(boost::regex::icase));
		sanitized = regex_replace(sanitized, re_dragonborn, "0x$2~Dragonborn.esm");

		return sanitized;
	}

	/**
	 * \brief Removes spaces between & and , for Filters.
	 * \param string        - Filter to parse.
	 * \return              - Sanitized Filter.
	 */
	inline std::string SanitizeFilter(const std::string& string)
	{
		std::string sanitized = string;

		// strip spaces between " & "
		static const boost::regex re_bar(R"(\s*\&\s*)", boost::regex_constants::optimize);
		sanitized = regex_replace(sanitized, re_bar, "&");

		// strip spaces between " , "
		static const boost::regex re_comma(R"(\s*,\s*)", boost::regex_constants::optimize);
		sanitized = regex_replace(sanitized, re_comma, ",");
		return sanitized;
	}

	/**
	 * \brief Change string to make all characters lowercase.
	 * \param string        - String to change.
	 */
	inline void ToLower(std::string& string)
	{
		std::ranges::transform(string, string.begin(), [](const unsigned char c)
							   { return std::tolower(c); });
	}

	/**
	 * \brief Check if string contains non alpha character.
	 * \param string        - String to check.
	 * \return              - True, if string contains at least one non alpha character.
	 */
	inline bool ContainsNonAlpha(const std::string& string)
	{
		return std::ranges::find_if(string, [](char c)
									{ return !std::isalpha(c); }) != string.end();
	}

	/**
	 * \brief Adds correct generic entries with forms to the game.
	 * \param data              - A map containing FromLists with their corresponding Forms.
	 */
	inline std::pair<int, int> AddGeneric(FormListsData& data)
	{
		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::Header("FORMLISTS"sv);
			log::indent_level++;
		}

		int total_duplicates = 0;
		int total_added = 0;

		for(auto& [form_list, forms] : data)
		{
			int duplicates = 0;
			int added = 0;
			RE::BGSListForm* fl = form_list;
			if(log::operating_mode == OperatingMode::INITIALIZE)
			{
				log::Info("FormList {} \"{}\" [{:X}]", GetEditorId(fl), fl->GetName(), fl->formID);
				log::indent_level++;
			}

			for(const auto& f : forms)
			{
				if(fl->HasForm(f))
				{
					if(log::operating_mode == OperatingMode::INITIALIZE && log::debug_mode)
						log::DuplicateWarn("Form"sv, f);
					duplicates++;
					continue;
				}
				else
				{
					fl->AddForm(f);
					added++;
					if(log::debug_mode && log::operating_mode == OperatingMode::INITIALIZE)
						log::Added("Form", f);
				}
			}

			if(log::operating_mode == OperatingMode::INITIALIZE)
			{
				log::Info("{} new Forms added, skipped {} duplicates.", added, duplicates);
				log::indent_level--;
			}

			total_added += added;
			total_duplicates += duplicates;
		}

		if(log::operating_mode == OperatingMode::INITIALIZE)
		{
			log::indent_level--;
			log::Info("Total {} new Forms added to {} FormLists, skipped {} duplicates.", total_added, data.size(), total_duplicates);
			log::Header();
		}

		return std::make_pair(total_added, total_duplicates);
	}

	/**
	 * \brief Evaluate Filter.
	 * \param filter                    - Filter to evaluate in format: +/-ESP[&+-ESP], +/-ESP[&+-ESP], itd.
	 * \return                          - 1, if Filter meet criteria, 0 if invalid, -1 if did not meet criteria.
	 */
	inline int EvaluateFilter(const std::string& filter)
	{
		const auto conditions_sections = string::split(filter, ",");

		for(auto& cs : conditions_sections)
		{
			const auto plugins = string::split(cs, "&");
			bool result = true;
			for(auto& plugin : plugins)
			{
				if(plugin[0] != '+' && plugin[0] != '-')
				{
					if(log::debug_mode)
						log::Warn("Filter \"{}\" has an invalid format.", filter);
					return 0;
				}
				else
				{
					std::string plugin_name = plugin.substr(1);
					const auto res = GetTesFile(plugin_name);
					if(log::debug_mode)
						log::Info("Plugin {} status {}.", plugin_name, res ? true : false);

					if(!res && plugin[0] == '+' || res && plugin[0] == '-')
					{
						result = false;
						break;
					}
				}
			}
			if(result)
				return 1;
		}

		return -1;
	}
}
