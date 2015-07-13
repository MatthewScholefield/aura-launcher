# About
Aura Launcher is an aesthetically pleasing homebrew launcher based off of DevkitPro's hbmenu which can be used to replace the menu on several DS flashcards. Read more about the core of the launcher [on the hbmenu page][hbmenu].

# Installation
To try out the launcher, place `Aura Launcher.nds` in the root of your card and start it like you would any other homebrew. To replace it as your default launcher, copy the contents of the install folder to the root of your SD card (Overwriting duplicate files).

# Compatible Flash Cards
Currently the following cards are supported:
- Original R4
- EZ Flash 5
- DSTT
- Acekard 2(i)

Many R4i knockoffs are also supported (Such as R4i SDHC and Gold) thanks to fincs, but not included in the download. To use Aura Launcher with one of those cards:

1. [Download fincs' bootstrap][fincs' blog page]
2. Copy the `_DS_MENU.DAT` and `R4.dat` files from that download to the root of the SD card
3. Copy `Aura Launcher.nds` to the root of the SD card and rename it to `_BOOT_DS.NDS`

 
[hbmenu]:https://github.com/devkitPro/nds-hb-menu
[fincs' blog page]:http://fincs.drunkencoders.com/2010/04/13/r4i-christmas-hbmenu-bootstub/
