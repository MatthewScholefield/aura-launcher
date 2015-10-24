/*-----------------------------------------------------------------
 Copyright (C) 2015
	Matthew Scholefield

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

------------------------------------------------------------------*/

#include <nds.h>
#include "font.h"
#include "sub_bg.h"

void graphicsInit()
{
	videoSetModeSub(MODE_5_2D | DISPLAY_BG_EXT_PALETTE);
	vramSetBankC(VRAM_C_SUB_BG);
	int subBgID = bgInitSub(2, BgType_ExRotation, BgSize_ER_512x512, 10, 2);
	bgWrapOn(subBgID);
	vramSetBankH(VRAM_H_LCD);
	dmaCopy(sub_bgPal, VRAM_H_EXT_PALETTE[2][0], sub_bgPalLen);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	dmaCopy(sub_bgTiles, bgGetGfxPtr(subBgID), sub_bgTilesLen);

	uint16 *bgptr = bgGetMapPtr(subBgID);
	for (int i = 0; i < 32; ++i)
		for (int j = 0; j < 24; ++j)
			bgptr[i + j * 64] = i + j * 32;
}

void fontInit()
{
	PrintConsole *console = consoleInit(NULL, 0, BgType_Text8bpp, BgSize_T_512x256, 8, 0, false, false);
	ConsoleFont font;
	font.gfx = (u16*) fontTiles;
	font.pal = (u16*) fontPal;
	font.numChars = 256;
	font.numColors = fontPalLen / 2;
	font.bpp = 8;
	font.asciiOffset = 0;
	font.convertSingleColor = false;
	consoleSetFont(console, &font);
	vramSetBankH(VRAM_H_LCD);
	dmaCopy(&fontPal, VRAM_H_EXT_PALETTE[0][0], fontPalLen); //Copy the palette
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	dmaCopy(&fontTiles, (uint16*) 0x0620400, fontTilesLen);
}