#pragma once

#include "Types/Types.hpp"
#include "Utility/ExternalModules.hpp"

namespace flm::log
{
	inline unsigned int indent_level = 0;                    /* Indentation level. */
	inline bool debug_mode = false;                          /* Mode for more detailed information. */
	inline OMode operating_mode = OperatingMode::INITIALIZE; /* Current operating mode. */

	/**
	 * \brief Initialize logging for plugin.
	 */
	inline void InitializeLog()
	{
		auto path = logger::log_directory();
		if(!path)
			util::report_and_fail("Failed to find standard logging directory"sv);

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
		constexpr const auto log_level = spdlog::level::info;

		const auto global_log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		global_log->set_level(log_level);
		global_log->flush_on(log_level);

		spdlog::set_default_logger(std::move(global_log));
		spdlog::set_pattern("[%Y-%m-%d %H-%M-%S.%e] [%^%=7l%$] %v"s);
	}

	/**
	 * \brief Sets current operating mode to NewGame.
	 */
	inline void SetNewGameMode()
	{
		log::operating_mode = OperatingMode::NEW_GAME;
	}

	/**
	 * \brief Sets current operating mode to LoadGame.
	 */
	inline void SetLoadGameMode()
	{
		log::operating_mode = OperatingMode::LOAD_GAME;
	}

	template<typename... Args>
	inline void Info(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::info("{:{}}{}", "", indent_level * 4, fm);
	}

	template<typename... Args>
	inline void Warn(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::warn("{:{}}{}", "", indent_level * 4, fm);
	}

	template<typename... Args>
	inline void Error(std::string_view format, Args&&... args)
	{
		std::string fm = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));
		logger::error("{:{}}{}", "", indent_level * 4, fm);
	}

	inline void Header(const std::string_view& title = ""sv)
	{
		Info("{:-^47}", title);
	}

	inline void DuplicateWarn(const std::string_view& what, RE::TESForm* form)
	{
		Warn("{} {} \"{}\" [{:X}] already on the list!", what, GetEditorId(form), form->GetName(), form->formID);
	}

	inline void Added(const std::string_view& what, RE::TESForm* form)
	{
		Info("{}: {} \"{}\" [{:X}] added!", what, GetEditorId(form), form->GetName(), form->formID);
	}

	inline void AddedPair(const std::string_view& f, RE::TESForm* ff, const std::string_view& s, RE::TESForm* sf)
	{
		Info("{}: {} \"{}\" [{:X}] and {}: {} \"{}\" [{:X}] added!", f, GetEditorId(ff), ff->GetName(), ff->formID, s, GetEditorId(sf->formID), sf->GetName(), sf->formID);
	}

	inline void TotalAdded(const std::string_view& what, int added, int duplicates)
	{
		Info("Total {} new {} added, skipped {} duplicates.", added, what, duplicates);
	}
}
