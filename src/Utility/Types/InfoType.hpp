#pragma once

namespace flm::InfoType
{
	/**
	 * Types of countable statistics.
	 */
	enum InfoType
	{
		CONFIGS_V = 0, /* How many valid configs is. */
		CONFIGS_IN,    /* How many invalid configs is. */

		ENTRIES_V,  /* How many valid entries is. */
		ENTRIES_IN, /* How many invalid entries is. */
		ENTRIES_FO, /* How many entries did not meet the filter criterion. */

		ALIASES_DUP, /* Total amount of Aliases duplicates. */
		ALIASES_NE,  /* How many invalid aliases is. */

		GROUPS_DUP, /* Total amount of Groups duplicates. */
		GROUPS_NE,  /* How many in invalid groups is. */

		COLLE_DUP, /* Total amount of Collections duplicates. */
		COLLE_NE,  /* How many in invalid collections is. */

		FILTERS_DUP, /* Total amount of Filters duplicates. */
		FILTERS_NE,  /* How many in invalid Filters is. */

		FLIST_MIS, /* How many missing FormLists is. */

		FORMS,      /* Total amount of found Forms during configs parse. */
		FORMS_MISS, /* Total amount of missing Forms. */

		FORMS_ADD, /* Total amount of added Forms. */
		FORMS_DUP, /* Total amount of Forms duplicates. */

		PLANTS_ADD, /* Total amount of added Plants. */
		PLANTS_DUP, /* Total amount of Plants duplicates. */

		B_TOYS,     /* Total amount of added boy's toys. */
		B_TOYS_DUP, /* Total amount of boy's toys duplicates. */

		G_TOYS,     /* Total amount of added girl's toys. */
		G_TOYS_DUP, /* Total amount of girl's toys duplicates. */

		HAIRC,     /* Total amount of added hair colors. */
		HAIRC_DUP, /* Total amount of hair colors duplicates. */

		AFORG_ADD, /* Total amount of added recipes and results to atronach forge. */
		AFORG_DUP, /* Total amount of recipes and results duplicates to atronach forge. */

		ASFRG_ADD, /* Total amount of added recipes and results to atronach forge with sigil stone. */
		ASFRG_DUP, /* Total amount of recipes and results duplicates to atronach forge with sigil stone. */

		DSREC_ADD, /* Total amount of added recipes and results to Dragonborn Spider Crafting. */
		DSREC_DUP, /* Total amount of recipes and results duplicates to Dragonborn Spider Crafting. */

		MODEV,     /* Total amount of added Mod Events. */
		MODEV_INV, /* Total amount of invalid Mod Events. */

		ALL /* Amount of Entry types. */
	};
}
