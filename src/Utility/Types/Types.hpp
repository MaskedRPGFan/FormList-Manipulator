#pragma once

#include "Utility/Types/EntryType.hpp"
#include "Utility/Types/FormListType.hpp"
#include "Utility/Types/InfoType.hpp"
#include "Utility/Types/Keywords.hpp"
#include "Utility/Types/OperatingMode.hpp"

namespace flm
{
	using ParseEntryCallback = std::function<bool(const std::string&)>;                      /* Pointer to the function that parses the entry. */
	using FormListsData = std::map<RE::BGSListForm*, std::vector<RE::TESForm*>>;             /* Data for mod events. */
	using ModEvents = std::unordered_map<std::string, FormListsData>;                        /* Mod events type. */
	using FormPair = std::pair<RE::TESForm*, RE::TESForm*>;                                  /* Pair of Forms*. */
	using Forms = std::vector<RE::TESForm*>;                                                 /* Vector of pointers to TESFroms. */
	using FormsLists = std::vector<RE::BGSListForm*>;                                        /* Vector of pointers to BGSListForm. */
	using FormsPairs = std::vector<FormPair>;                                                /* Vector of FormPair. */
	using StringViewPair = std::pair<std::string_view, std::string_view>;                    /* Pair of string views. */
	using PairEntryNames = std::tuple<std::string_view, std::string_view, std::string_view>; /* Names for pair entry: entry, first element, second element. */
	using Flt = FormListType::FormListType;                                                  /* Form list type. */
	using FltPair = std::pair<Flt, Flt>;                                                     /* Pair of Form list types. */
	using InfoT = InfoType::InfoType;                                                        /* Info type. */
	using InfoTPair = std::pair<InfoT, InfoT>;                                               /* Pair of Info types. */
	using OMode = OperatingMode::OperatingMode;                                              /* Operating mode. */
}
