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
  
## Custom DBCs  
`.cdbc` file extension is purely cosmetic, just to make it easier to distinguish between stock client dbcs and custom ones. Default files will be provided in `Custom DBCs` directory.  
### LFGRoles.cdbc  
Dehardcodes class roles from Wow.exe, moving the whole table to DBC file. Record contains 2 columns, ClassID and RoleMask.  
