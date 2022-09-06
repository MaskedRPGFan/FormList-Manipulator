#pragma once

namespace flm::FormListType
{
	/**
	 * Types of FormLists from Skyrim for use in simplified entries.
	 */
	enum FormListType
	{
		SEED = 0, /* Seed. */
		PLANT,    /* Plant. */
		BTOYS,    /* Boy's toys. */
		GTOYS,    /* Girl's toys. */
		HAIRC,    /* Hair colors. */
		AFREC,    /* Atronach forge recipe. */
		AFRES,    /* Atronach forge result. */

		ALL /* Amount of FormList types. */
	};

	inline std::array<std::string, FormListType::ALL> editor_id{
		"flPlanterPlantableItem",                        /* Seeds. */
		"flPlanterPlantedFlora",                         /* Plants. */
		"BYOHRelationshipAdoptionPlayerGiftChildMale",   /* Boy's toys. */
		"BYOHRelationshipAdoptionPlayerGiftChildFemale", /* Girl's toys. */
		"HairColorList",                                 /* Hair colors. */
		"AtrFrgSigilStoneRecipeList",                    /* Atronach Forge recipes. */
		"AtrFrgSigilStoneResultList",                    /* Atronach Forge results. */
	};                                                   /* EditorIDs for FormLists used in simplified entries. */
}
