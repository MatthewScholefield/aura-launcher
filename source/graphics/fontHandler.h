#pragma once

class TextEntry
{
public:
	static const int ACTIVE = 0;
	static const int COMPLETE = -1;
	static const int PRECISION = 10;

	bool large;
	bool immune; //Does not clear
	bool fade;
	int initX, initY, x, y, finalX, finalY;
	int invAccel;
	int delay;
	const char *message;

	TextEntry(bool large, int x, int y, const char *message)
	: large(large), immune(false), fade(true), initX(x), initY(y)
	, x(x*PRECISION), y(y*PRECISION), finalX(x), finalY(y)
	, invAccel(6), delay(1), message(message) { }
};

void fontInit();
void updateText(bool top);
void clearText(bool top);
void clearText();
void printSmall(bool top, int x, int y, const char *message);
void printLarge(bool top, int x, int y, const char *message);
void animateTextIn(bool top);
TextEntry *getPreviousTextEntry(bool top);