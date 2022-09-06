#pragma once

namespace flm::log
{
	inline unsigned int level = 0; /* Indentation level. */

	template<typename... Args>
	inline void Info(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::info("{:{}}{}", "", level * 4, fm);
	}

	template<typename... Args>
	inline void Warn(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::warn("{:{}}{}", "", level * 4, fm);
	}

	template<typename... Args>
	inline void Error(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::error("{:{}}{}", "", level * 4, fm);
	}

	inline void Header(const std::string_view& title = ""sv)
	{
		Info("{:-^47}", title);
	}

	inline void DuplicateWarn(const std::string_view& what, RE::TESForm* form)
	{
		Warn("{} \"{}\" [{:X}] already on the list!", what, form->GetName(), form->formID);
	}

	inline void Added(const std::string_view& what, RE::TESForm* form)
	{
		Info("{}: \"{}\" [{:X}] added!", what, form->GetName(), form->formID);
	}

	inline void AddedPair(const std::string_view& f, RE::TESForm* ff, const std::string_view& s, RE::TESForm* sf)
	{
		Info("{}: \"{}\" [{:X}] and {}: \"{}\" [{:X}] added!", f, ff->GetName(), ff->formID, s, sf->GetName(), sf->formID);
	}

	inline void TotalAdded(const std::string_view& what, int added, int duplicates)
	{
		Info("Total {} new {} added, skipped {} duplicates.", added, what, duplicates);
	}
}
