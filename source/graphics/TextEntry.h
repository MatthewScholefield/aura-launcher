#pragma once

class TextEntry
{
public:
	static const int ACTIVE = 0;
	static const int COMPLETE = -1;
	static const int PRECISION = 10;

	enum class FadeType
	{
		NONE,
		IN,
		OUT
	};

	bool large;
	bool immune; //Does not clear
	FadeType fade;
	int initX, initY, x, y, finalX, finalY;
	int invAccel;
	int delay;
	int polyID;
	const char *message;

	int calcAlpha();
	bool update(); //Returns true to delete itself

	TextEntry(bool large, int x, int y, const char *message);
};