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
#include <gl2d.h>
#include "font.h"
#include "sub_bg.h"

#include "hbmenu_banner.h"
#include "font6x8.h"
#include "../iconTitle.h"

//-------------------------------------------------------
// set up a 2D layer construced of bitmap sprites
// this holds the image when rendering to the top screen
//-------------------------------------------------------

void initSubSprites(void)
{

	oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
	int id = 0;

	//set up a 4x3 grid of 64x64 sprites to cover the screen
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 4; x++)
		{
			oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
			oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
			oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
			++id;
		}

	swiWaitForVBlank();

	oamUpdate(&oamSub);
}

void startRendering(bool top)
{
	if (top)
	{
		lcdMainOnTop();
		vramSetBankD(VRAM_D_LCD);
		vramSetBankC(VRAM_C_SUB_BG);
		REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
	}
	else
	{
		lcdMainOnBottom();
		vramSetBankC(VRAM_C_LCD);
		vramSetBankD(VRAM_D_SUB_SPRITE);
		REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
	}
}

void graphicsInit()
{
	/*// initialize video mode
	videoSetMode(MODE_4_2D);

	// initialize VRAM banks
	vramSetPrimaryBanks(VRAM_A_MAIN_BG,
						VRAM_B_MAIN_SPRITE,
						VRAM_C_LCD,
						VRAM_D_LCD);

	// initialize bg2 as a rotation background and bg3 as a bmp background
	// http://mtheall.com/vram.html#T2=3&RNT2=96&MB2=3&TB2=0&S2=2&T3=6&MB3=1&S3=1
	int bg2 = bgInit(2, BgType_Rotation, BgSize_R_512x512, 3, 0);
	int bg3 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 1, 0);

	// initialize rotate, scale, and scroll
	bgSetRotateScale(bg3, 0, 1 << 8, 1 << 8);
	bgSetScroll(bg3, 0, 0);
	bgSetRotateScale(bg2, 0, 8 * (1 << 8) / 6, 1 << 8);
	bgSetScroll(bg2, -TITLE_POS_X, -TITLE_POS_Y);

	// clear bg2's map: 512x512 pixels is 64x64 tiles is 4KB
	dmaFillHalfWords(0, bgGetMapPtr(bg2), 4096);
	// load compressed font into bg2's tile data
	decompress(font6x8Tiles, bgGetGfxPtr(bg2), LZ77Vram);

	// load compressed bitmap into bg3
	decompress(hbmenu_bannerBitmap, bgGetGfxPtr(bg3), LZ77Vram);

	// load font palette
	dmaCopy(font6x8Pal, BG_PALETTE, font6x8PalLen);

	// apply the bg changes
	bgUpdate();

	// initialize OAM
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	u16 *sprite = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
	dmaFillHalfWords(0, sprite, sizeof (u8)*512);
	oamSet(&oamMain, 0, ICON_POS_X, ICON_POS_Y, 0, 0,
		SpriteSize_32x32, SpriteColorFormat_16Color, sprite,
		-1, 0, 0, 0, 0, 0);

	// oam can only be updated during vblank
	swiWaitForVBlank();
	oamUpdate(&oamMain);

	iconTitleInit(bg2, bg3, sprite);*/

	////////////////////////////////////////////////////////////
	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	// Initialize OAM to capture 3D scene
	initSubSprites();

	// The sub background holds the top image when 3D directed to bottom
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	// Initialize GL in 3D mode
	glScreen2D();

	// Set up enough texture memory for our textures
	// Bank A is just 128kb and we are using 194 kb of
	// sprites
	//vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankB(VRAM_B_TEXTURE);
	vramSetBankF(VRAM_F_TEX_PALETTE); // Allocate VRAM bank for all the palettes

	//vramSetBankE(VRAM_E_MAIN_BG); // Main bg text/8bit bg. Bank E size == 64kb, exactly enough for 8bit * 256 * 192 + text layer
}

/*void fontInit()
{
	consoleDemoInit();
	return;
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
}*/