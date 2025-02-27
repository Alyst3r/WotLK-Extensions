# WotLK-Extensions  
Client extension project, independent from TSWoW.  
  
Cmake files based on TSWoW's [ClientExtensions](https://github.com/tswow/tswow/tree/master/misc/client-extensions)  
  
### Patcher.exe  
In essence, it's [WoWFix335](https://github.com/robinsch/WoWFix335) by Robinsch, so most credits to him.  
  
Most of patch content should probably be credited to FrostAtom, [AwesomeWotlk](https://github.com/FrostAtom/awesome_wotlk/blob/main/src/AwesomeWotlkPatch/Patch.h) is where I've got dll loading from.  
  
Exe header data recalculated using [CFF Explorer VIII](https://ntcore.com/explorer-suite/).  
  
### WotLKExtensions.dll  
Various runtime patches, as well as functionality extensions, all configurable from *PatchConfig.h* file. **By default all of the patches are turned off!**  
Will be periodically updated, obviously (but no promises how ofted, depends on various factors).  
  
**Patches:**  
+ No Ammo - disables ammo requirement for ranged weapons; may require server core edits to fix ammo display (if not edited, without ammo in ammo slot weapons will shot invisible arrows/bullets); requires core edit to patch out server side `Out of Ammo` error message  
+ More than 21 races crashfix - self-explanatory, allows to have up to 31 playable races in creation screen without crashes upon selecting them  
+ Combo point fix - allows every class to utilise combo points  
+ More than 12 classes in LFD - original role table stores only 12 (technically 13 if you count ID == 0) class bytes representing LFD roles, this patch expands it to 31  
  
**Custom Lua Functions**
Various new or backported Lua functions - see `Docs` directory for further details.  
  
**Custom DBC Manager**  
What started as a code written in assembly sparked an idea of writing openly available DBC loader that's already in use by Duskhaven, being ported to main TSWoW repository, and now added to this project. For now, only one new DBC file is added but there are some more ideas floating around. See `Docs` directory for more info.  
  
### Credits/Acknowledgements  
In no particular order:  
[Tester](https://github.com/TesterWoWDev) - huge help with DBC manager, as well as various other things  
[Robinsch](https://github.com/robinsch) - patcher code, various client patches  
[Nix](https://github.com/NixAJ)  
[Deamon](https://github.com/Deamon87)  
[Natrist](https://github.com/natrist) - (see, it is possible to release smth :P)  
[DrFrugal (aka 4bhorrent)](https://drfrugal.xyz/)  
[Titi](https://gitlab.com/T1ti) - some ideas what to add (for example, dehardcoding lfg roles from Wow.exe)  
[M'Dic](https://github.com/acidmanifesto) - c'mon, who wouldn't  
[I'm probably forgetting a bunch of people, I will add you when I remember](https://github.com/Alyst3r/WotLK-Extensions)  
