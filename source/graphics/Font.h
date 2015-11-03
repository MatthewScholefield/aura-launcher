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
	glImage *fontSprite;
	char buffer[256];
	char buffer2[256];
	
public:

	Font() { };
	int load(glImage *_font_sprite,
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
	void print(int x, int y, const char *text);
	void print(int x, int y, int value);
	void printCentered(int x, int y, const char *text);
	void printCentered(int x, int y, int value);
};