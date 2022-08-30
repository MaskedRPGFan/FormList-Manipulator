#pragma once

namespace flm
{
	inline RE::BGSListForm* GetFormList(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm<RE::BGSListForm>(rawFormId, pluginName) : nullptr;
	}

	inline RE::TESForm* GetTESForm(const std::string& pluginName, const std::uint32_t rawFormId)
	{
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return data_handler ? data_handler->LookupForm(rawFormId, pluginName) : nullptr;
	}

	inline RE::BGSListForm* FindFormList(const std::string& aStr)
	{
		if(aStr.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(aStr, "~");
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
		else if(aStr.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID<RE::BGSListForm>(string::lexical_cast<RE::FormID>(aStr, true)))
				return f;

		return RE::TESForm::LookupByEditorID<RE::BGSListForm>(aStr);
	}

	inline RE::TESForm* FindForm(const std::string& aStr)
	{
		if(aStr.find("~"sv) != std::string::npos)
		{
			auto split_id = string::split(aStr, "~");
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
		else if(aStr.find("0x"sv) != std::string::npos)
			if(const auto f = RE::TESForm::LookupByID(string::lexical_cast<RE::FormID>(aStr, true)))
				return f;

		return RE::TESForm::LookupByEditorID(aStr);
	}

	// From https://github.com/powerof3/Spell-Perk-Item-Distributor
	inline std::string Sanitize(const std::string& string)
	{
		auto sanitized = string;

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
