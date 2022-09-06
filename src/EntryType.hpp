#pragma once

namespace flm::EntryType
{
	/**
	 * Types of entries in configuration files.
	 */
	enum EntryType
	{
		ALIAS = 0, /* Aliases for FormLists. */
		GROUP,     /* Groups for Forms. */
		MODEV,     /* Mod events. */
		FLIST,     /* FromList. */
		PLANT,     /* Plant. */
		BTOYS,     /* Boy's toys. */
		GTOYS,     /* Girl's toys. */
		HAIRC,     /* Hair colors. */
		AFORG,     /* Atronach forge. */

		ALL /* Amount of Entry types. */
	};
}
