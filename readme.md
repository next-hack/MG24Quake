
# MG24Quake: a Quake Port to Silicon Labs EFR32MG24/MGM240 devices requiring only 276 kB RAM!

Release 2.0.

**Version 2.0 UPDATE! Now supporting the FULL retail game episodes!** 
**NOTE!** Starting from release 2.0 we have modified the PAK0.PAK data structure, so you must reconvert the PAK0.PAK (+ PAK1.PAK if you have) and then reupload it. If you don't, the game will crash. There is no check for now.

---

This is a port to two simple open-source handheld gaming consoles, based on the Sparkfun Things Plus Matter and Arduino Nano Matter boards. 
It does not require external RAM: it uses just the embedded RAM regions (256 kB +  20kB). Two external flash ICs are used to store the PAK0.PAK data file.

Based on WinQuake/SDLQuake. Port by Nicola Wrachien.

For more information visit the technical article on: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/.

For more information about running the full retail Quake, read the new article: https://next-hack.com/index.php/2024/11/02/now-even-the-full-retail-quake-version-runs-on-the-arduino-nano-matter-board-and-it-is-faster-as-well/.

## Features

 - Full Quake engine implementation
	 - Static and dynamic lightings with bilinear interpolation
	 - Gouraud shading on enemies
	 - Animated sky
	 - Turbulent surfaces (water, teleport, etc.)
	 - Underwater warp effect.
	 - Particles for smoke, blood, etc.
 - Resolution: 320 x 200 pixels (Quake default resolution)
 - Full game-logic including:
	 - Monster AI/behaviors.
	 - Teleports.
	 - Triggers.
	 - Doors.
	 - Etc.
 - Sound:
	 -  8 bit stereo, 11025 Hz.
	 - Static, ambient and dynamic sound support.
 - Console with cheats.
 - Options (saved on external flash), with keyboard remapping.
 - Savegames; full game state support.
 - All the shareware levels supported, including skill/episode selection map.
 - **NEW FROM RELEASE 2.0** Retail levels are supported as well! (Require using 32 MB flash ICs, for a total of 64 MB).
 - current demo3 timedemo score: ~29.2 fps, with instantaneous fps (1/frame time) ranging from 18.2 to 47.8 fps (note that in-game instantaneous and average framerate might be higher or lower, depending on various factors, such as scene complexity, number of used channel sounds, dynamic lights, particles, map-size, and on-screen enemies).


## Limitations
- ~~Only Shareware Quake supported. (retail version NOT supported)~~ <---- **LIMITATION REMOVED! FULL RETAIL GAME IS SUPPORTED!!!**
- No CD audio supported
- Screen size fixed. The Status bar can't be reduced/removed.
- No music. 
- No Multiplayer.


## Supported Boards
 - The Gamepad (described in [this article on next-hack.com](https://next-hack.com/index.php/2024/09/21/the-gamepad-an-open-source-diy-handheld-gaming-console)), based on [Arduino Nano Matter Community Preview Board](https://store.arduino.cc/en-hu/pages/nano-matter).
 - SparkDoom (described in [this article on next-hack.com](https://next-hack.com/index.php/2023/12/10/multiplayer-doom-on-the-sparkfun-thing-plus-matter-board/)), based on [Sparkfun Thing Plus Matter - MGM240P board](https://www.sparkfun.com/products/20270). **Note that you need 16 MB flash ICs instead of 8 MB!**
 
**You can easily add support to more boards by editing boards.h and creating new build configurations.**
 
 ## Build and programming
 
See article: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/

## PAK file upload


You need at least the shareware PAK0.PAK. Just google for it! 
If you want to support the full retail game, you must also have the retail PAK1.PAK.

1. Put the PAK0.PAK (and the PAK1.PAK for full retail game support) in the same directory of the MCUPackConverter.exe (located in Tools/MCUPackConverter/Bin/Debug/).
2. Execute MCUPackConverter.exe: this will vomit a lot of data onscreen, press any key when asked.
3. You'll find on the same directory a new file, named PAK0Conv.PAK (there will be only one big PAK0Conv.PAK file, regardless if you have PAK1.PAK as well: the files are joined). 
4. Put PAK0Conv.PAK to an SD card and rename it to PAK0.PAK.
5. Then insert the SD Card in the Display board SD card holder, and reset the device, and follow on-screen directions to start the PAK0.PAK data copy operation. Note this will take 100 seconds for flash erase + about 2s per megabyte (i.e. if you have a retail game, you will have to wait 4 minutes).

This is explained here: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/


## Changelog

V2.0:
- New features:
	- **Added full support for retail episodes.**
	- Support for 32 MB flash ICs (32 bits addressing). Total external flash size can be now as high as 1 GB.
	- Faster same-level savegame load.
	- **Speed improvement** due to possibility of caching colormap to Zone Memory and some model skins to internal flash. (Current demo3 timedemo performance is 29.2 fps).
- Bugfixes:
	- Added missing fields on some edicts. This did not increase memory consumption.
	- Fixed memory fragmentation issue (this could be triggered only by console timedemo command in Windows build, or after introducing colormap caching).
	- Fixed savegame loading issues, which might cause "internal flash memory overflow" issues.
	- Fixed oldone boss health to make it fit into a signed short.
	- Fixed SPI routines to support flash memories from BYTe semiconductor as well, which seem to have more critical timings.
	- Fixed handling of external flash addresses.
	- Fixed qcc_lip field size and sign, causing E3M2 lift not working.
	- Added a "rand()" call just after the Z_zone initialization, so that the malloc_wrapper will be called first, allocating a non-releasable block (PU_WRAP) for it at the beginning of the static zone. 
- Other changes
	- Models now use index to string and not a full string, saving a lot of internal flash.
	- Models now share the alias/brushmodel data pointers, with an union, saving 1 kB
	- The surfaceNodeIndex array has been removed. Each of its element is now inside surface_t (there were 16 unused bits due to padding), saving up to 14kB of internal flash. 
	- Increased Zone Memory by 9kB (decreased textureCacheBuffer to 20kB)
	- The first 10k cachedEdgeOffsets are temporarily stored in the textureCacheBuffer, the remaining in Z-Buffer.
	- Changed optimization flags on some files/directories, to improve code size.
	- Remove unused multiplayer code (still not being optimized out because it referenced by some arrays and some - never reached - cases in the menu.
	- Removed unused CVars and commands.
	- Improved PAK0.PAK upload speed to 500kB/s.
	  
V1.1: 
-	Bugfixes:
	-	fixed bug on particles (speed was not correct resulting to a shrunk cloud)

V1.0: Initial release.