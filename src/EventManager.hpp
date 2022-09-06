#pragma once

#include "Utility.hpp"

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
			 * \param a_event               - Received signal.
			 * \return                      - Status of further handling of the event: continue or stop. Always continue.
			 */
			RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* a_event, RE::BSTEventSource<SKSE::ModCallbackEvent>*) override;

		private:
			ModEvents mod_events_; /* All valid Forms with ModEvents. */

			EventManager(const EventManager&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager& operator=(const EventManager&) = delete;
			EventManager& operator=(EventManager&&) = delete;
	};

	inline RE::BSEventNotifyControl EventManager::ProcessEvent(const SKSE::ModCallbackEvent* a_event, RE::BSTEventSource<SKSE::ModCallbackEvent>*)
	{
		if(auto event_name = a_event->eventName.c_str(); a_event && mod_events_.contains(event_name))
		{
			logger::info("Got event: {}, strArg: {}, numArg: {}.", event_name, a_event->strArg, a_event->numArg);
			auto [added, duplicates] = AddGeneric(mod_events_[event_name], OperatingMode::INITIALIZE);

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
