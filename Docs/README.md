## Custom Lua functions  
###GetShapeshiftFormId  
originally added in 4.0.1, no args, returns ID of currently active shapeshift form  
###GetSpellDescription  
originally added in 4.0.1, spell ID as an argument, returns description of spell in current client language or nil if spell doesn't exist  
###FindSpellActionBarSlots  
spell ID as an argument, multi-return, returns all action bar slots spell is found in (so up to 144 return values lol) or nil if spell is not placed on any action bar or unknown  
###ReplaceActionBarSpell  
args: oldSpellID, newSpellID; replaces spell on action bar with another spell if both spell IDs are known  
###SetSpellInActionBarSlot  
args: spellID, slotNumber; adds spell (if known) to action bar slot  
###ReloadMap  
no args; reloads currently loaded map for active player and returns string if active player is valid, otherwise returns nil  
