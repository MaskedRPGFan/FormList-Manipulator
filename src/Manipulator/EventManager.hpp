#pragma once

#include "Utility/Utility.hpp"

namespace flm
{
	/**
	 * \brief Manages mod events.
	 */
	class EventManager final : public RE::BSTEventSink<SKSE::ModCallbackEvent>
	{
		public:
			EventManager() = default;
			~EventManager() override = default;

			/**
			 * \brief Returns Mod Events.
			 * \return Mod Events.
			 */
			ModEvents& Events();

		protected:
			/**
			 * \brief Processes received signals from mods.
			 * \param aEvent               - Received signal.
			 * \return                      - Status of further handling of the event: continue or stop. Always continue.
			 */
			RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* aEvent, RE::BSTEventSource<SKSE::ModCallbackEvent>*) override;

		private:
			ModEvents mod_events_; /* All valid Forms with ModEvents. */

			EventManager(const EventManager&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager& operator=(const EventManager&) = delete;
			EventManager& operator=(EventManager&&) = delete;
	};

	inline RE::BSEventNotifyControl EventManager::ProcessEvent(const SKSE::ModCallbackEvent* aEvent, RE::BSTEventSource<SKSE::ModCallbackEvent>*)
	{
		if(auto event_name = aEvent->eventName.c_str(); aEvent && mod_events_.contains(event_name))
		{
			logger::info("Got event: {}, strArg: {}, numArg: {}.", event_name, aEvent->strArg, aEvent->numArg);
			auto [added, duplicates] = AddGeneric(mod_events_[event_name]);

			const auto sent_event_name = fmt::format("{}OK", event_name);
			const SKSE::ModCallbackEvent mod_event{
				sent_event_name,
				RE::BSFixedString(fmt::format("{}|{}|{}", event_name, added, duplicates)),
				static_cast<float>(added),
				nullptr
			};

			SKSE::GetModCallbackEventSource()->SendEvent(&mod_event);
			logger::info("Sent event: {}.", sent_event_name);
		}

		return RE::BSEventNotifyControl::kContinue;
	}

	inline ModEvents& EventManager::Events()
	{
		return mod_events_;
	}
}
