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
		ASFRC,    /* Atronach forge with Sigil Stone recipe. */
		ASFRS,    /* Atronach forge with Sigil Stone result. */
		DSREC,    /* Dragonborn Spider Crafting recipe. */
		DSRES,    /* Dragonborn Spider Crafting result. */

		ALL /* Amount of FormList types. */
	};

	inline std::array<std::string, FormListType::ALL> editor_id{
		"flPlanterPlantableItem",                        /* Seeds. */
		"flPlanterPlantedFlora",                         /* Plants. */
		"BYOHRelationshipAdoptionPlayerGiftChildMale",   /* Boy's toys. */
		"BYOHRelationshipAdoptionPlayerGiftChildFemale", /* Girl's toys. */
		"HairColorList",                                 /* Hair colors. */
		"AtrFrgAtronachForgeRecipeList",                 /* Atronach Forge recipes. */
		"AtrFrgAtronachForgeResultList",                 /* Atronach Forge results. */
		"AtrFrgSigilStoneRecipeList",                    /* Atronach Forge with Sigil Stone recipes. */
		"AtrFrgSigilStoneResultList",                    /* Atronach Forge with Sigil Stone results. */
		"DLC2ExpSpiderCraftingRecipesList",              /* Dragonborn Spider Crafting recipes. */
		"DLC2ExpSpiderCraftingResultsList",              /* Dragonborn Spider Crafting results. */
	};                                                   /* EditorIDs for FormLists used in simplified entries. */
}
