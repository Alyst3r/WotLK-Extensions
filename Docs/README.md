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
no args; reloads currently loaded map for active player and returns string if active player is valid, otherwise returns nil  
### FlashGameWindow  
no args; flashes taskbar icon if game window is inactive until being brought to foreground  
