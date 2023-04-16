#pragma once

#undef MessageBox
#undef GetModuleHandle

namespace winApi = SKSE::WinAPI;

namespace flm
{
	inline winApi::HMODULE tweaks{ nullptr }; /* PowerOfThree Tweaks handle. */

	/**
	 * \brief Returns the EditorID for a given FromID.
	 * \param fromId            - FromID for which EditorID will be returned.
	 * \return                  - EditorID for given FormID.
	 */
	inline std::string GetEditorId(const RE::FormID fromId)
	{
		if(static auto function = reinterpret_cast<const char* (*)(std::uint32_t)>(GetProcAddress(tweaks, "GetFormEditorID")))
			return function(fromId);

		return {};
	}

	/**
	 * \brief Returns the EditorID for a given FromID.
	 * \param form              - From for which EditorID will be returned.
	 * \return                  - EditorID for given FormID.
	 */
	inline std::string GetEditorId(const RE::TESForm* form)
	{
		return GetEditorId(form->formID);
	}

	/**
	 * \brief Checks whether the specified dll library has been installed.
	 * \param dll               - Poiter to dll.
	 * \param dllName           - Name of the dll.
	 * \param header            - Header in the displayed message if the dll is not installed.
	 * \param info              - The contents of the displayed message if the dll is not installed.
	 */
	inline void CheckDll(winApi::HMODULE& dll, const wchar_t* dllName, const std::string_view& header, const std::string_view& info)
	{
		dll = winApi::GetModuleHandle(dllName);
		if(!dll)
			if(const auto id = winApi::MessageBox(nullptr, info.data(), header.data(), 0x00000001); id == 2)
				std::_Exit(EXIT_FAILURE);
	}

	/**
	 * \brief Checks whether po3's Tweaks has been installed.
	 */
	inline void CheckPo3Tweaks()
	{
		constexpr std::string_view header = R"(No po3's Tweaks installed!)";
		constexpr std::string_view info_f = R"(po3's Tweaks is required for {} to work, install it from: https://www.nexusmods.com/skyrimspecialedition/mods/51073.)";
		const std::string info = fmt::format(info_f.data(), Plugin::NAME);
		CheckDll(flm::tweaks, L"po3_Tweaks", header, info.c_str());
	}
}
