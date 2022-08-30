#pragma once

namespace flm
{
	/**
	 * \brief Returns a poniter to FormList based on mod name and record FromID.
	 * \param pluginName    - Name of the mod with extension.
	 * \param rawFormId     - FormID of the record.
	 * \return              - FormList pointer or nullptr if not found.
	 */
	inline RE::BGSListForm* GetFormList(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm<RE::BGSListForm>(rawFormId, pluginName) : nullptr;
	}

	/**
	 * \brief Returns a poniter to Form based on mod name and record FromID.
	 * \param pluginName    - Name of the mod with extension.
	 * \param rawFormId     - FormID of the record.
	 * \return              - Form (TESForm) pointer or nullptr if not found.
	 */
	inline RE::TESForm* GetTESForm(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm(rawFormId, pluginName) : nullptr;
	}

	/**
	 * \brief Returns a poniter to FormList based on string.
	 * \param string        - String in the format RecordID~ModName or EditorID.
	 * The mod name must have extension. ~ and ModName can be omitted for base game plugins. RecordID can have a maximum of 8 characters.
	 * \return              - FormList pointer or nullptr if not found.
	 */
	inline RE::BGSListForm* FindFormList(const std::string& string)
	{
		if(string.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(string, "~");
			auto [plugin, form_id_str] = std::make_pair(split_id.at(1), split_id.at(0));
			if(form_id_str.size() == 10)
				form_id_str.erase(2, 2);
			auto form_id = string::lexical_cast<RE::FormID>(form_id_str, true);

			if(const auto f = GetFormList(plugin, form_id))
				return f;
			else
			{
				logger::error("            Can't find FormList with FormID {:X} from plugin {}.", form_id, plugin);
				return nullptr;
			}
		}
		else if(string.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID<RE::BGSListForm>(string::lexical_cast<RE::FormID>(string, true)))
				return f;

		return RE::TESForm::LookupByEditorID<RE::BGSListForm>(string);
	}

	/**
	 * \brief Returns a poniter to Form based on string.
	 * \param string        - String in the format RecordID~ModName or EditorID.
	 * The mod name must have extension. ~ and ModName can be omitted for base game plugins. RecordID can have a maximum of 8 characters.
	 * \return              - FormList pointer or nullptr if not found.
	 */
	inline RE::TESForm* FindForm(const std::string& string)
	{
		if(string.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(string, "~");
			auto [plugin, form_id_str] = std::make_pair(split_id.at(1), split_id.at(0));
			if(form_id_str.size() == 10)
				form_id_str.erase(2, 2);
			auto form_id = string::lexical_cast<RE::FormID>(form_id_str, true);

			if(const auto f = GetTESForm(plugin, form_id))
				return f;
			else
			{
				logger::error("            Can't find Form with FormID {:X} from plugin {}.", form_id, plugin);
				return nullptr;
			}
		}
		else if(string.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID(string::lexical_cast<RE::FormID>(string, true)))
				return f;

		return RE::TESForm::LookupByEditorID(string);
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

		return sanitized;
	}
}
