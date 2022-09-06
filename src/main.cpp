#include "Plugin.hpp"
#include <SimpleIni.h>
#include <xbyak/xbyak.h>

#include "RegisterFuncs.hpp"
#include "MergeMapperPluginAPI.h"

namespace
{
	/**
	 * \brief Initialize logging for plugin.
	 */
	void InitializeLog()
	{
		auto path = logger::log_directory();
		if(!path)
			util::report_and_fail("Failed to find standard logging directory"sv);

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
		constexpr const auto level = spdlog::level::info;

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		// spdlog::set_pattern("[%=17!s::%=17!!:%3#]: [%^%=7l%$] %v"s);
		spdlog::set_pattern("[%Y-%m-%d %H-%M-%S.%e] [%^%=7l%$] %v"s);
	}

	/**
	 * \brief Sink to capture SKSE events.
	 * \param event - Submitted event.
	 */
	void OnEvent(SKSE::MessagingInterface::Message* event)
	{
		if (event->type == SKSE::MessagingInterface::kPostPostLoad) {
			MergeMapperPluginAPI::GetMergeMapperInterface001();
			if (g_mergeMapperInterface) {
				const auto version = g_mergeMapperInterface->GetBuildNumber();
				logger::info("Got MergeMapper interface buildnumber {}", version);
			}
			else
				logger::info("MergeMapper not detected");
		}
		// After all the ESM/ESL/ESP plugins are loaded.
		if(event->type == SKSE::MessagingInterface::kDataLoaded)
		{
			flm::manipulator.FindAll();
			flm::manipulator.AddAll();
			flm::manipulator.Summary();
		}
		// The user has started a new game by selecting New Game at the main menu.
		else if(event->type == SKSE::MessagingInterface::kNewGame)
		{
			flm::manipulator.SetNewGameMode();
			flm::manipulator.AddAll();
		}
		// The user has loaded a saved game.
		else if(event->type == SKSE::MessagingInterface::kPostLoadGame)
		{
			flm::manipulator.SetLoadGameMode();
			flm::manipulator.AddAll();
		}
	}

	/**
	 * \brief Returns the type of Skyrim that is running. Anniversary Edition, Special Edition, VR or Unknown.
	 * \return - Type of Skyrim that is running.
	 */
	static std::string_view GetRuntimeString()
	{
		switch(REL::Module::GetRuntime())
		{
			case REL::Module::Runtime::AE:
				return "Anniversary Edition"sv;
			case REL::Module::Runtime::SE:
				return "Special Edition"sv;
			case REL::Module::Runtime::VR:
				return "VR"sv;
		}
		return "Unknown"sv;
	}
}

/**
 * \brief For AE versions of the executable - SKSE looks for static data in the DLL with the plugin metadata.
 */
extern "C" [[maybe_unused]] DLLEXPORT constinit auto SKSEPlugin_Version = []() noexcept
{
	SKSE::PluginVersionData v;

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);
	v.AuthorName(Plugin::AUTHOR);
	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_AE });

	return v;
}();

/**
 * \brief SKSE's way of identifying an SKSE plugin.
 * \param pluginInfo    - Plugin info structure.
 * \return              - True, if everything went fine.
 */
extern "C" [[maybe_unused]] DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface*, SKSE::PluginInfo* pluginInfo)
{
	pluginInfo->name = Plugin::NAME.data();
	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->version = Plugin::VERSION.pack();
	return true;
}

/**
 * \brief Once valid SKSE plugins have been identified, SKSE will call their SKSEPlugin_Load functions one at a time.
 * This function must also be present or the SKSE plugin will not be loaded, and the function must have a particular signature.
 * \param skse      - SKSE interface.
 * \return          - True, if everything went fine.
 */
extern "C" [[maybe_unused]] DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse)
{
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
	logger::info("Runtime: {}"sv, GetRuntimeString());

	SKSE::Init(skse);
	SKSE::GetMessagingInterface()->RegisterListener(OnEvent);
	SKSE::GetPapyrusInterface()->Register(papyrus::RegisterFunctions);
	SKSE::GetModCallbackEventSource()->AddEventSink(&flm::manipulator.GetEventManager());

	return true;
}
