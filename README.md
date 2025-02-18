# WotLK-Extensions
Client extension project, independent from TSWoW.  
  
Cmake files based on TSWoW's [ClientExtensions](https://github.com/tswow/tswow/tree/master/misc/client-extensions)  
  
### Patcher.exe
In essence, it's [WoWFix335](https://github.com/robinsch/WoWFix335) by Robinsch, so most credits to him.  
  
Most of patch content should probably be credited to FrostAtom, [AwesomeWotlk](https://github.com/FrostAtom/awesome_wotlk/blob/main/src/AwesomeWotlkPatch/Patch.h) is where I've got dll loading from.  
  
Exe header data recalculated using [CFF Explorer VIII](https://ntcore.com/explorer-suite/).  
  
### WotLKExtensions.dll
Various runtime patches, as well as functionality extensions, all configurable from *PatchConfig.h* file.  
  
**Patches:**  
+ No Ammo - disables ammo requirement for ranged weapons; may require server core edits to fix ammo display (if not edited, without ammo in ammo slot weapons will shot invisible arrows/bullets)  
+ More than 21 races crashfix - self-explanatory, allows to have up to 31 playable races in creation screen without crashes upon selecting them  
+ Combo point fix - allows every class to utilise combo points  
+ More than 12 classes in LFD - original role table stores only 12 (technically 13 if you count ID == 0) class bytes representing LFD roles, this patch expands it to 31
