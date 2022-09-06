#pragma once

#include "EntryType.hpp"

namespace flm
{
	inline std::array<std::string, EntryType::ALL> keywords{
		"alias",         /* Aliases for FormLists. */
		"group",         /* Groups for Forms. */
		"modevent",      /* Mod events. */
		"formlist",      /* FromList. */
		"plant",         /* Plant. */
		"btoys",         /* Boy's toys. */
		"gtoys",         /* Girl's toys. */
		"haircolors",    /* Hair colors. */
		"atronachforge", /* Atronach forge. */
	};                   /* Types of the keywords used in config files. */
}
