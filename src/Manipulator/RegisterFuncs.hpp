#pragma once

#include "Manipulator.hpp"

namespace papyrus
{
	inline unsigned int functions_counter = 0;

	/**
	 * \brief Returns version of the dll.
	 * \return                  - Version of the dll.
	 */
	static std::string Version(RE::StaticFunctionTag*)
	{
		return Plugin::VERSION.string();
	}

	/**
	 * \brief Returns debug mode state.
	 * \return                  - Debug mode state.
	 */
	static bool DebugMode(RE::StaticFunctionTag*)
	{
		return flm::log::debug_mode;
	}

	/**
	 * \brief Sets debug mode state.
	 * \param mode              - New debug mode state.
	 */
	static void SetDebugMode(RE::StaticFunctionTag*, bool mode)
	{
		flm::log::debug_mode = mode;
	}

	/**
	 * \brief Register functions for Papyrus scripts.
	 * \param aVirtualMachine   - Papyrus virtual machine.
	 * \return                  - True, if everything went fine.
	 */
	inline bool RegisterFunctions(RE::BSScript::IVirtualMachine* aVirtualMachine)
	{
		aVirtualMachine->RegisterFunction("Version", Plugin::NAME, Version);
		functions_counter++;
		aVirtualMachine->RegisterFunction("DebugMode", Plugin::NAME, DebugMode);
		functions_counter++;
		aVirtualMachine->RegisterFunction("SetDebugMode", Plugin::NAME, SetDebugMode);
		functions_counter++;

		// logger::info("Registered {} Papyrus functions.", functions_counter);
		return true;
	}
}
