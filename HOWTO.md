It's pretty straightforward, really:  
1. Clone repository (either download, use link or whatever is your prefered method).  
2. Run CMake (CMake gui?) to generate VS project. Set up your source and build folders then press configure until red options disappear - important to note, during configuration process `Optional platform for generator` needs to be set up to Win32. Then press `Generate`.  
3. Now you can open VS project and compile. Go to Build->Configuration Manager and set `Active solution configuration` to `Release` unless you need to debug. In `WotLKExtensions`->Header files there is `PatchConfig.h`, set whatever you want to use to true. Then select `ALL_BUILD` in Solution Explorer and press Ctrl+B.  
4. Files will be build in `[build folder you set in Cmake]/Patcher/Release` and `[build folder you set in Cmake]/WotLKExtensions/Release`.  
5. Run patcher on your Wow.exe by either dragging Wow.exe on Patcher.exe or using CLI `Patcher.exe Path/to/your/Wow.exe`. The best would be untouched Wow.exe but if you know what you're doing, do whatever. Patcher registers dll file, enables custom Glue XML edits and sets Large Address Aware flag so you don't need to.  
5. You need to copy WotLKExtensions.dll from `WotLKExtensions/Release` to the same folder your Wow.exe is.  
6. You also need to add custom DBC files to mpq archive if you use Custom DBC Manager. I assume you know how (if not, I kindly ask you what are you even doing here). Paths inside are same as in case of stock DBCs - so `DBFilesClient/[files].cdbc`  
7. ???  
8. Profit.  
