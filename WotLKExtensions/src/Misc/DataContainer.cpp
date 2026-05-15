#include <Data/DBCAddresses.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <SharedDefines.hpp>

#include <PatchConfig.hpp>

#include <ctime>

DataContainer::DataContainer() : m_lfgRolesCDBC(LFGRoles::GetInstance()), m_occlusionVolumeCDBC(OcclusionVolume::GetInstance()), m_occlusionVolumePointCDBC(OcclusionVolumePoint::GetInstance()),
    m_spellAttributesExtendedCDBC(SpellAttributesExtended::GetInstance()), m_zoneLightCDBC(ZoneLight::GetInstance()), m_zoneLightPointCDBC(ZoneLightPoint::GetInstance())
{
    m_raceNameTable.resize(32, 0);
    m_memoryTable.resize(64, 0);
    SetupDBCDataVector();
}

DataContainer::~DataContainer()
{
}

DataContainer& DataContainer::GetInstance()
{
    static DataContainer instance;

    return instance;
}

void DataContainer::ResetData()
{
    for (size_t i = 0; i < 7; i++)
        m_playerFields.m_combatRating[i] = 0;
}

void DataContainer::AddLuaFunction(const char* name, void* ptr)
{
    m_luaFunctions.insert(std::make_pair(name, ptr));
}

std::unordered_map<const char*, void*>& DataContainer::GetLuaFunctionMap()
{
    return m_luaFunctions;
}

void DataContainer::AddGlueLuaFunction(const char* name, void* ptr)
{
    m_glueLuaFunctions.insert(std::make_pair(name, ptr));
}

std::unordered_map<const char*, void*>& DataContainer::GetGlueLuaFunctionMap()
{
    return m_glueLuaFunctions;
}

void DataContainer::AddPacketHandler(uint32_t opcode, CNetClientCustomPacket packetData)
{
    m_packetData.insert(std::make_pair(opcode, packetData));
}

std::unordered_map <uint32_t, CNetClientCustomPacket>& DataContainer::GetPacketHandlerMap()
{
    return m_packetData;
}

void DataContainer::AddGlueCVar(const CustomCVar& entry)
{
    m_customGlueCVars.push_back(entry);
}

std::vector<CustomCVar>& DataContainer::GetGlueCVarVector()
{
    return m_customGlueCVars;
}

void DataContainer::LoadLFGRolesDB()
{
    m_lfgRolesCDBC.LoadDB();
}

void DataContainer::UnloadLFGRolesDB()
{
    m_lfgRolesCDBC.UnloadDB();
}

void DataContainer::GetLFGRolesRow(LFGRolesRow& row, int32_t index)
{
    m_lfgRolesCDBC.GetRow(row, index);
}

void DataContainer::LoadOcclusionVolumeDB()
{
    m_occlusionVolumeCDBC.LoadDB();
}

void DataContainer::UnloadOcclusionVolumeDB()
{
    m_occlusionVolumeCDBC.UnloadDB();
}

void DataContainer::GetOcclusionVolumeRow(OcclusionVolumeRow& row, int32_t index)
{
    m_occlusionVolumeCDBC.GetRow(row, index);
}

int32_t DataContainer::GetOcclusionVolumeRowMinIndex() const
{
    return m_occlusionVolumeCDBC.GetMinIndex();
}
int32_t DataContainer::GetOcclusionVolumeRowMaxIndex() const
{
    return m_occlusionVolumeCDBC.GetMaxIndex();
}

void DataContainer::LoadOcclusionVolumePointDB()
{
    m_occlusionVolumePointCDBC.LoadDB();
}

void DataContainer::UnloadOcclusionVolumePointDB()
{
    m_occlusionVolumePointCDBC.UnloadDB();
}

void DataContainer::GetOcclusionVolumePointRow(OcclusionVolumePointRow& row, int32_t index)
{
    m_occlusionVolumePointCDBC.GetRow(row, index);
}

int32_t DataContainer::GetOcclusionVolumePointRowMinIndex() const
{
    return m_occlusionVolumePointCDBC.GetMinIndex();
}

int32_t DataContainer::GetOcclusionVolumePointRowMaxIndex() const
{
    return m_occlusionVolumePointCDBC.GetMaxIndex();
}

void DataContainer::LoadSpellAttributesExtendedDB()
{
    m_spellAttributesExtendedCDBC.LoadDB();
}

void DataContainer::UnloadSpellAttributesExtendedDB()
{
    m_spellAttributesExtendedCDBC.UnloadDB();
}

void DataContainer::GetSpellAttributesExtendedRow(SpellAttributesExtendedRow& row, int32_t index)
{
    m_spellAttributesExtendedCDBC.GetRow(row, index);
}

void DataContainer::LoadZoneLightDB()
{
    m_zoneLightCDBC.LoadDB();
}

void DataContainer::UnloadZoneLightDB()
{
    m_zoneLightCDBC.UnloadDB();
}

void DataContainer::GetZoneLightRow(ZoneLightRow& row, int32_t index)
{
    m_zoneLightCDBC.GetRow(row, index);
}

int32_t DataContainer::GetZoneLightRowMinIndex() const
{
    return m_zoneLightCDBC.GetMinIndex();
}
int32_t DataContainer::GetZoneLightRowMaxIndex() const
{
    return m_zoneLightCDBC.GetMaxIndex();
}

void DataContainer::LoadZoneLightPointDB()
{
    m_zoneLightPointCDBC.LoadDB();
}

void DataContainer::UnloadZoneLightPointDB()
{
    m_zoneLightPointCDBC.UnloadDB();
}

void DataContainer::GetZoneLightPointRow(ZoneLightPointRow& row, int32_t index)
{
    m_zoneLightPointCDBC.GetRow(row, index);
}

int32_t DataContainer::GetZoneLightPointRowMinIndex() const
{
    return m_zoneLightPointCDBC.GetMinIndex();
}

int32_t DataContainer::GetZoneLightPointRowMaxIndex() const
{
    return m_zoneLightPointCDBC.GetMaxIndex();
}

std::vector<const char*>& DataContainer::GetSpellVariableData()
{
    return m_spellVariables;
}

uint32_t* DataContainer::GetRaceTablePtr()
{
    return m_raceNameTable.data();
}

uint32_t* DataContainer::GetMemoryTablePtr()
{
    return m_memoryTable.data();
}

uint8_t* DataContainer::GetClassRoleMaskTablePtr()
{
    return m_classRoleMask.data();
}

uint32_t DataContainer::GetYearOffsetMultiplier() const
{
    return m_yearOffsetMult;
}

void DataContainer::SetYearOffsetMultiplier()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    m_yearOffsetMult = (ltm->tm_year - 100) / 32;
}

void DataContainer::AddOcclusionVolume(OcclusionVolumeData& occlusionData)
{
    m_occlusionVolumeData.push_back(occlusionData);
}

void DataContainer::ClearOcclusionVolume()
{
    m_occlusionVolumeData.clear();
}

OcclusionVolumeData* DataContainer::GetOcclusionVolumeData()
{
    return m_occlusionVolumeData.data();
}

size_t DataContainer::GetOcclusionVolumeDataSize() const
{
    return m_occlusionVolumeData.size();
}

void DataContainer::AddZoneLight(ZoneLightData& lightData)
{
    m_zoneLightData.push_back(lightData);
}

void DataContainer::ClearZoneLight()
{
    m_zoneLightData.clear();
}

std::vector<ZoneLightData>& DataContainer::GetZoneLightData()
{
    return m_zoneLightData;
}

bool DataContainer::GetShouldFillZoneLightData() const
{
    return m_shouldFillZoneLightData;
}

void DataContainer::SetShouldFillZoneLightData(bool result/* = true*/)
{
    m_shouldFillZoneLightData = result;
}

int32_t DataContainer::GetCustomCombatRating(int8_t index) const
{
    return m_playerFields.m_combatRating[index];
}

void DataContainer::SetCustomCombatRating(int8_t index, int32_t value)
{
    m_playerFields.m_combatRating[index] = value;
}

std::vector<DBClientEntry>& DataContainer::GetDBCDataVector()
{
    return m_dbcData;
}

void DataContainer::SetupDBCDataVector()
{
    m_dbcData.reserve(237);
    
    m_dbcData.emplace_back(DBClientEntry("achievement", g_achievementDB, 235));
    m_dbcData.emplace_back(DBClientEntry("achievement_criteria", g_achievement_CriteriaDB, 236));
    m_dbcData.emplace_back(DBClientEntry("achievement_category", g_achievement_CategoryDB, 237));
    m_dbcData.emplace_back(DBClientEntry("animationdata", g_animationDataDB, 238));
    m_dbcData.emplace_back(DBClientEntry("areagroup", g_areaGroupDB, 239));
    m_dbcData.emplace_back(DBClientEntry("areapoi", g_areaPOIDB, 240));
    m_dbcData.emplace_back(DBClientEntry("areatable", g_areaTableDB, 241));
    m_dbcData.emplace_back(DBClientEntry("areatrigger", g_areaTriggerDB, 242));
    m_dbcData.emplace_back(DBClientEntry("attackanimkit", g_attackAnimKitsDB, 243));
    m_dbcData.emplace_back(DBClientEntry("attackanimtypes", g_attackAnimTypesDB, 244));
    m_dbcData.emplace_back(DBClientEntry("auctionhouse", g_auctionHouseDB, 245));
    m_dbcData.emplace_back(DBClientEntry("bankbagslotprices", g_bankBagSlotPricesDB, 246));
    m_dbcData.emplace_back(DBClientEntry("bannedaddons", g_bannedAddOnsDB, 247));
    m_dbcData.emplace_back(DBClientEntry("barbershopstyle", g_barberShopStyleDB, 248));
    m_dbcData.emplace_back(DBClientEntry("battlemasterlist", g_battlemasterListDB, 249));
    m_dbcData.emplace_back(DBClientEntry("camerashakes", g_cameraShakesDB, 250));
    m_dbcData.emplace_back(DBClientEntry("cfg_categories", g_cfg_CategoriesDB, 251));
    m_dbcData.emplace_back(DBClientEntry("cfg_configs", g_cfg_ConfigsDB, 252));
    m_dbcData.emplace_back(DBClientEntry("charbaseinfo", g_charBaseInfoDB, 253));
    m_dbcData.emplace_back(DBClientEntry("charhairgeosets", g_charHairGeosetsDB, 254));
    m_dbcData.emplace_back(DBClientEntry("charsections", g_charSectionsDB, 255));
    m_dbcData.emplace_back(DBClientEntry("charstartoutfit", g_charStartOutfitDB, 256));
    m_dbcData.emplace_back(DBClientEntry("chartitles", g_charTitlesDB, 257));
    m_dbcData.emplace_back(DBClientEntry("characterfacialhairstyles", g_characterFacialHairStylesDB, 258));
    m_dbcData.emplace_back(DBClientEntry("chatchannels", g_chatChannelsDB, 259));
    m_dbcData.emplace_back(DBClientEntry("chatprofanity", g_chatProfanityDB, 260));
    m_dbcData.emplace_back(DBClientEntry("chrclasses", g_chrClassesDB, 261));
    m_dbcData.emplace_back(DBClientEntry("chrraces", g_chrRacesDB, 262));
    m_dbcData.emplace_back(DBClientEntry("cinematiccamera", g_cinematicCameraDB, 263));
    m_dbcData.emplace_back(DBClientEntry("cinematicsequences", g_cinematicSequencesDB, 264));
    m_dbcData.emplace_back(DBClientEntry("creaturedisplayinfo", g_creatureDisplayInfoDB, 265));
    m_dbcData.emplace_back(DBClientEntry("creaturedisplayinfoextra", g_creatureDisplayInfoExtraDB, 266));
    m_dbcData.emplace_back(DBClientEntry("creaturefamily", g_creatureFamilyDB, 267));
    m_dbcData.emplace_back(DBClientEntry("creaturemodeldata", g_creatureModelDataDB, 268));
    m_dbcData.emplace_back(DBClientEntry("creaturemovementinfo", g_creatureMovementInfoDB, 269));
    m_dbcData.emplace_back(DBClientEntry("creaturesounddata", g_creatureSoundDataDB, 270));
    m_dbcData.emplace_back(DBClientEntry("creaturespelldata", g_creatureSpellDataDB, 271));
    m_dbcData.emplace_back(DBClientEntry("creaturetype", g_creatureTypeDB, 272));
    m_dbcData.emplace_back(DBClientEntry("currencytypes", g_currencyTypesDB, 273));
    m_dbcData.emplace_back(DBClientEntry("currencycategory", g_currencyCategoryDB, 274));
    m_dbcData.emplace_back(DBClientEntry("dancemoves", g_danceMovesDB, 275));
    m_dbcData.emplace_back(DBClientEntry("deaththudlookups", g_deathThudLookupsDB, 276));
    m_dbcData.emplace_back(DBClientEntry("destructiblemodeldata", g_destructibleModelDataDB, 277));
    m_dbcData.emplace_back(DBClientEntry("dungeonencounter", g_dungeonEncounterDB, 278));
    m_dbcData.emplace_back(DBClientEntry("dungeonmap", g_dungeonMapDB, 279));
    m_dbcData.emplace_back(DBClientEntry("dungeonmapchunk", g_dungeonMapChunkDB, 280));
    m_dbcData.emplace_back(DBClientEntry("durabilitycosts", g_durabilityCostsDB, 281));
    m_dbcData.emplace_back(DBClientEntry("durabilityquality", g_durabilityQualityDB, 282));
    m_dbcData.emplace_back(DBClientEntry("emotes", g_emotesDB, 283));
    m_dbcData.emplace_back(DBClientEntry("emotestext", g_emotesTextDB, 284));
    m_dbcData.emplace_back(DBClientEntry("emotestextdata", g_emotesTextDataDB, 285));
    m_dbcData.emplace_back(DBClientEntry("emotestextsound", g_emotesTextSoundDB, 286));
    m_dbcData.emplace_back(DBClientEntry("environmentaldamage", g_environmentalDamageDB, 287));
    m_dbcData.emplace_back(DBClientEntry("exhaustion", g_exhaustionDB, 288));
    m_dbcData.emplace_back(DBClientEntry("faction", g_factionDB, 289));
    m_dbcData.emplace_back(DBClientEntry("factiongroup", g_factionGroupDB, 290));
    m_dbcData.emplace_back(DBClientEntry("factiontemplate", g_factionTemplateDB, 291));
    m_dbcData.emplace_back(DBClientEntry("filedata", g_fileDataDB, 292));
    m_dbcData.emplace_back(DBClientEntry("footprinttextures", g_footprintTexturesDB, 293));
    m_dbcData.emplace_back(DBClientEntry("footstepterrainlookup", g_footstepTerrainLookupDB, 294));
    m_dbcData.emplace_back(DBClientEntry("gameobjectartkit", g_gameObjectArtKitDB, 295));
    m_dbcData.emplace_back(DBClientEntry("gameobjectdisplayinfo", g_gameObjectDisplayInfoDB, 296));
    m_dbcData.emplace_back(DBClientEntry("gametables", g_gameTablesDB, 297));
    m_dbcData.emplace_back(DBClientEntry("gametips", g_gameTipsDB, 298));
    m_dbcData.emplace_back(DBClientEntry("gemproperties", g_gemPropertiesDB, 299));
    m_dbcData.emplace_back(DBClientEntry("glyphproperties", g_glyphPropertiesDB, 300));
    m_dbcData.emplace_back(DBClientEntry("glyphslot", g_glyphSlotDB, 301));
    m_dbcData.emplace_back(DBClientEntry("gmsurveyanswers", g_GMSurveyAnswersDB, 302));
    m_dbcData.emplace_back(DBClientEntry("gmsurveycurrentsurvey", g_GMSurveyCurrentSurveyDB, 303));
    m_dbcData.emplace_back(DBClientEntry("gmsurveyquestions", g_GMSurveyQuestionsDB, 304));
    m_dbcData.emplace_back(DBClientEntry("gmsurveysurveys", g_GMSurveySurveysDB, 305));
    m_dbcData.emplace_back(DBClientEntry("gmticketcategory", g_GMTicketCategoryDB, 306));
    m_dbcData.emplace_back(DBClientEntry("groundeffectdoodad", g_groundEffectDoodadDB, 307));
    m_dbcData.emplace_back(DBClientEntry("groundeffecttexture", g_groundEffectTextureDB, 308));
    m_dbcData.emplace_back(DBClientEntry("gtbarbershopcostbase", g_gtBarberShopCostBaseDB, 309));
    m_dbcData.emplace_back(DBClientEntry("gtcombatratings", g_gtCombatRatingsDB, 310));
    m_dbcData.emplace_back(DBClientEntry("gtchancetomeleecrit", g_gtChanceToMeleeCritDB, 311));
    m_dbcData.emplace_back(DBClientEntry("gtchancetomeleecritbase", g_gtChanceToMeleeCritBaseDB, 312));
    m_dbcData.emplace_back(DBClientEntry("gtchancetospellcrit", g_gtChanceToSpellCritDB, 313));
    m_dbcData.emplace_back(DBClientEntry("gtchancetospellcritbase", g_gtChanceToSpellCritBaseDB, 314));
    m_dbcData.emplace_back(DBClientEntry("gtnpcmanacostscaler", g_gtNPCManaCostScalerDB, 315));
    m_dbcData.emplace_back(DBClientEntry("gtoctclasscombatratingscalar", g_gtOCTClassCombatRatingScalarDB, 316));
    m_dbcData.emplace_back(DBClientEntry("gtoctregenhp", g_gtOCTRegenHPDB, 317));
    m_dbcData.emplace_back(DBClientEntry("gtoctregenmp", g_gtOCTRegenMPDB, 318));
    m_dbcData.emplace_back(DBClientEntry("gtregenhpperspt", g_gtRegenHPPerSptDB, 319));
    m_dbcData.emplace_back(DBClientEntry("gtregenmpperspt", g_gtRegenMPPerSptDB, 320));
    m_dbcData.emplace_back(DBClientEntry("helmetgeosetvisdata", g_helmetGeosetVisDataDB, 321));
    m_dbcData.emplace_back(DBClientEntry("holidaydescriptions", g_holidayDescriptionsDB, 322));
    m_dbcData.emplace_back(DBClientEntry("holidaynames", g_holidayNamesDB, 323));
    m_dbcData.emplace_back(DBClientEntry("holidays", g_holidaysDB, 324));
    m_dbcData.emplace_back(DBClientEntry("item", g_itemDB, 325));
    m_dbcData.emplace_back(DBClientEntry("itembagfamily", g_itemBagFamilyDB, 326));
    m_dbcData.emplace_back(DBClientEntry("itemclass", g_itemClassDB, 327));
    m_dbcData.emplace_back(DBClientEntry("itemcondextcosts", g_itemCondExtCostsDB, 328));
    m_dbcData.emplace_back(DBClientEntry("itemdisplayinfo", g_itemDisplayInfoDB, 329));
    m_dbcData.emplace_back(DBClientEntry("itemextendedcost", g_itemExtendedCostDB, 330));
    m_dbcData.emplace_back(DBClientEntry("itemgroupsounds", g_itemGroupSoundsDB, 331));
    m_dbcData.emplace_back(DBClientEntry("itemlimitcategory", g_itemLimitCategoryDB, 332));
    m_dbcData.emplace_back(DBClientEntry("itempetfood", g_itemPetFoodDB, 333));
    m_dbcData.emplace_back(DBClientEntry("itempurchasegroup", g_itemPurchaseGroupDB, 334));
    m_dbcData.emplace_back(DBClientEntry("itemrandomproperties", g_itemRandomPropertiesDB, 335));
    m_dbcData.emplace_back(DBClientEntry("itemrandomsuffix", g_itemRandomSuffixDB, 336));
    m_dbcData.emplace_back(DBClientEntry("itemset", g_itemSetDB, 337));
    m_dbcData.emplace_back(DBClientEntry("itemsubclass", g_itemSubClassDB, 338));
    m_dbcData.emplace_back(DBClientEntry("itemsubclassmask", g_itemSubClassMaskDB, 339));
    m_dbcData.emplace_back(DBClientEntry("itemvisualeffects", g_itemVisualEffectsDB, 340));
    m_dbcData.emplace_back(DBClientEntry("itemvisuals", g_itemVisualsDB, 341));
    m_dbcData.emplace_back(DBClientEntry("languagewords", g_languageWordsDB, 342));
    m_dbcData.emplace_back(DBClientEntry("languages", g_languagesDB, 343));
    m_dbcData.emplace_back(DBClientEntry("lfgdungeonexpansion", g_lfgDungeonExpansionDB, 344));
    m_dbcData.emplace_back(DBClientEntry("lfgdungeongroup", g_lfgDungeonGroupDB, 345));
    m_dbcData.emplace_back(DBClientEntry("lfgdungeons", g_lfgDungeonsDB, 346));
    m_dbcData.emplace_back(DBClientEntry("light", g_lightDB, 347));
    m_dbcData.emplace_back(DBClientEntry("lightfloatband", g_lightFloatBandDB, 348));
    m_dbcData.emplace_back(DBClientEntry("lightintband", g_lightIntBandDB, 349));
    m_dbcData.emplace_back(DBClientEntry("lightparams", g_lightParamsDB, 350));
    m_dbcData.emplace_back(DBClientEntry("lightskybox", g_lightSkyboxDB, 351));
    m_dbcData.emplace_back(DBClientEntry("liquidtype", g_liquidTypeDB, 352));
    m_dbcData.emplace_back(DBClientEntry("liquidmaterial", g_liquidMaterialDB, 353));
    m_dbcData.emplace_back(DBClientEntry("loadingscreens", g_loadingScreensDB, 354));
    m_dbcData.emplace_back(DBClientEntry("loadingscreentaxisplines", g_loadingScreenTaxiSplinesDB, 355));
    m_dbcData.emplace_back(DBClientEntry("lock", g_lockDB, 356));
    m_dbcData.emplace_back(DBClientEntry("locktype", g_lockTypeDB, 357));
    m_dbcData.emplace_back(DBClientEntry("mailtemplate", g_mailTemplateDB, 358));
    m_dbcData.emplace_back(DBClientEntry("map", g_mapDB, 359));
    m_dbcData.emplace_back(DBClientEntry("mapdifficulty", g_mapDifficultyDB, 360));
    m_dbcData.emplace_back(DBClientEntry("material", g_materialDB, 361));
    m_dbcData.emplace_back(DBClientEntry("movie", g_movieDB, 362));
    m_dbcData.emplace_back(DBClientEntry("moviefiledata", g_movieFileDataDB, 363));
    m_dbcData.emplace_back(DBClientEntry("movievariation", g_movieVariationDB, 364));
    m_dbcData.emplace_back(DBClientEntry("namegen", g_nameGenDB, 365));
    m_dbcData.emplace_back(DBClientEntry("npcsounds", g_NPCSoundsDB, 366));
    m_dbcData.emplace_back(DBClientEntry("namesprofanity", g_namesProfanityDB, 367));
    m_dbcData.emplace_back(DBClientEntry("namesreserved", g_namesReservedDB, 368));
    m_dbcData.emplace_back(DBClientEntry("overridespelldata", g_overrideSpellDataDB, 369));
    m_dbcData.emplace_back(DBClientEntry("package", g_packageDB, 370));
    m_dbcData.emplace_back(DBClientEntry("pagetextmaterial", g_pageTextMaterialDB, 371));
    m_dbcData.emplace_back(DBClientEntry("paperdollitemframe", g_paperDollItemFrameDB, 372));
    m_dbcData.emplace_back(DBClientEntry("particlecolor", g_particleColorDB, 373));
    m_dbcData.emplace_back(DBClientEntry("petpersonality", g_petPersonalityDB, 374));
    m_dbcData.emplace_back(DBClientEntry("powerdisplay", g_powerDisplayDB, 375));
    m_dbcData.emplace_back(DBClientEntry("pvpdifficulty", g_pvpDifficultyDB, 376));
    m_dbcData.emplace_back(DBClientEntry("questfactionreward", g_questFactionRewardDB, 377));
    m_dbcData.emplace_back(DBClientEntry("questinfo", g_questInfoDB, 378));
    m_dbcData.emplace_back(DBClientEntry("questsort", g_questSortDB, 379));
    m_dbcData.emplace_back(DBClientEntry("questxp", g_questXPDB, 380));
    m_dbcData.emplace_back(DBClientEntry("resistances", g_resistancesDB, 381));
    m_dbcData.emplace_back(DBClientEntry("randproppoints", g_randPropPointsDB, 382));
    m_dbcData.emplace_back(DBClientEntry("scalingstatdistribution", g_scalingStatDistributionDB, 383));
    m_dbcData.emplace_back(DBClientEntry("scalingstatvalues", g_scalingStatValuesDB, 384));
    m_dbcData.emplace_back(DBClientEntry("screeneffect", g_screenEffectDB, 385));
    m_dbcData.emplace_back(DBClientEntry("servermessages", g_serverMessagesDB, 386));
    m_dbcData.emplace_back(DBClientEntry("sheathesoundlookups", g_sheatheSoundLookupsDB, 387));
    m_dbcData.emplace_back(DBClientEntry("skillcostsdata", g_skillCostsDataDB, 388));
    m_dbcData.emplace_back(DBClientEntry("skilllineability", g_skillLineAbilityDB, 389));
    m_dbcData.emplace_back(DBClientEntry("skilllinecategory", g_skillLineCategoryDB, 390));
    m_dbcData.emplace_back(DBClientEntry("skillline", g_skillLineDB, 391));
    m_dbcData.emplace_back(DBClientEntry("skillraceclassinfo", g_skillRaceClassInfoDB, 392));
    m_dbcData.emplace_back(DBClientEntry("skilltiers", g_skillTiersDB, 393));
    m_dbcData.emplace_back(DBClientEntry("soundambience", g_soundAmbienceDB, 394));
    m_dbcData.emplace_back(DBClientEntry("soundemitters", g_soundEmittersDB, 395));
    m_dbcData.emplace_back(DBClientEntry("soundentries", g_soundEntriesDB, 396));
    m_dbcData.emplace_back(DBClientEntry("soundproviderpreferences", g_soundProviderPreferencesDB, 397));
    m_dbcData.emplace_back(DBClientEntry("soundsamplepreferences", g_soundSamplePreferencesDB, 398));
    m_dbcData.emplace_back(DBClientEntry("soundwatertype", g_soundWaterTypeDB, 399));
    m_dbcData.emplace_back(DBClientEntry("spammessages", g_spamMessagesDB, 400));
    m_dbcData.emplace_back(DBClientEntry("spellcasttimes", g_spellCastTimesDB, 401));
    m_dbcData.emplace_back(DBClientEntry("spellcategory", g_spellCategoryDB, 402));
    m_dbcData.emplace_back(DBClientEntry("spellchaineffects", g_spellChainEffectsDB, 403));
    m_dbcData.emplace_back(DBClientEntry("spell", g_spellDB, 404));
    m_dbcData.emplace_back(DBClientEntry("spelldescriptionvariables", g_spellDescriptionVariablesDB, 405));
    m_dbcData.emplace_back(DBClientEntry("spelldifficulty", g_spellDifficultyDB, 406));
    m_dbcData.emplace_back(DBClientEntry("spelldispeltype", g_spellDispelTypeDB, 407));
    m_dbcData.emplace_back(DBClientEntry("spellduration", g_spellDurationDB, 408));
    m_dbcData.emplace_back(DBClientEntry("spelleffectcamerashakes", g_spellEffectCameraShakesDB, 409));
    m_dbcData.emplace_back(DBClientEntry("spellfocusobject", g_spellFocusObjectDB, 410));
    m_dbcData.emplace_back(DBClientEntry("spellicon", g_spellIconDB, 411));
    m_dbcData.emplace_back(DBClientEntry("spellitemenchantment", g_spellItemEnchantmentDB, 412));
    m_dbcData.emplace_back(DBClientEntry("spellitemenchantmentcondition", g_spellItemEnchantmentConditionDB, 413));
    m_dbcData.emplace_back(DBClientEntry("spellmechanic", g_spellMechanicDB, 414));
    m_dbcData.emplace_back(DBClientEntry("spellmissile", g_spellMissileDB, 415));
    m_dbcData.emplace_back(DBClientEntry("spellmissilemotion", g_spellMissileMotionDB, 416));
    m_dbcData.emplace_back(DBClientEntry("spellradius", g_spellRadiusDB, 417));
    m_dbcData.emplace_back(DBClientEntry("spellrange", g_spellRangeDB, 418));
    m_dbcData.emplace_back(DBClientEntry("spellrunecost", g_spellRuneCostDB, 419));
    m_dbcData.emplace_back(DBClientEntry("spellshapeshiftform", g_spellShapeshiftFormDB, 420));
    m_dbcData.emplace_back(DBClientEntry("spellvisual", g_spellVisualDB, 421));
    m_dbcData.emplace_back(DBClientEntry("spellvisualeffectname", g_spellVisualEffectNameDB, 422));
    m_dbcData.emplace_back(DBClientEntry("spellvisualkit", g_spellVisualKitDB, 423));
    m_dbcData.emplace_back(DBClientEntry("spellvisualkitareamodel", g_spellVisualKitAreaModelDB, 424));
    m_dbcData.emplace_back(DBClientEntry("spellvisualkitmodelattach", g_spellVisualKitModelAttachDB, 425));
    m_dbcData.emplace_back(DBClientEntry("stableslotprices", g_stableSlotPricesDB, 426));
    m_dbcData.emplace_back(DBClientEntry("stationery", g_stationeryDB, 427));
    m_dbcData.emplace_back(DBClientEntry("stringlookups", g_stringLookupsDB, 428));
    m_dbcData.emplace_back(DBClientEntry("summonproperties", g_summonPropertiesDB, 429));
    m_dbcData.emplace_back(DBClientEntry("talent", g_talentDB, 430));
    m_dbcData.emplace_back(DBClientEntry("talenttab", g_talentTabDB, 431));
    m_dbcData.emplace_back(DBClientEntry("taxinodes", g_taxiNodesDB, 432));
    m_dbcData.emplace_back(DBClientEntry("taxipath", g_taxiPathDB, 433));
    m_dbcData.emplace_back(DBClientEntry("taxipathnode", g_taxiPathNodeDB, 434));
    m_dbcData.emplace_back(DBClientEntry("teamcontributionpoints", g_teamContributionPointsDB, 435));
    m_dbcData.emplace_back(DBClientEntry("terraintype", g_terrainTypeDB, 436));
    m_dbcData.emplace_back(DBClientEntry("terraintypesounds", g_terrainTypeSoundsDB, 437));
    m_dbcData.emplace_back(DBClientEntry("totemcategory", g_totemCategoryDB, 438));
    m_dbcData.emplace_back(DBClientEntry("transportanimation", g_transportAnimationDB, 439));
    m_dbcData.emplace_back(DBClientEntry("transportphysics", g_transportPhysicsDB, 440));
    m_dbcData.emplace_back(DBClientEntry("transportrotation", g_transportRotationDB, 441));
    m_dbcData.emplace_back(DBClientEntry("uisoundlookups", g_UISoundLookupsDB, 442));
    m_dbcData.emplace_back(DBClientEntry("unitblood", g_unitBloodDB, 443));
    m_dbcData.emplace_back(DBClientEntry("unitbloodlevels", g_unitBloodLevelsDB, 444));
    m_dbcData.emplace_back(DBClientEntry("vehicle", g_vehicleDB, 445));
    m_dbcData.emplace_back(DBClientEntry("vehicleseat", g_vehicleSeatDB, 446));
    m_dbcData.emplace_back(DBClientEntry("vehicleuiindicator", g_vehicleUIIndicatorDB, 447));
    m_dbcData.emplace_back(DBClientEntry("vehicleuiindseat", g_vehicleUIIndSeatDB, 448));
    m_dbcData.emplace_back(DBClientEntry("vocaluisounds", g_vocalUISoundsDB, 449));
    m_dbcData.emplace_back(DBClientEntry("wmoareatable", g_WMOAreaTableDB, 450));
    m_dbcData.emplace_back(DBClientEntry("weaponimpactsounds", g_weaponImpactSoundsDB, 451));
    m_dbcData.emplace_back(DBClientEntry("weaponswingsounds2", g_weaponSwingSounds2DB, 452));
    m_dbcData.emplace_back(DBClientEntry("weather", g_weatherDB, 453));
    m_dbcData.emplace_back(DBClientEntry("worldmaparea", g_worldMapAreaDB, 454));
    m_dbcData.emplace_back(DBClientEntry("worldmaptransforms", g_worldMapTransformsDB, 455));
    m_dbcData.emplace_back(DBClientEntry("worldnapcontinent", g_worldMapContinentDB, 456));
    m_dbcData.emplace_back(DBClientEntry("worldmapoverlay", g_worldMapOverlayDB, 457));
    m_dbcData.emplace_back(DBClientEntry("worldsafelocs", g_worldSafeLocsDB, 458));
    m_dbcData.emplace_back(DBClientEntry("worldstateui", g_worldStateUIDB, 459));
    m_dbcData.emplace_back(DBClientEntry("zoneintromusictable", g_zoneIntroMusicTableDB, 460));
    m_dbcData.emplace_back(DBClientEntry("zonemusic", g_zoneMusicDB, 461));
    m_dbcData.emplace_back(DBClientEntry("worldstatezonesounds", g_worldStateZoneSoundsDB, 462));
    m_dbcData.emplace_back(DBClientEntry("worldchunksounds", g_worldChunkSoundsDB, 463));
    m_dbcData.emplace_back(DBClientEntry("soundentriesadvanced", g_soundEntriesAdvancedDB, 464));
    m_dbcData.emplace_back(DBClientEntry("objecteffect", g_objectEffectDB, 465));
    m_dbcData.emplace_back(DBClientEntry("objecteffectgroup", g_objectEffectGroupDB, 466));
    m_dbcData.emplace_back(DBClientEntry("objecteffectmodifier", g_objectEffectModifierDB, 467));
    m_dbcData.emplace_back(DBClientEntry("objecteffectpackage", g_objectEffectPackageDB, 468));
    m_dbcData.emplace_back(DBClientEntry("objecteffectpackageelem", g_objectEffectPackageElemDB, 469));
    m_dbcData.emplace_back(DBClientEntry("soundfilter", g_soundFilterDB, 470));
    m_dbcData.emplace_back(DBClientEntry("soundfilterelem", g_soundFilterElemDB, 471));
}

bool DataContainer::ReloadCDBCByName(std::string& name)
{
    bool result = false;

    Util::StringToLower(name);

#if LFGROLES_DBC
    if (name == "lfgroles")
    {
        UnloadLFGRolesDB();
        LoadLFGRolesDB();

        result = true;
    }
#endif

#if SPELLATTRIBUTESEXTENDED_DBC
    if (name == "spellattributesextended")
    {
        UnloadSpellAttributesExtendedDB();
        LoadSpellAttributesExtendedDB();

        result = true;
    }
#endif

#if OCCLUSIONVOLUME_DBC
    if (name == "occlusionvolume" || name == "occlusionvolumepoint")
    {
        ClearOcclusionVolume();
        UnloadOcclusionVolumePointDB();
        UnloadOcclusionVolumeDB();
        LoadOcclusionVolumeDB();
        LoadOcclusionVolumePointDB();
        OcclusionVolumeData::FillOcclusionVolumeData();

        result = true;
    }
#endif

#if ZONELIGHT_DBC
    if (name == "zonelight" || name == "zonelightpoint")
    {
        ClearZoneLight();
        UnloadZoneLightPointDB();
        UnloadZoneLightDB();
        LoadZoneLightDB();
        LoadZoneLightPointDB();
        ZoneLightData::FillZoneLightData();

        result = true;
    }
#endif

    return result;
}
