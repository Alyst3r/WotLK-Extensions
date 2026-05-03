#pragma once

#include <GameObjects/CGObject.hpp>

#include <SharedDefines.hpp>

struct ItemEnchant
{
    uint32_t m_ID;
    uint32_t m_duration;
    // Aleist3r: apparently server treats those two as uint32 so I'm doing it here as well, until it turns out to be broken in the client
    // uint16_t field2;
    // uint16_t field3;
    uint32_t m_charges;
};

struct ItemFields
{
    WoWGUID m_owner;
    WoWGUID m_container;
    WoWGUID m_creator;
    WoWGUID m_giftCreator;
    uint32_t m_itemStackCount;
    uint32_t m_itemDuration;
    uint32_t m_itemSpellCharges[5];
    uint32_t m_flags;
    ItemEnchant m_enchantment[12];
    uint32_t m_propertySeed;
    uint32_t m_randomPropertySeed;
    uint32_t m_durability;
    uint32_t m_maxDurability;
    uint32_t m_createPlayedTime; // ?
    uint32_t m_padding;
};

struct CGItem : CGObject
{
    void* m_vTable;
    ItemFields* m_itemData;
    int32_t padding0xD4[176];
    int32_t m_flags;
    int32_t m_padding0x039C[242];

    static char* BuildItemName(char* buffer, int32_t size, int32_t itemID, int32_t a4);
    static int32_t sub_61DC90(void* thisObject);
    static int32_t sub_707390(void* thisObject, int32_t a2);
    static bool sub_708520(CGItem* thisItem);
};
