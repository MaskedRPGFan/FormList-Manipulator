#pragma once

namespace flm::InfoType
{
	/**
	 * Types of countable statistics.
	 */
	enum InfoType
	{
		CONFIGS_V = 0, /** How many valid configs is. */
		CONFIGS_IN,    /** How many invalid configs is. */
		ENTRIES_V,     /** How many valid entries is. */
		ENTRIES_IN,    /** How many invalid entries is. */

		ALIASES,     /** Total amount of found Aliases. */
		ALIASES_DUP, /** Total amount of Aliases duplicates. */
		ALIASES_NE,  /** How many invalid aliases is. */

		GROUPS,     /** Total amount of found Groups. */
		GROUPS_DUP, /** Total amount of Groups duplicates. */
		GROUPS_NE,  /** How many in invalid aliases is. */

		FLIST_MIS, /** How many missing FormLists is. */

		FORMS,      /** Total amount of found Forms during configs parse. */
		FORMS_ADD,  /** Total amount of added Forms. */
		FORMS_DUP,  /** Total amount of Forms duplicates. */
		FORMS_MISS, /** Total amount of missing Forms. */

		PLANTS_ADD, /** Total amount of added Plants. */
		PLANTS_DUP, /** Total amount of Plants duplicates. */

		B_TOYS,       /** Total amount of added boy's toys. */
		BOY_TOYS_DUP, /** Total amount of boy's toys duplicates. */

		G_TOYS,        /** Total amount of added girl's toys. */
		GIRL_TOYS_DUP, /** Total amount of girl's toys duplicates. */

		HAIRC,     /** Total amount of added hair colors. */
		HAIRC_DUP, /** Total amount of hair colors duplicates. */

		AFORG_ADD, /** Total amount of added recipes and results to atronach forge. */
		AFORG_DUP, /** Total amount of recipes and results duplicates. */

		MODEV,     /** Total amount of added Mod Events. */
		MODEV_INV, /** Total amount of invalid Mod Events. */

		ALL /* Amount of Entry types. */
	};
}
