# MG24Quake: a Quake Port to Silicon Labs EFR32MG24/MGM240 devices requiring only 276 kB RAM!

This is a port to two simple open-source handheld gaming consoles, based on the Sparkfun Things Plus Matter and Arduino Nano Matter boards. 
It does not require external RAM: it uses just the embedded RAM regions (256 kB +  20kB). Two external flash ICs are used to store the PAK0.PAK data file.

Based on WinQuake/SDLQuake. Port by Nicola Wrachien.

For more information visit the technical article on: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/.

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
 - demo3 timedemo score: 28.0 fps, with instantaneous fps (1/frame time) ranging from 17.7 to 45.6 fps (note that in-game instantaneous and average framerate might be higher or lower, depending on various factors, such as scene complexity, number of used channel sounds, dynamic lights, particles, map-size, and on-screen enemies).


## Limitations
- Only Shareware Quake supported. (retail version NOT supported)
- No CD audio supported
- Screen size fixed. The Status bar can't be reduced/removed.
- No music. 


## Supported Boards
 - The Gamepad (described in [this article on next-hack.com](https://next-hack.com/index.php/2024/09/21/the-gamepad-an-open-source-diy-handheld-gaming-console)), based on [Arduino Nano Matter Community Preview Board](https://store.arduino.cc/en-hu/pages/nano-matter).
 - SparkDoom (described in [this article on next-hack.com](https://next-hack.com/index.php/2023/12/10/multiplayer-doom-on-the-sparkfun-thing-plus-matter-board/)), based on [Sparkfun Thing Plus Matter - MGM240P board](https://www.sparkfun.com/products/20270). **Note that you need 16 MB flash ICs instead of 8 MB!**
 
**You can easily add support to more boards by editing boards.h and creating new build configurations.**
 
 ## Build and programming
 
See article: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/

## PAK file upload

You need the shareware PAK0.PAK. Just google for it!
After you have downloaded it, you must use the utility in Tools/MCUPackConverter/Bin/Debug/ to convert it so that it can be used by this port. This is explained here: https://next-hack.com/index.php/2024/09/22/quake-port-to-sparkfun-and-arduino-nano-matter-boards-using-only-276-kb-ram/
