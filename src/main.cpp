#include "Plugin.hpp"

#include "Manipulator/RegisterFuncs.hpp"
#include "Manipulator/EventManager.hpp"
#include "MergeMapperPluginAPI.h"

namespace
{
	/**
	 * \brief Sink to capture SKSE events.
	 * \param event - Submitted event.
	 */
	void OnEvent(SKSE::MessagingInterface::Message* event)
	{

		// After all the ESM/ESL/ESP plugins are loaded.
		if(event->type == SKSE::MessagingInterface::kDataLoaded)
		{
            if(!flm::CheckPo3Kid())
            {
				flm::manipulator.FindAll();
				flm::manipulator.AddAll();
				flm::manipulator.SendEventDone();
            }
			else
				flm::log::Info(("KID is installed, waiting for KID to finish distribution..."));

		}
		// When Skyrim starts, SKSE will begin by querying for SKSE plugins and then calling each plugin's SKSEPlugin_Load function.
		// Once all load functions are called this message is sent.
		else if(event->type == SKSE::MessagingInterface::kPostLoad)
		{
			flm::CheckPo3Tweaks();
		}
		// The user has started a new game by selecting New Game at the main menu.
		else if(event->type == SKSE::MessagingInterface::kNewGame)
		{
			flm::log::SetNewGameMode();
			flm::manipulator.AddAll();
		}
		// The user has loaded a saved game.
		else if(event->type == SKSE::MessagingInterface::kPostLoadGame)
		{
			flm::log::SetLoadGameMode();
			flm::manipulator.AddAll();
		}
		// Once all kPostLoad handlers have run, it will signal kPostPostLoad.
		else if(event->type == SKSE::MessagingInterface::kPostPostLoad)
		{
			if(MergeMapperPluginAPI::GetMergeMapperInterface001())
			{
				const auto version = g_mergeMapperInterface->GetBuildNumber();
				logger::info("Got MergeMapper interface buildnumber {}", version);
			}
			else
				logger::info("MergeMapper not detected");
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
			default: ;
		}
		return "Unknown"sv;
	}
}

/**
 * \brief Once valid SKSE plugins have been identified, SKSE will call their SKSEPlugin_Load functions one at a time.
 * This function must also be present or the SKSE plugin will not be loaded, and the function must have a particular signature.
 * \param skse      - SKSE interface.
 * \return          - True, if everything went fine.
 */
extern "C" [[maybe_unused]] DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse)
{
	flm::log::InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
	logger::info("Runtime: {}"sv, GetRuntimeString());

	SKSE::Init(skse);
	SKSE::GetMessagingInterface()->RegisterListener(OnEvent);
	SKSE::GetPapyrusInterface()->Register(papyrus::RegisterFunctions);
	SKSE::GetModCallbackEventSource()->AddEventSink(&flm::event_manager);

	return true;
}
