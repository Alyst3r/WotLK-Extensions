#include <Client/ClientServices.hpp>
#include <Client/Misc.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void Misc::ApplyPatches()
{
    uint32_t addressArray[] = { 0x510440, 0x510460, 0x52B2BC, 0x6B204C, 0x6B21F9 };

    for (size_t i = 0; i < sizeof(addressArray) / 4; i++)
        Util::OverwriteUInt32AtAddress(addressArray[i] - 4, reinterpret_cast<uint32_t>(&ClientServices::CharacterLogoutEx) - addressArray[i]);

#if NOAMMO_PATCH
    uint8_t byteArray[] = { 0xE9, 0xBA, 0x00, 0x00, 0x00 };
    Util::OverwriteBytesAtAddress(0x809540, byteArray, sizeof(byteArray));
#endif

#if ITEMMODEXT_PATCH
    // Code needs to be un-commented when you decide to add some custom mods
    // ofc can replace "ITEM_MOD_TEST" with your own
    //const char* customItemModStrings[1] =
    //{
    //    "ITEM_MOD_TEST"
    //};

    memcpy(&itemModTable, (const void*)0xAD6640, 0xC4);
    Util::OverwriteUInt32AtAddress(0x5DC1EB, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x629211, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x6292E6, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x62BC60, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x62BE67, (uint32_t)&itemModTable);
    //
    Util::OverwriteUInt32AtAddress(0x62BD82, (uint32_t)&itemModTable[45]);
    // when you read code in ida, this table is kinda dumb but what can you do about it
    memcpy(&itemModTableVal, (const void*)0xA25F78, 0x94);
    Util::OverwriteUInt32AtAddress(0x62BC43, (uint32_t)&itemModTableVal);
    Util::SetByteAtAddress((void*)0x62BC4E, (uint8_t)(sizeof(itemModTableVal)/4));
    Util::OverwriteUInt32AtAddress(0x62BC59, (uint32_t)&itemModTableVal);
    Util::OverwriteUInt32AtAddress(0x62BE4A, (uint32_t)&itemModTableVal);
    Util::SetByteAtAddress((void*)0x62BE55, (uint8_t)(sizeof(itemModTableVal) / 4));
    Util::OverwriteUInt32AtAddress(0x62BE60, (uint32_t)&itemModTableVal);

    //for (uint32_t i = 0; i < sizeof(customItemModStrings) / 4; i++)
    //    itemModTable[i + 49] = (uint32_t)customItemModStrings[i];

    //for (uint32_t j = 37; j < sizeof(itemModTableVal) / 4; j++)
    //    itemModTableVal[j] = j + 12;
#endif

#if OCCLUSIONVOLUME_DBC
    Util::OverwriteUInt32AtAddress(0x9E04CC, 0x5EEB70);
#endif
}
