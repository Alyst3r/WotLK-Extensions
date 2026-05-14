#include <excpt.h>
#include <cstring>
#include <cstdint>
#include <Data/DBCAddresses.hpp>
#include "DBCReloader.hpp"

int load_dbc(uint32_t pObj, uint32_t dbc_base, uint32_t dbc_id) {
	// Addresses
	// Mark as not loaded
	DBClient* ploader = (DBClient*)0x00AD49D0;	// Using the spellDBC address.
	ploader->m_isLoaded = false;
	ploader->m_numRows = 0;

	// Get vtable and load function
	uintptr_t vtable = *(uintptr_t*)0x00AD49D0;		// Again, using spellDBC address to get the vtable.
	uintptr_t loadFunction = *(uintptr_t*)(vtable + 4);

	// Call the load function
	__try {
		__asm {
			push dbc_id       // Push dbc_id
			push DBCLIENT_BASE      // Push dbc_base (0x626E8C)
			mov ecx, 0x00AD49D0           // Set this pointer    ----  This is just the spellDBC address.
			mov eax, vtable
			mov eax, [eax + 4]        // Get load function address
			call eax                // Call it
		}
		//CGChat::AddChatMessage("Spell.dbc hot reloaded successfully!", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return 0;
}

// This is our own custom struct, making it easier to manage the DBC entries we want to support for hot reloading.
// Simple mapping entry for name -> (pObj, dbc_id)
struct DBCEntry {
	const char* name;
	uint32_t pObj;
	uint32_t dbc_id;
};

// NOTE: this list is illustrative. Add entries you need. Names should match what Lua will pass.
static DBCEntry g_dbcList[] = {
	{ "achievement", DBCAddresses::ACHIEVEMENTDB, 235 },
	{ "achievement_criteria", DBCAddresses::ACHIEVEMENT_CRITERIADB, 236 },
	{ "achievement_category", DBCAddresses::ACHIEVEMENT_CATEGORYDB, 237 },
	{ "animationdata", DBCAddresses::ANIMATIONDATADB, 238 },
	{ "areagroup", DBCAddresses::AREAGROUPDB, 239 },
	{ "areapoi", DBCAddresses::AREAPOIDB, 240 },
	{ "areatable", DBCAddresses::AREATABLEDB, 241 },
	{ "areatrigger", DBCAddresses::AREATRIGGERDB, 242 },
	{ "attackanimkits", DBCAddresses::ATTACKANIMKITSDB, 243 },
	{ "attackanimtypes", DBCAddresses::ATTACKANIMTYPESDB, 244 },
	{ "auctionhouse", DBCAddresses::AUCTIONHOUSEDB, 245 },
	{ "bankbagslotprices", DBCAddresses::BANKBAGSLOTPRICESDB, 246 },
	{ "bannedaddons", DBCAddresses::BANNEDADDONSDB, 247 },
	{ "barbershop_style_", DBCAddresses::BARBERSHOP_STYLE_DB, 248 },
	{ "battlemaster_list_", DBCAddresses::BATTLEMASTER_LIST_DB, 249 },
	{ "camera_shakes_", DBCAddresses::CAMERA_SHAKES_DB, 250 },
	{ "cfg_categories_", DBCAddresses::CFG_CATEGORIES_DB, 251 },
	{ "cfg_configs_", DBCAddresses::CFG_CONFIGS_DB, 252 },
	{ "char_base_info_", DBCAddresses::CHAR_BASE_INFO_DB, 253 },
	{ "char_hair_geosets_", DBCAddresses::CHAR_HAIR_GEOSETS_DB, 254 },
	{ "char_sections_", DBCAddresses::CHAR_SECTIONS_DB, 255 },
	{ "char_startout_fit_", DBCAddresses::CHAR_STARTOUT_FIT_DB, 256 },
	{ "char_titles_", DBCAddresses::CHAR_TITLES_DB, 257 },
	{ "character_facial_hairstyles_", DBCAddresses::CHARACTER_FACIAL_HAIRSTYLES_DB, 258 },
	{ "chat_channels_", DBCAddresses::CHAT_CHANNELS_DB, 259 },
	{ "chat_profanity_", DBCAddresses::CHAT_PROFANITY_DB, 260 },
	{ "chr_classes_", DBCAddresses::CHR_CLASSES_DB, 261 },
	{ "chr_races_", DBCAddresses::CHR_RACES_DB, 262 },
	{ "cinematic_camera_", DBCAddresses::CINEMATIC_CAMERA_DB, 263 },
	{ "cinematic_sequences_", DBCAddresses::CINEMATIC_SEQUENCES_DB, 264 },
	{ "creature_displayinfo_", DBCAddresses::CREATURE_DISPLAYINFO_DB, 265 },
	{ "creature_displayinfo_extra_", DBCAddresses::CREATURE_DISPLAYINFO_EXTRA_DB, 266 },
	{ "creature_family_", DBCAddresses::CREATURE_FAMILY_DB, 267 },
	{ "creature_modeldata_", DBCAddresses::CREATURE_MODELDATA_DB, 268 },
	{ "creature_movementinfo_", DBCAddresses::CREATURE_MOVEMENTINFO_DB, 269 },
	{ "creature_sounddata_", DBCAddresses::CREATURE_SOUNDDATA_DB, 270 },
	{ "creature_spelldata_", DBCAddresses::CREATURE_SPELLDATA_DB, 271 },
	{ "creature_type_", DBCAddresses::CREATURE_TYPE_DB, 272 },
	{ "currency_types_", DBCAddresses::CURRENCY_TYPES_DB, 273 },
	{ "currency_category_", DBCAddresses::CURRENCY_CATEGORY_DB, 274 },
	{ "dancemoves_", DBCAddresses::DANCEMOVES_DB, 275 },
	{ "deaththud_lookups_", DBCAddresses::DEATHTHUD_LOOKUPS_DB, 276 },
	{ "destructiblemodeldata", DBCAddresses::DESTRUCTIBLEMODELDATADB, 277 },
	{ "dungeonencounter", DBCAddresses::DUNGEONENCOUNTERDB, 278 },
	{ "dungeonmap", DBCAddresses::DUNGEONMAPDB, 279 },
	{ "dungeonmapchunk", DBCAddresses::DUNGEONMAPCHUNKDB, 280 },
	{ "durabilitycosts", DBCAddresses::DURABILITYCOSTSDB, 281 },
	{ "durabilityquality", DBCAddresses::DURABILITYQUALITYDB, 282 },
	{ "emotes", DBCAddresses::EMOTESDB, 283 },
	{ "emotestext", DBCAddresses::EMOTESTEXTDB, 284 },
	{ "emotestextdata", DBCAddresses::EMOTESTEXTDATADB, 285 },
	{ "emotestextsound", DBCAddresses::EMOTESTEXTSOUNDDB, 286 },
	{ "environmentaldamage", DBCAddresses::ENVIRONMENTALDAMAGEDB, 287 },
	{ "exhaustion", DBCAddresses::EXHAUSTIONDB, 288 },
	{ "faction", DBCAddresses::FACTIONDB, 289 },
	{ "factiongroup", DBCAddresses::FACTIONGROUPDB, 290 },
	{ "factiontemplate", DBCAddresses::FACTIONTEMPLATEDB, 291 },
	{ "filedata", DBCAddresses::FILEDATADB, 292 },
	{ "footprinttextures", DBCAddresses::FOOTPRINTTEXTURESDB, 293 },
	{ "footstepterrainlookup", DBCAddresses::FOOTSTEPTERRAINLOOKUPDB, 294 },
	{ "gameobjectartkit", DBCAddresses::GAMEOBJECTARTKITDB, 295 },
	{ "gameobjectdisplayinfo", DBCAddresses::GAMEOBJECTDISPLAYINFODB, 296 },
	{ "gametables", DBCAddresses::GAMETABLESDB, 297 },
	{ "gametips", DBCAddresses::GAMETIPSDB, 298 },
	{ "gemproperties", DBCAddresses::GEMPROPERTIESDB, 299 },
	{ "glyphproperties", DBCAddresses::GLYPHPROPERTIESDB, 300 },
	{ "glyphslot", DBCAddresses::GLYPHSLOTDB, 301 },
	{ "gmsurveyanswers", DBCAddresses::GMSURVEYANSWERSDB, 302 },
	{ "gmsurveycurrentsurvey", DBCAddresses::GMSURVEYCURRENTSURVEYDB, 303 },
	{ "gmsurveyquestions", DBCAddresses::GMSURVEYQUESTIONSDB, 304 },
	{ "gmsurveysurveys", DBCAddresses::GMSURVEYSURVEYSDB, 305 },
	{ "gmticketcategory", DBCAddresses::GMTICKETCATEGORYDB, 306 },
	{ "groundeffectdoodad", DBCAddresses::GROUNDEFFECTDOODADDB, 307 },
	{ "groundeffecttexture", DBCAddresses::GROUNDEFFECTTEXTUREDB, 308 },
	{ "gtbarbershopcostbase", DBCAddresses::GTBARBERSHOPCOSTBASEDB, 309 },
	{ "gtcombatratings", DBCAddresses::GTCOMBATRATINGSDB, 310 },
	{ "gtchancetomeleecrit", DBCAddresses::GTCHANCETOMELEECRITDB, 311 },
	{ "gtchancetomeleecritbase", DBCAddresses::GTCHANCETOMELEECRITBASEDB, 312 },
	{ "gtchancetospellcrit", DBCAddresses::GTCHANCETOSPELLCRITDB, 313 },
	{ "gtchancetospellcritbase", DBCAddresses::GTCHANCETOSPELLCRITBASEDB, 314 },
	{ "gtnpcmanacostscaler", DBCAddresses::GTNPCMANACOSTSCALERDB, 315 },
	{ "gtoctclasscombatratingscalar", DBCAddresses::GTOCTCLASSCOMBATRATINGSCALARDB, 316 },
	{ "gtoctregenhp", DBCAddresses::GTOCTREGENHPDB, 317 },
	{ "gtoctregenmp", DBCAddresses::GTOCTREGENMPDB, 318 },
	{ "gtregenhpperspt", DBCAddresses::GTREGENHPPERSPTDB, 319 },
	{ "gtregenmpperspt", DBCAddresses::GTREGENMPPERSPTDB, 320 },
	{ "helmetgeosetvisdata", DBCAddresses::HELMETGEOSETVISDATADB, 321 },
	{ "holidaydescriptions", DBCAddresses::HOLIDAYDESCRIPTIONSDB, 322 },
	{ "holidaynames", DBCAddresses::HOLIDAYNAMESDB, 323 },
	{ "holidays", DBCAddresses::HOLIDAYSDB, 324 },
	{ "item", DBCAddresses::ITEMDB, 325 },
	{ "itembagfamily", DBCAddresses::ITEMBAGFAMILYDB, 326 },
	{ "itemclass", DBCAddresses::ITEMCLASSDB, 327 },
	{ "itemcondextcosts", DBCAddresses::ITEMCONDEXTCOSTSDB, 328 },
	{ "itemdisplayinfo", DBCAddresses::ITEMDISPLAYINFODB, 329 },
	{ "itemextendedcost", DBCAddresses::ITEMEXTENDEDCOSTDB, 330 },
	{ "itemgroupsounds", DBCAddresses::ITEMGROUPSOUNDSDB, 331 },
	{ "itemlimitcategory", DBCAddresses::ITEMLIMITCATEGORYDB, 332 },
	{ "itempetfood", DBCAddresses::ITEMPETFOODDB, 333 },
	{ "itempurchasegroup", DBCAddresses::ITEMPURCHASEGROUPDB, 334 },
	{ "itemrandomproperties", DBCAddresses::ITEMRANDOMPROPERTIESDB, 335 },
	{ "itemrandomsuffix", DBCAddresses::ITEMRANDOMSUFFIXDB, 336 },
	{ "itemset", DBCAddresses::ITEMSETDB, 337 },
	{ "itemsubclass", DBCAddresses::ITEMSUBCLASSDB, 338 },
	{ "itemsubclassmask", DBCAddresses::ITEMSUBCLASSMASKDB, 339 },
	{ "itemvisualeffects", DBCAddresses::ITEMVISUALEFFECTSDB, 340 },
	{ "itemvisuals", DBCAddresses::ITEMVISUALSDB, 341 },
	{ "languagewords", DBCAddresses::LANGUAGEWORDSDB, 342 },
	{ "languages", DBCAddresses::LANGUAGESDB, 343 },
	{ "lfgdungeonexpansion", DBCAddresses::LFGDUNGEONEXPANSIONDB, 344 },
	{ "lfgdungeongroup", DBCAddresses::LFGDUNGEONGROUPDB, 345 },
	{ "lfgdungeons", DBCAddresses::LFGDUNGEONSDB, 346 },
	{ "liquidtype", DBCAddresses::LIQUIDTYPEDB, 352 },
	{ "liquidmaterial", DBCAddresses::LIQUIDMATERIALDB, 353 },
	{ "loadingscreens", DBCAddresses::LOADINGSCREENSDB, 354 },
	{ "loadingscreentaxisplines", DBCAddresses::LOADINGSCREENTAXISPLINESDB, 355 },
	{ "lock", DBCAddresses::LOCKDB, 356 },
	{ "locktype", DBCAddresses::LOCKTYPEDB, 357 },
	{ "mailtemplate", DBCAddresses::MAILTEMPLATEDB, 358 },
	{ "map", DBCAddresses::MAPDB, 359 },
	{ "mapdifficulty", DBCAddresses::MAPDIFFICULTYDB, 360 },
	{ "material", DBCAddresses::MATERIALDB, 361 },
	{ "movie", DBCAddresses::MOVIEDB, 362 },
	{ "moviefiledata", DBCAddresses::MOVIEFILEDATADB, 363 },
	{ "movievariation", DBCAddresses::MOVIEVARIATIONDB, 364 },
	{ "namegen", DBCAddresses::NAMEGENDB, 365 },
	{ "npcsounds", DBCAddresses::NPCSOUNDSDB, 366 },
	{ "namesprofanity", DBCAddresses::NAMESPROFANITYDB, 367 },
	{ "namesreserved", DBCAddresses::NAMESRESERVEDDB, 368 },
	{ "overridespelldata", DBCAddresses::OVERRIDESPELLDATADB, 369 },
	{ "package", DBCAddresses::PACKAGEDB, 370 },
	{ "pagetextmaterial", DBCAddresses::PAGETEXTMATERIALDB, 371 },
	{ "paperdollitemframe", DBCAddresses::PAPERDOLLITEMFRAMEDB, 372 },
	{ "particlecolor", DBCAddresses::PARTICLECOLORDB, 373 },
	{ "petpersonality", DBCAddresses::PETPERSONALITYDB, 374 },
	{ "powerdisplay", DBCAddresses::POWERDISPLAYDB, 375 },
	{ "pvpdifficulty", DBCAddresses::PVPDIFFICULTYDB, 376 },
	{ "questfactionreward", DBCAddresses::QUESTFACTIONREWARDDB, 377 },
	{ "questinfo", DBCAddresses::QUESTINFODB, 378 },
	{ "questsort", DBCAddresses::QUESTSORTDB, 379 },
	{ "questxp", DBCAddresses::QUESTXPDB, 380 },
	{ "resistances", DBCAddresses::RESISTANCESDB, 381 },
	{ "randproppoints", DBCAddresses::RANDPROPPOINTSDB, 382 },
	{ "scalingstatdistribution", DBCAddresses::SCALINGSTATDISTRIBUTIONDB, 383 },
	{ "scalingstatvalues", DBCAddresses::SCALINGSTATVALUESDB, 384 },
	{ "screeneffect", DBCAddresses::SCREENEFFECTDB, 385 },
	{ "servermessages", DBCAddresses::SERVERMESSAGESDB, 386 },
	{ "sheathesoundlookups", DBCAddresses::SHEATHESOUNDLOOKUPSDB, 387 },
	{ "skillcostsdata", DBCAddresses::SKILLCOSTSDATADB, 388 },
	{ "skilllineability", DBCAddresses::SKILLLINEABILITYDB, 389 },
	{ "skilllinecategory", DBCAddresses::SKILLLINECATEGORYDB, 390 },
	{ "skillline", DBCAddresses::SKILLLINEDB, 391 },
	{ "skillraceclassinfo", DBCAddresses::SKILLRACECLASSINFODB, 392 },
	{ "skilltiers", DBCAddresses::SKILLTIERSDB, 393 },
	{ "soundambience", DBCAddresses::SOUNDAMBIENCEDB, 394 },
	{ "soundemitters", DBCAddresses::SOUNDEMITTERSDB, 395 },
	{ "soundentries", DBCAddresses::SOUNDENTRIESDB, 396 },
	{ "soundproviderpreferences", DBCAddresses::SOUNDPROVIDERPREFERENCESDB, 397 },
	{ "soundsamplepreferences", DBCAddresses::SOUNDSAMPLEPREFERENCESDB, 398 },
	{ "soundwatertype", DBCAddresses::SOUNDWATERTYPEDB, 399 },
	{ "spammessages", DBCAddresses::SPAMMESSAGESDB, 400 },
	{ "spellcasttimes", DBCAddresses::SPELLCASTTIMESDB, 401 },
	{ "spellcategory", DBCAddresses::SPELLCATEGORYDB, 402 },
	{ "spellchaineffects", DBCAddresses::SPELLCHAINEFFECTSDB, 403 },
	{ "spell", DBCAddresses::SPELLDB, 404 },
	{ "spelldescriptionvariables", DBCAddresses::SPELLDESCRIPTIONVARIABLESDB, 405 },
	{ "spelldifficulty", DBCAddresses::SPELLDIFFICULTYDB, 406 },
	{ "spelldispeltype", DBCAddresses::SPELLDISPELTYPEDB, 407 },
	{ "spellduration", DBCAddresses::SPELLDURATIONDB, 408 },
	{ "spelleffectcamerashakes", DBCAddresses::SPELLEFFECTCAMERASHAKESDB, 409 },
	{ "spellfocusobject", DBCAddresses::SPELLFOCUSOBJECTDB, 410 },
	{ "spellicon", DBCAddresses::SPELLICONDB, 411 },
	{ "spellitemenchantment", DBCAddresses::SPELLITEMENCHANTMENTDB, 412 },
	{ "spellitemenchantmentcondition", DBCAddresses::SPELLITEMENCHANTMENTCONDITIONDB, 413 },
	{ "spellmechanic", DBCAddresses::SPELLMECHANICDB, 414 },
	{ "spellmissile", DBCAddresses::SPELLMISSILEDB, 415 },
	{ "spellmissilemotion", DBCAddresses::SPELLMISSILEMOTIONDB, 416 },
	{ "spellradius", DBCAddresses::SPELLRADIUSDB, 417 },
	{ "spellrange", DBCAddresses::SPELLRANGEDB, 418 },
	{ "spellrunecost", DBCAddresses::SPELLRUNECOSTDB, 419 },
	{ "spellshapeshiftform", DBCAddresses::SPELLSHAPESHIFTFORMDB, 420 },
	{ "spellvisual", DBCAddresses::SPELLVISUALDB, 421 },
	{ "spellvisualeffectname", DBCAddresses::SPELLVISUALEFFECTNAMEDB, 422 },
	{ "spellvisualkit", DBCAddresses::SPELLVISUALKITDB, 423 },
	{ "spellvisualkitareamodel", DBCAddresses::SPELLVISUALKITAREAMODELDB, 424 },
	{ "spellvisualkitmodelattach", DBCAddresses::SPELLVISUALKITMODELATTACHDB, 425 },
	{ "stableslotprices", DBCAddresses::STABLESLOTPRICESDB, 426 },
	{ "stationery", DBCAddresses::STATIONERYDB, 427 },
	{ "stringlookups", DBCAddresses::STRINGLOOKUPSDB, 428 },
	{ "summonproperties", DBCAddresses::SUMMONPROPERTIESDB, 429 },
	{ "talent", DBCAddresses::TALENTDB, 430 },
	{ "talenttab", DBCAddresses::TALENTTABDB, 431 },
	{ "taxinodes", DBCAddresses::TAXINODESDB, 432 },
	{ "taxipath", DBCAddresses::TAXIPATHDB, 433 },
	{ "taxipathnode", DBCAddresses::TAXIPATHNODEDB, 434 },
	{ "teamcontributionpoints", DBCAddresses::TEAMCONTRIBUTIONPOINTSDB, 435 },
	{ "terraintype", DBCAddresses::TERRAINTYPEDB, 436 },
	{ "terraintypesounds", DBCAddresses::TERRAINTYPESOUNDSDB, 437 },
	{ "totemcategory", DBCAddresses::TOTEMCATEGORYDB, 438 },
	{ "transportanimation", DBCAddresses::TRANSPORTANIMATIONDB, 439 },
	{ "transportphysics", DBCAddresses::TRANSPORTPHYSICSDB, 440 },
	{ "transportrotation", DBCAddresses::TRANSPORTROTATIONDB, 441 },
	{ "uisoundlookups", DBCAddresses::UISOUNDLOOKUPSDB, 442 },
	{ "unitblood", DBCAddresses::UNITBLOODDB, 443 },
	{ "unitbloodlevels", DBCAddresses::UNITBLOODLEVELSDB, 444 },
	{ "vehicle", DBCAddresses::VEHICLEDB, 445 },
	{ "vehicleseat", DBCAddresses::VEHICLESEATDB, 446 },
	{ "vehicleuiindicator", DBCAddresses::VEHICLEUIINDICATORDB, 447 },
	{ "vehicleuiindseat", DBCAddresses::VEHICLEUIINDSEATDB, 448 },
	{ "vocaluisounds", DBCAddresses::VOCALUISOUNDSDB, 449 },
	{ "wmoareatable", DBCAddresses::WMOAREATABLEDB, 450 },
	{ "weaponimpactsounds", DBCAddresses::WEAPONIMPACTSOUNDSDB, 451 },
	{ "weaponswingsounds2", DBCAddresses::WEAPONSWINGSOUNDS2DB, 452 },
	{ "weather", DBCAddresses::WEATHERDB, 453 },
	{ "worldmaparea", DBCAddresses::WORLDMAPAREADB, 454 },
	{ "worldmaptransforms", DBCAddresses::WORLDMAPTRANSFORMSDB, 455 },
	{ "worldmapcontinent", DBCAddresses::WORLDMAPCONTINENTDB, 456 },
	{ "worldmapoverlay", DBCAddresses::WORLDMAPOVERLAYDB, 457 },
	{ "worldsafelocs", DBCAddresses::WORLDSAFELOCSDB, 458 },
	{ "worldstateui", DBCAddresses::WORLDSTATEUIDB, 459 },
	{ "zoneintromusictable", DBCAddresses::ZONEINTROMUSICTABLEDB, 460 },
	{ "zonemusic", DBCAddresses::ZONEMUSICDB, 461 },
	{ "worldstatezonesounds", DBCAddresses::WORLDSTATEZONESOUNDSDB, 462 },
	{ "worldchunksounds", DBCAddresses::WORLDCHUNKSOUNDSDB, 463 },
	{ "soundentriesadvanced", DBCAddresses::SOUNDENTRIESADVANCEDDB, 464 },
	{ "objecteffect", DBCAddresses::OBJECTEFFECTDB, 465 },
	{ "objecteffectgroup", DBCAddresses::OBJECTEFFECTGROUPDB, 466 },
	{ "objecteffectmodifier", DBCAddresses::OBJECTEFFECTMODIFIERDB, 467 },
	{ "objecteffectpackage", DBCAddresses::OBJECTEFFECTPACKAGEDB, 468 },
	{ "objecteffectpackageelem", DBCAddresses::OBJECTEFFECTPACKAGEELEMDB, 469 },
	{ "soundfilter", DBCAddresses::SOUNDFILTERDB, 470 },
	{ nullptr, 0, 0 }
};

int DBCReloader::ReloadDBCByName(const char* name)
{
	if (!name) return -1;

	for (int i = 0; g_dbcList[i].name != nullptr; ++i)
	{
		if (_stricmp(g_dbcList[i].name, name) == 0)
		{
			return load_dbc(g_dbcList[i].pObj, DBCLIENT_BASE, g_dbcList[i].dbc_id);
		}
	}

	return -1; // not found
}

int DBCReloader::LoadAllDBCs()
{
	load_dbc(0xAD305C, DBCLIENT_BASE, 235);
	load_dbc(0xAD3080, DBCLIENT_BASE, 236);
	load_dbc(0xAD30A4, DBCLIENT_BASE, 237);
	load_dbc(0xAD30C8, DBCLIENT_BASE, 238);
	load_dbc(0xAD30EC, DBCLIENT_BASE, 239);
	load_dbc(0xAD3110, DBCLIENT_BASE, 240);
	load_dbc(0xAD3134, DBCLIENT_BASE, 241);
	load_dbc(0xAD3158, DBCLIENT_BASE, 242);
	load_dbc(0xAD317C, DBCLIENT_BASE, 243);
	load_dbc(0xAD31A0, DBCLIENT_BASE, 244);
	load_dbc(0xAD31C4, DBCLIENT_BASE, 245);
	load_dbc(0xAD31E8, DBCLIENT_BASE, 246);
	load_dbc(0xAD320C, DBCLIENT_BASE, 247);
	load_dbc(0xAD3230, DBCLIENT_BASE, 248);
	load_dbc(0xAD3254, DBCLIENT_BASE, 249);
	load_dbc(0xAD3278, DBCLIENT_BASE, 250);
	load_dbc(0xAD329C, DBCLIENT_BASE, 251);
	load_dbc(0xAD32C0, DBCLIENT_BASE, 252);
	load_dbc(0xAD32E4, DBCLIENT_BASE, 253);
	load_dbc(0xAD3308, DBCLIENT_BASE, 254);
	load_dbc(0xAD332C, DBCLIENT_BASE, 255);
	load_dbc(0xAD3350, DBCLIENT_BASE, 256);
	load_dbc(0xAD3374, DBCLIENT_BASE, 257);
	load_dbc(0xAD3398, DBCLIENT_BASE, 258);
	load_dbc(0xAD33BC, DBCLIENT_BASE, 259);
	load_dbc(0xAD33E0, DBCLIENT_BASE, 260);
	load_dbc(0xAD3404, DBCLIENT_BASE, 261);
	load_dbc(0xAD3428, DBCLIENT_BASE, 262);
	load_dbc(0xAD344C, DBCLIENT_BASE, 263);
	load_dbc(0xAD3470, DBCLIENT_BASE, 264);
	load_dbc(0xAD34B8, DBCLIENT_BASE, 265);
	load_dbc(0xAD3494, DBCLIENT_BASE, 266);
	load_dbc(0xAD34DC, DBCLIENT_BASE, 267);
	load_dbc(0xAD3500, DBCLIENT_BASE, 268);
	load_dbc(0xAD3524, DBCLIENT_BASE, 269);
	load_dbc(0xAD3548, DBCLIENT_BASE, 270);
	load_dbc(0xAD356C, DBCLIENT_BASE, 271);
	load_dbc(0xAD3590, DBCLIENT_BASE, 272);
	load_dbc(0xAD35B4, DBCLIENT_BASE, 273);
	load_dbc(0xAD35D8, DBCLIENT_BASE, 274);
	load_dbc(0xAD35FC, DBCLIENT_BASE, 275);
	load_dbc(0xAD3620, DBCLIENT_BASE, 276);
	load_dbc(0xAD368C, DBCLIENT_BASE, 277);
	load_dbc(0xAD36B0, DBCLIENT_BASE, 278);
	load_dbc(0xAD36D4, DBCLIENT_BASE, 279);
	load_dbc(0xAD36F8, DBCLIENT_BASE, 280);
	load_dbc(0xAD371C, DBCLIENT_BASE, 281);
	load_dbc(0xAD3740, DBCLIENT_BASE, 282);
	load_dbc(0xAD3764, DBCLIENT_BASE, 283);
	load_dbc(0xAD37D0, DBCLIENT_BASE, 284);
	load_dbc(0xAD3788, DBCLIENT_BASE, 285);
	load_dbc(0xAD37AC, DBCLIENT_BASE, 286);
	load_dbc(0xAD37F4, DBCLIENT_BASE, 287);
	load_dbc(0xAD3818, DBCLIENT_BASE, 288);
	load_dbc(0xAD3860, DBCLIENT_BASE, 289);
	load_dbc(0xAD383C, DBCLIENT_BASE, 290);
	load_dbc(0xAD3884, DBCLIENT_BASE, 291);
	load_dbc(0xAD38A8, DBCLIENT_BASE, 292);
	load_dbc(0xAD38CC, DBCLIENT_BASE, 293);
	load_dbc(0xAD38F0, DBCLIENT_BASE, 294);
	load_dbc(0xAD3914, DBCLIENT_BASE, 295);
	load_dbc(0xAD3938, DBCLIENT_BASE, 296);
	load_dbc(0xAD395C, DBCLIENT_BASE, 297);
	load_dbc(0xAD3980, DBCLIENT_BASE, 298);
	load_dbc(0xAD39A4, DBCLIENT_BASE, 299);
	load_dbc(0xAD39C8, DBCLIENT_BASE, 300);
	load_dbc(0xAD39EC, DBCLIENT_BASE, 301);
	load_dbc(0xAD3A10, DBCLIENT_BASE, 302);
	load_dbc(0xAD3A34, DBCLIENT_BASE, 303);
	load_dbc(0xAD3A58, DBCLIENT_BASE, 304);
	load_dbc(0xAD3A7C, DBCLIENT_BASE, 305);
	load_dbc(0xAD3AA0, DBCLIENT_BASE, 306);
	load_dbc(0xAD3AC4, DBCLIENT_BASE, 307);
	load_dbc(0xAD3AE8, DBCLIENT_BASE, 308);
	load_dbc(0xAD3B0C, DBCLIENT_BASE, 309);
	load_dbc(0xAD3B30, DBCLIENT_BASE, 310);
	load_dbc(0xAD3B54, DBCLIENT_BASE, 311);
	load_dbc(0xAD3B78, DBCLIENT_BASE, 312);
	load_dbc(0xAD3B9C, DBCLIENT_BASE, 313);
	load_dbc(0xAD3BC0, DBCLIENT_BASE, 314);
	load_dbc(0xAD3BE4, DBCLIENT_BASE, 315);
	load_dbc(0xAD3C08, DBCLIENT_BASE, 316);
	load_dbc(0xAD3C2C, DBCLIENT_BASE, 317);
	load_dbc(0xAD3C50, DBCLIENT_BASE, 318);
	load_dbc(0xAD3C74, DBCLIENT_BASE, 319);
	load_dbc(0xAD3C98, DBCLIENT_BASE, 320);
	load_dbc(0xAD3CBC, DBCLIENT_BASE, 321);
	load_dbc(0xAD3CE0, DBCLIENT_BASE, 322);
	load_dbc(0xAD3D04, DBCLIENT_BASE, 323);
	load_dbc(0xAD3D28, DBCLIENT_BASE, 324);
	load_dbc(0xAD3D4C, DBCLIENT_BASE, 325);
	load_dbc(0xAD3D70, DBCLIENT_BASE, 326);
	load_dbc(0xAD3D94, DBCLIENT_BASE, 327);
	load_dbc(0xAD3DB8, DBCLIENT_BASE, 328);
	load_dbc(0xAD3DDC, DBCLIENT_BASE, 329);
	load_dbc(0xAD3E00, DBCLIENT_BASE, 330);
	load_dbc(0xAD3E24, DBCLIENT_BASE, 331);
	load_dbc(0xAD3E48, DBCLIENT_BASE, 332);
	load_dbc(0xAD3E6C, DBCLIENT_BASE, 333);
	load_dbc(0xAD3E90, DBCLIENT_BASE, 334);
	load_dbc(0xAD3EB4, DBCLIENT_BASE, 335);
	load_dbc(0xAD3ED8, DBCLIENT_BASE, 336);
	load_dbc(0xAD3EFC, DBCLIENT_BASE, 337);
	load_dbc(0xAD3F44, DBCLIENT_BASE, 338);
	load_dbc(0xAD3F20, DBCLIENT_BASE, 339);
	load_dbc(0xAD3F68, DBCLIENT_BASE, 340);
	load_dbc(0xAD3F8C, DBCLIENT_BASE, 341);
	load_dbc(0xAD3FB0, DBCLIENT_BASE, 342);
	load_dbc(0xAD3FD4, DBCLIENT_BASE, 343);
	load_dbc(0xAD3FF8, DBCLIENT_BASE, 344);
	load_dbc(0xAD401C, DBCLIENT_BASE, 345);
	load_dbc(0xAD4040, DBCLIENT_BASE, 346);
	load_dbc(0xAF4A28, DBCLIENT_BASE, 347);
	load_dbc(0xAF49E0, DBCLIENT_BASE, 348);
	load_dbc(0xAF49BC, DBCLIENT_BASE, 349);
	load_dbc(0xAF4A04, DBCLIENT_BASE, 350);
	load_dbc(0xAF4998, DBCLIENT_BASE, 351);
	load_dbc(0xAD4064, DBCLIENT_BASE, 352);
	load_dbc(0xAD4088, DBCLIENT_BASE, 353);
	load_dbc(0xAD40AC, DBCLIENT_BASE, 354);
	load_dbc(0xAD40D0, DBCLIENT_BASE, 355);
	load_dbc(0xAD40F4, DBCLIENT_BASE, 356);
	load_dbc(0xAD4118, DBCLIENT_BASE, 357);
	load_dbc(0xAD413C, DBCLIENT_BASE, 358);
	load_dbc(0xAD4160, DBCLIENT_BASE, 359);
	load_dbc(0xAD4184, DBCLIENT_BASE, 360);
	load_dbc(0xAD41A8, DBCLIENT_BASE, 361);
	load_dbc(0xAD41CC, DBCLIENT_BASE, 362);
	load_dbc(0xAD41F0, DBCLIENT_BASE, 363);
	load_dbc(0xAD4214, DBCLIENT_BASE, 364);
	load_dbc(0xAD4238, DBCLIENT_BASE, 365);
	load_dbc(0xAD425C, DBCLIENT_BASE, 366);
	load_dbc(0xAD4280, DBCLIENT_BASE, 367);
	load_dbc(0xAD42A4, DBCLIENT_BASE, 368);
	load_dbc(0xAD42C8, DBCLIENT_BASE, 369);
	load_dbc(0xAD42EC, DBCLIENT_BASE, 370);
	load_dbc(0xAD4310, DBCLIENT_BASE, 371);
	load_dbc(0xAD4334, DBCLIENT_BASE, 372);
	load_dbc(0xAD4358, DBCLIENT_BASE, 373);
	load_dbc(0xAD437C, DBCLIENT_BASE, 374);
	load_dbc(0xAD43A0, DBCLIENT_BASE, 375);
	load_dbc(0xAD43C4, DBCLIENT_BASE, 376);
	load_dbc(0xAD43E8, DBCLIENT_BASE, 377);
	load_dbc(0xAD440C, DBCLIENT_BASE, 378);
	load_dbc(0xAD4430, DBCLIENT_BASE, 379);
	load_dbc(0xAD4454, DBCLIENT_BASE, 380);
	load_dbc(0xAD4478, DBCLIENT_BASE, 381);
	load_dbc(0xAD449C, DBCLIENT_BASE, 382);
	load_dbc(0xAD44C0, DBCLIENT_BASE, 383);
	load_dbc(0xAD44E4, DBCLIENT_BASE, 384);
	load_dbc(0xAD4508, DBCLIENT_BASE, 385);
	load_dbc(0xAD452C, DBCLIENT_BASE, 386);
	load_dbc(0xAD4550, DBCLIENT_BASE, 387);
	load_dbc(0xAD4574, DBCLIENT_BASE, 388);
	load_dbc(0xAD4598, DBCLIENT_BASE, 389);
	load_dbc(0xAD45BC, DBCLIENT_BASE, 390);
	load_dbc(0xAD45E0, DBCLIENT_BASE, 391);
	load_dbc(0xAD4604, DBCLIENT_BASE, 392);
	load_dbc(0xAD4628, DBCLIENT_BASE, 393);
	load_dbc(0xAD464C, DBCLIENT_BASE, 394);
	load_dbc(0xAD4694, DBCLIENT_BASE, 395);
	load_dbc(0xAD4670, DBCLIENT_BASE, 396);
	load_dbc(0xAD46B8, DBCLIENT_BASE, 397);
	load_dbc(0xAD46DC, DBCLIENT_BASE, 398);
	load_dbc(0xAD4700, DBCLIENT_BASE, 399);
	load_dbc(0xAD4724, DBCLIENT_BASE, 400);
	load_dbc(0xAD4748, DBCLIENT_BASE, 401);
	load_dbc(0xAD476C, DBCLIENT_BASE, 402);
	load_dbc(0xAD4790, DBCLIENT_BASE, 403);
	load_dbc(0xAD49D0, DBCLIENT_BASE, 404);
	load_dbc(0xAD47B4, DBCLIENT_BASE, 405);
	load_dbc(0xAD47D8, DBCLIENT_BASE, 406);
	load_dbc(0xAD47FC, DBCLIENT_BASE, 407);
	load_dbc(0xAD4820, DBCLIENT_BASE, 408);
	load_dbc(0xAD4844, DBCLIENT_BASE, 409);
	load_dbc(0xAD4868, DBCLIENT_BASE, 410);
	load_dbc(0xAD488C, DBCLIENT_BASE, 411);
	load_dbc(0xAD48B0, DBCLIENT_BASE, 412);
	load_dbc(0xAD48D4, DBCLIENT_BASE, 413);
	load_dbc(0xAD48F8, DBCLIENT_BASE, 414);
	load_dbc(0xAD491C, DBCLIENT_BASE, 415);
	load_dbc(0xAD4940, DBCLIENT_BASE, 416);
	load_dbc(0xAD4964, DBCLIENT_BASE, 417);
	load_dbc(0xAD4988, DBCLIENT_BASE, 418);
	load_dbc(0xAD49AC, DBCLIENT_BASE, 419);
	load_dbc(0xAD49F4, DBCLIENT_BASE, 420);
	load_dbc(0xAD4AA8, DBCLIENT_BASE, 421);
	load_dbc(0xAD4A18, DBCLIENT_BASE, 422);
	load_dbc(0xAD4A3C, DBCLIENT_BASE, 423);
	load_dbc(0xAD4A60, DBCLIENT_BASE, 424);
	load_dbc(0xAD4A84, DBCLIENT_BASE, 425);
	load_dbc(0xAD4ACC, DBCLIENT_BASE, 426);
	load_dbc(0xAD4AF0, DBCLIENT_BASE, 427);
	load_dbc(0xAD4B14, DBCLIENT_BASE, 428);
	load_dbc(0xAD4B38, DBCLIENT_BASE, 429);
	load_dbc(0xAD4B5C, DBCLIENT_BASE, 430);
	load_dbc(0xAD4B80, DBCLIENT_BASE, 431);
	load_dbc(0xAD4BA4, DBCLIENT_BASE, 432);
	load_dbc(0xAD4BEC, DBCLIENT_BASE, 433);
	load_dbc(0xAD4BC8, DBCLIENT_BASE, 434);
	load_dbc(0xAD4C10, DBCLIENT_BASE, 435);
	load_dbc(0xAD4C34, DBCLIENT_BASE, 436);
	load_dbc(0xAD4C58, DBCLIENT_BASE, 437);
	load_dbc(0xAD4C7C, DBCLIENT_BASE, 438);
	load_dbc(0xAD4CA0, DBCLIENT_BASE, 439);
	load_dbc(0xAD4CC4, DBCLIENT_BASE, 440);
	load_dbc(0xAD4CE8, DBCLIENT_BASE, 441);
	load_dbc(0xAD4D0C, DBCLIENT_BASE, 442);
	load_dbc(0xAD4D54, DBCLIENT_BASE, 443);
	load_dbc(0xAD4D30, DBCLIENT_BASE, 444);
	load_dbc(0xAD4D78, DBCLIENT_BASE, 445);
	load_dbc(0xAD4D9C, DBCLIENT_BASE, 446);
	load_dbc(0xAD4DC0, DBCLIENT_BASE, 447);
	load_dbc(0xAD4DE4, DBCLIENT_BASE, 448);
	load_dbc(0xAD4E08, DBCLIENT_BASE, 449);
	load_dbc(0xAD4E2C, DBCLIENT_BASE, 450);
	load_dbc(0xAD4E50, DBCLIENT_BASE, 451);
	load_dbc(0xAD4E74, DBCLIENT_BASE, 452);
	load_dbc(0xAD4E98, DBCLIENT_BASE, 453);
	load_dbc(0xAD4EBC, DBCLIENT_BASE, 454);
	load_dbc(0xAD4F28, DBCLIENT_BASE, 455);
	load_dbc(0xAD4EE0, DBCLIENT_BASE, 456);
	load_dbc(0xAD4F04, DBCLIENT_BASE, 457);
	load_dbc(0xAD4F4C, DBCLIENT_BASE, 458);
	load_dbc(0xAD4F70, DBCLIENT_BASE, 459);
	load_dbc(0xAD4F94, DBCLIENT_BASE, 460);
	load_dbc(0xAD4FB8, DBCLIENT_BASE, 461);
	load_dbc(0xAD4FDC, DBCLIENT_BASE, 462);
	load_dbc(0xAD5000, DBCLIENT_BASE, 463);
	load_dbc(0xAD5024, DBCLIENT_BASE, 464);
	load_dbc(0xAD5048, DBCLIENT_BASE, 465);
	load_dbc(0xAD506C, DBCLIENT_BASE, 466);
	load_dbc(0xAD5090, DBCLIENT_BASE, 467);
	load_dbc(0xAD50B4, DBCLIENT_BASE, 468);
	load_dbc(0xAD50D8, DBCLIENT_BASE, 469);
	load_dbc(0xAD50FC, DBCLIENT_BASE, 470);
	return load_dbc(0xAD5120, DBCLIENT_BASE, 471);
}