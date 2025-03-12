## Custom Lua functions  
### GetShapeshiftFormId  
originally added in 4.0.1, no args, returns ID of currently active shapeshift form  
### GetSpellDescription  
originally added in 4.0.1, spell ID as argument, returns description of spell in current client language or nil if spell doesn't exist  
### GetSpellNameById  
spell ID as argument, returns spell name and spell subtext (usually used as rank) if spell exists, nil otherwise
### FindSpellActionBarSlots  
spell ID as an argument, multi-return, returns all action bar slots spell is found in (so up to 144 return values lol) or nil if spell is not placed on any action bar or unknown  
### ReplaceActionBarSpell  
args: oldSpellID, newSpellID; replaces spell on action bar with another spell if both spell IDs are known  
### SetSpellInActionBarSlot  
args: spellID, slotNumber; adds spell (if known) to action bar slot  
### ReloadMap  
no args, nil return; reloads currently loaded map for active player  
### FlashGameWindow  
no args, nil return; flashes taskbar icon if game window is inactive until being brought to foreground  
### ToggleDisplayNormals  
no args, nil return; turns on/off ground normals  
### ToggleGroundEffects  
no args, nil return; turns on/off ground effects like grass or small rocks  
### ToggleLiquids  
no args, nil return; turns on/off liquid surfaces and particles  
### ToggleM2  
no args, nil return; turns on/off client-side m2 objects  
### ToggleTerrain  
no args, nil return; turns on/off terrain  
### ToggleTerrainCulling  
no args, nil return; turns on/off terrain culling  
### ToggleWireframeMode  
no args, nil return; turns on/off wireframe mode  
### ToggleWMO  
no args, nil return; turns on/off WMO  
### ConvertCoordsToScreenSpace  
args: x, y, z, returns x, y, (z); converts given world coordinates to current screen position; credits to Tester for original implementation in Duskhaven branch of TSWoW  
  
## Custom DBCs  
`.cdbc` file extension is purely cosmetic, just to make it easier to distinguish between stock client dbcs and custom ones. Default files will be provided in `Custom DBCs` directory.  
### LFGRoles.cdbc  
Dehardcodes class roles from Wow.exe, moving the whole table to DBC file. Record contains 2 columns, ClassID and RoleMask.  
  
## Custom Packets  
Various new data sent to and received from server. Keep in mind, sending invalid opcode from client to server usually results with disconnect.  
### SMSG_UPDATE_CUSTOM_COMBAT_RATING  
Allows utilizing unused combat rating IDs 25-31 from DBCs. Data can be retrived using `GetCustomCombatRating(combatRating)` for raw value, and `GetCustomCombatRatingBonus(combatRating)` for percent value (going by Blizzard design, `combatRating` are actually 26-32). Adding new ratings probably requires dbc edits as well. Also, it may be a good idea to use Item mod expansion patch to allow usage of those new ratings in items (and enchants).  
[Example: server-side imlementation in TrinityCore.](https://github.com/Aleist3r-s-Org/tc-fork/compare/3.3.5...Aleist3r-s-Org:tc-fork:custom-packets-combat-ratings)  
### CMSG_TELEPORT_GRAVEYARD_REQUEST  
Allows dead players to teleport to nearest graveyard using lua function `PortGraveyard()` (unlike 4.0.1 implementation, it is not made secure function but that may change in the future).  
[Example: server-side implementation in TrinityCore.](https://github.com/Aleist3r-s-Org/tc-fork/compare/3.3.5...Aleist3r-s-Org:tc-fork:custom-packets-port-graveyard)  
