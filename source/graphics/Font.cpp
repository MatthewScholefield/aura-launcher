/******************************************************************************
 *******************************************************************************
	A simple font class for Easy GL2D DS created by:

	Relminator (Richard Eric M. Lope BSN RN)
	Http://Rel.Phatcode.Net

 *******************************************************************************
 ******************************************************************************/

#include <nds.h>
#include <stdio.h>
#include <gl2d.h>
#include "Font.h"

int Font::Load(glImage *_font_sprite,
				  const unsigned int numframes,
				  const unsigned int *texcoords,
				  GL_TEXTURE_TYPE_ENUM type,
				  int sizeX,
				  int sizeY,
				  int param,
				  int pallette_width,
				  const u16 *palette,
				  const uint8 *texture
				  )

{
	font_sprite = _font_sprite;

	int textureID =
			glLoadSpriteSet(font_sprite,
							numframes,
							texcoords,
							type,
							sizeX,
							sizeY,
							param,
							pallette_width,
							palette,
							texture
							);

	return textureID;

}

void Font::Print(int x, int y, const char *text)
{
	unsigned char font_char;

	while (*text)
	{
		font_char = (*(unsigned char*) text++) - 32;
		glSprite(x, y, GL_FLIP_NONE, &font_sprite[font_char]);
		x += font_sprite[font_char].width;
	}
}

void Font::Print(int x, int y, int value)
{
	sprintf(str, "%i", value);
	Print(x, y, str);
}

void Font::PrintCentered(int x, int y, const char *text)
{

	unsigned char font_char;
	int total_width = 0;
	char *o_text = (char*) text;

	while (*text)
	{
		font_char = (*(unsigned char*) text++) - 32;
		total_width += font_sprite[font_char].width;
	}

	x = (SCREEN_WIDTH - total_width) / 2;

	text = o_text;
	while (*text)
	{
		font_char = (*(unsigned char*) text++) - 32;
		glSprite(x, y, GL_FLIP_NONE, &font_sprite[font_char]);
		x += font_sprite[font_char].width;
	}

}

void Font::PrintCentered(int x, int y, int value)
{
	sprintf(str, "%i", value);
	PrintCentered(x, y, str);
}