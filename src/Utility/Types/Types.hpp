#pragma once

#include "Utility/Types/EntryType.hpp"
#include "Utility/Types/FormListType.hpp"
#include "Utility/Types/InfoType.hpp"
#include "Utility/Types/Keywords.hpp"
#include "Utility/Types/OperatingMode.hpp"

namespace flm
{
    // From pow3 KID
    struct StringViewHash
	{
		using is_transparent = void;  // enable heterogeneous overloads
		using is_avalanching = void;  // mark class as high quality avalanching hash

		[[nodiscard]] std::uint64_t operator()(std::string_view str) const noexcept
		{
			return ankerl::unordered_dense::hash<std::string_view>{}(str);
		}
	};

	template <class D>
	using StringViewMap = ankerl::unordered_dense::map<std::string_view, D, StringViewHash, std::equal_to<>>; /* String_view map. */
    template <class D>
	using StringMap = ankerl::unordered_dense::map<std::string, D, StringViewHash, std::equal_to<>>; /* String map. */
	using StringViewSet = ankerl::unordered_dense::set<std::string_view, StringViewHash, std::equal_to<>>;
	using StringSet = ankerl::unordered_dense::set<std::string, StringViewHash, std::equal_to<>>;

    template <class K, class D>
	using Map = ankerl::unordered_dense::segmented_map<K, D>;
	template <class K>
	using Set = ankerl::unordered_dense::segmented_set<K>;

	using ParseEntryCallback = std::function<bool(const std::string&)>;                      /* Pointer to the function that parses the entry. */
	using Forms = std::vector<RE::TESForm*>;                                                 /* Vector of pointers to TESForms. */
	using MapForms = StringMap<Forms>;                                                       /* Map with Vectors of pointers to TESForms. */
	using FormListsData = std::map<RE::BGSListForm*, Forms>;                                 /* Data for mod events. */
	using MapModEvents = StringMap<FormListsData>;                                           /* Mod events type. */
	using FormPair = std::pair<RE::TESForm*, RE::TESForm*>;                                  /* Pair of Forms*. */
	using FormsLists = std::vector<RE::BGSListForm*>;                                        /* Vector of pointers to BGSListForm. */
	using FormsPairs = std::vector<FormPair>;                                                /* Vector of FormPair. */
	using StringViewPair = std::pair<std::string_view, std::string_view>;                    /* Pair of string views. */
	using PairEntryNames = std::tuple<std::string_view, std::string_view, std::string_view>; /* Names for pair entry: entry, first element, second element. */
	using Flt = FormListType::FormListType;                                                  /* Form list type. */
	using FltPair = std::pair<Flt, Flt>;                                                     /* Pair of Form list types. */
	using InfoT = InfoType::InfoType;                                                        /* Info type. */
	using InfoTPair = std::pair<InfoT, InfoT>;                                               /* Pair of Info types. */
	using OMode = OperatingMode::OperatingMode;                                              /* Operating mode. */
    using GetFormEditorId = const char* (*)(std::uint32_t);                                  /* Pow3 GetFormEditorID function type. */ 
	using Keywords = std::vector<RE::BGSKeyword*>;                                           /* Vector of keywords.*/
	using KeywordsPairVec = std::pair<Keywords, Keywords>;                                   /* Pair of Vectors of Keywords.*/
	using MapKeywords = StringViewMap<RE::BGSKeyword*>;                                      /* For EditorID - keyword. */
	using StringMapSet = StringMap<StringSet>;                                               /* Map of name - set. */

	namespace ift = InfoType; /* InfoType namespace short alias. */

	using Strings = std::vector<std::string>;                                                /* Vector of strings.*/
	using CollectionData = StringMap<KeywordsPairVec>;                                       /* Pair Collection name - keywords.*/
}
