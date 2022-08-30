#pragma once

#include "Manipulator.hpp"

namespace papyrus
{
	inline unsigned int functions_counter = 0;

	static std::string Version(RE::StaticFunctionTag*)
	{
		return Plugin::VERSION.string();
	}

	static bool DebugMode(RE::StaticFunctionTag*)
	{
		return flm::manipulator.DebugMode();
	}

	static void SetDebugMode(RE::StaticFunctionTag*, bool mode)
	{
		flm::manipulator.SetDebugMode(mode);
	}

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
