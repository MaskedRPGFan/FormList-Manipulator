#pragma once

#include "LogInfo.hpp"
#include "OperatingMode.hpp"
#include "MergeMapperPluginAPI.h"

namespace flm
{
	using ParseEntryCallback = std::function<bool(const std::string&)>;          /* Pointer to the function that parses the entry. */
	using FormListsData = std::map<RE::BGSListForm*, std::vector<RE::TESForm*>>; /* Data for mod events. */
	using ModEvents = std::unordered_map<std::string, FormListsData>;            /* Mod events type. */

	/**
	 * \brief Returns a poniter to Form based on mod name and record FromID.
	 * \param pluginName    - Name of the mod with extension.
	 * \param rawFormId     - FormID of the record.
	 * \return              - Form (TESForm) pointer or nullptr if not found.
	 */
	inline RE::TESForm* GetTesForm(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm(rawFormId, pluginName) : nullptr;
	}

	/**
	 * \brief Returns a poniter to Form based on string.
	 * \param string        - String in the format RecordID~ModName or EditorID.
	 * The mod name must have extension. ~ and ModName can be omitted for base game plugins. RecordID can have a maximum of 8 characters.
	 * \param debug         - Debug mode that prints out additional information. Default: disabled.
	 * \return              - FormList pointer or nullptr if not found.
	 */
	template<typename T = RE::TESForm>
	inline T* FindForm(const std::string& string, bool debug = false)
	{
		if(string.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(string, "~");
			auto [plugin, form_id_str] = std::make_pair(split_id.at(1), split_id.at(0));
			if(form_id_str.size() == 10)
				form_id_str.erase(2, 2);
			auto form_id = string::lexical_cast<RE::FormID>(form_id_str, true);
      
			if (g_mergeMapperInterface){
				const auto processedFormPair = g_mergeMapperInterface->GetNewFormID(plugin.c_str(), form_id);
				plugin = std::string(processedFormPair.first);
				form_id = processedFormPair.second;
			}

			if(const auto f = GetTesForm(plugin, form_id))
				return f->As<T>();
			else
			{
				if(debug)
					log::Error("Can't find Form with FormID {:X} from plugin {}.", form_id, plugin);
				return nullptr;
			}
		}
		else if(string.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID(string::lexical_cast<RE::FormID>(string, true)))
				return f->As<T>();
			else
			{
				if(debug)
					log::Error("Can't find Form with FormID {}.", string);
				return nullptr;
			}
		if(const auto f = RE::TESForm::LookupByEditorID(string))
			return f->As<T>();

		if(debug)
			log::Error("Can't find Form with EditorID {}.", string);
		return nullptr;
	}

	/**
	 * \brief Removes spaces between | and leading zeros from string. From https://github.com/powerof3/Spell-Perk-Item-Distributor.
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
	 * \param mode              - Current Operating Mode.
	 * \param debug             - Debug mode that prints out additional information. Default: disabled.
	 */
	inline std::pair<int, int> AddGeneric(FormListsData& data, const OperatingMode::OperatingMode mode, bool debug = false)
	{
		if(mode == OperatingMode::INITIALIZE)
		{
			log::Header("FORMLISTS"sv);
			log::level++;
		}

		int total_duplicates = 0;
		int total_added = 0;

		for(auto& [form_list, forms] : data)
		{
			int duplicates = 0;
			int added = 0;
			RE::BGSListForm* fl = form_list;
			if(mode == OperatingMode::INITIALIZE)
				log::Info("FormList \"{}\" [{:X}]", fl->GetName(), fl->formID);
			log::level++;
			for(const auto& f : forms)
			{
				if(fl->HasForm(f))
				{
					if(mode == OperatingMode::INITIALIZE)
						log::DuplicateWarn("Form"sv, f);
					duplicates++;
					continue;
				}
				else
				{
					fl->AddForm(f);
					added++;
					if(debug)
						log::Added("Form", f);
				}
			}

			if(mode == OperatingMode::INITIALIZE)
			{
				log::Info("{} new Forms added, skipped {} duplicates.", added, duplicates);
				log::level--;
			}

			total_added += added;
			total_duplicates += duplicates;
		}

		if(mode == OperatingMode::INITIALIZE)
		{
			log::level--;
			log::Info("Total {} new Forms added to {} FormLists, skipped {} duplicates.", total_added, data.size(), total_duplicates);
			log::Header();
		}

		return std::make_pair(total_added, total_duplicates);
	}
}
