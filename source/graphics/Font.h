/******************************************************************************
 *******************************************************************************
	A simple font class for Easy GL2D DS created by:

	Relminator (Richard Eric M. Lope BSN RN)
	Http://Rel.Phatcode.Net

 *******************************************************************************
 ******************************************************************************/

#pragma once

class Font
{
private:
	glImage *font_sprite;
	char str[256];
	char str2[256];
	
public:

	Font() { };
	int Load(glImage *_font_sprite,
			const unsigned int numframes,
			const unsigned int *texcoords,
			GL_TEXTURE_TYPE_ENUM type,
			int sizeX,
			int sizeY,
			int param,
			int pallette_width,
			const u16 *palette,
			const uint8 *texture
			);
	void Print(int x, int y, const char *text);
	void Print(int x, int y, int value);
	void PrintCentered(int x, int y, const char *text);
	void PrintCentered(int x, int y, int value);
};