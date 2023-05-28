#pragma once

#include "Types.hpp"

namespace flm
{
    inline const StringViewMap<RE::FormType> FORM_TYPES{
        { "armor"sv, RE::FormType::Armor },
        { "weapon"sv, RE::FormType::Weapon },
        { "ammo"sv, RE::FormType::Ammo },
        { "magiceffect"sv, RE::FormType::MagicEffect },
        { "alchemyitem"sv, RE::FormType::AlchemyItem },
        { "scroll"sv, RE::FormType::Scroll },
        { "location"sv, RE::FormType::Location },
        { "ingredient"sv, RE::FormType::Ingredient },
        { "book"sv, RE::FormType::Book },
        { "misc"sv, RE::FormType::Misc },
        { "key"sv, RE::FormType::KeyMaster },
        { "soulgem"sv, RE::FormType::SoulGem },
        { "activator"sv, RE::FormType::Activator },
        { "flora"sv, RE::FormType::Flora },
        { "furniture"sv, RE::FormType::Furniture },
        { "race"sv, RE::FormType::Race },
        { "talkingactivator"sv, RE::FormType::TalkingActivator },
        { "enchantment"sv, RE::FormType::Enchantment },
        { "npc"sv, RE::FormType::NPC },
        { "spell"sv, RE::FormType::Spell },
    };
}
