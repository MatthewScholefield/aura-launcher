#pragma once

class TextEntry
{
public:
	static const int COMPLETE = -1;
	static const int NO_FADE = -2;
	static const int PRECISION = 10;

	bool large;
	int initX, initY, x, y, finalX, finalY;
	int delay;
	const char *message;

	TextEntry(bool large, int x, int y, const char *message)
	: large(large), initX(x), initY(y), x(x), y(y), finalX(x), finalY(y), delay(COMPLETE), message(message) { }
};

void fontInit();
void updateText(bool top);
void clearText(bool top);
void clearText();
void printSmall(bool top, int x, int y, const char *message);
void printLarge(bool top, int x, int y, const char *message);
void animateTextIn(bool top);
TextEntry *getPreviousTextEntry(bool top);