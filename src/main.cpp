#include "Plugin.hpp"
#include <SimpleIni.h>
#include <xbyak/xbyak.h>

#include "RegisterFuncs.hpp"

namespace
{
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
		spdlog::set_pattern("[%=17!s::%=17!!:%3#]: [%^%=7l%$] %v"s);
	}

	void OnEvent(SKSE::MessagingInterface::Message* event)
	{
		// After all the ESM/ESL/ESP plugins are loaded.
		if(event->type == SKSE::MessagingInterface::kDataLoaded)
		{
			flm::manipulator.FindLists();
			flm::manipulator.FindConfigs();
			flm::manipulator.AddPlants();
			flm::manipulator.AddToys();
			flm::manipulator.AddToFormLists();
			flm::manipulator.Summary();
		}
	}

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

extern "C" [[maybe_unused]] DLLEXPORT constinit auto SKSEPlugin_Version = []() noexcept
{
	SKSE::PluginVersionData v;

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);
	v.AuthorName(Plugin::AUTHOR);
	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();

extern "C" [[maybe_unused]] DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface*, SKSE::PluginInfo* pluginInfo)
{
	pluginInfo->name = Plugin::NAME.data();
	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->version = Plugin::VERSION.pack();
	return true;
}

extern "C" [[maybe_unused]] DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse)
{
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
	logger::info("Runtime: {}"sv, GetRuntimeString());

	SKSE::Init(skse);
	SKSE::GetMessagingInterface()->RegisterListener(OnEvent);
	SKSE::GetPapyrusInterface()->Register(papyrus::RegisterFunctions);

	return true;
}
