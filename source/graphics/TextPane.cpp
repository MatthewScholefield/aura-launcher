/* 
 * File:   TextPane.cpp
 * Author: Matthew Scholefield
 * 
 * Created on November 11, 2015, 2:54 PM
 */

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "TextPane.h"
#include "fontHandler.h"
#include "Font.h"

using namespace std;

void TextPane::wrapTransition()
{//Only call if text.size() is greater than SHOWN_ELEMENTS
	bool atBottom = startIndex > 0;
	const int SLIDE_Y = 16;
	int numElements = 0;
	for (auto it = shownText.begin(); it != shownText.end(); ++it)
	{
		if (it->fade == TextEntry::FadeType::OUT)
			continue;
		//it->delay = numElements++ * 2;
		it->initX = it->x / TextEntry::PRECISION;
		it->initY = it->y / TextEntry::PRECISION;
		it->finalY = it->y / TextEntry::PRECISION + (atBottom ? 1 : -1) * SLIDE_Y; //START_PY + FONT_SY * numElements + (atBottom ? 1 : -1) * SLIDE_Y;
		it->fade = TextEntry::FadeType::OUT;
		++numElements;
	}
	numElements = 0;
	for (int i = atBottom ? 0 : (text.size() - SHOWN_ELEMENTS); i < (atBottom ? SHOWN_ELEMENTS : (int) text.size()); ++i)
	{
		int pY = START_PY + FONT_SY * numElements++ + (atBottom ? -1 : 1) * SLIDE_Y;
		shownText.emplace_back(false, START_PX, pY, text[i]);
		TextEntry &entry = shownText.back();
		entry.delay = 0;
		entry.finalY += (atBottom ? 1 : -1) * SLIDE_Y;
		entry.fade = TextEntry::FadeType::IN;
	}
}

void TextPane::createDefaultEntries()
{
	for (int i = 0; i < min(SHOWN_ELEMENTS, (int) text.size()); ++i)
		shownText.emplace_back(false, START_PX, START_PY + FONT_SY * i, text[i]);
}

void TextPane::slideTransition(bool transitionIn)
{
	const int SLIDE_X = 16;
	int numElements = 0;
	for (auto it = shownText.begin(); it != shownText.end(); ++it)
	{
		it->delay = numElements++ * 2;
		it->x = TextEntry::PRECISION * (it->initX = it->finalX - SLIDE_X);
		it->fade = TextEntry::FadeType::IN;
	}
}

void TextPane::scroll(bool up)
{
	startIndex += up ? 1 : -1;
	if (startIndex < 0 || startIndex + SHOWN_ELEMENTS > (int) text.size())
	{
		wrapTransition();
		startIndex = up ? 0 : (text.size() - SHOWN_ELEMENTS);
		return;
	}
	for (auto it = shownText.begin(); it != shownText.end(); ++it)
	{
		if (it->fade == TextEntry::FadeType::OUT)
			continue;
		it->delay = TextEntry::ACTIVE;
		it->finalY += FONT_SY * (up ? -1 : 1);
		it->fade = TextEntry::FadeType::NONE;
	}
	TextEntry newEntry(false, START_PX, START_PY + FONT_SY * (up ? SHOWN_ELEMENTS : -1)
					, text[startIndex + (up ? (SHOWN_ELEMENTS - 1) : 0)]);
	int start = 0, finish = shownText.size();
	for (auto it = shownText.begin(); it != shownText.end() && it->fade == TextEntry::FadeType::OUT; ++it)
		++start;
	for (auto it = prev(shownText.end(), 1); it != prev(shownText.begin(), 1) && it->fade == TextEntry::FadeType::OUT; --it)
		--finish;

	newEntry.delay = TextEntry::ACTIVE;
	newEntry.finalY += FONT_SY * (up ? -1 : 1);
	//newEntry.finalX += 20;
	newEntry.fade = TextEntry::FadeType::IN;

	auto it = next(shownText.begin(), up ? start : (finish - 1));
	it->fade = TextEntry::FadeType::OUT;
	it->initX = it->x / TextEntry::PRECISION;
	it->initY = it->y / TextEntry::PRECISION;
	if (up)
		shownText.push_back(newEntry);
	else
		shownText.push_front(newEntry);
}

void TextPane::addLine(const char *line)
{
	text.emplace_back(line);
}

bool TextPane::update(bool top)
{
	if (top)
		return false;
	for (auto it = shownText.begin(); it != shownText.end(); ++it)
	{
		if (it->update())
		{
			it = shownText.erase(it);
			--it;
			continue;
		}
		glPolyFmt(POLY_ALPHA(it->calcAlpha()) | POLY_CULL_NONE | POLY_ID(1));
		getFont(it->large).print(it->x / TextEntry::PRECISION, it->y / TextEntry::PRECISION, it->message);
	}
	return shownText.size() == 0;
}

TextPane::TextPane(int startPX, int startPY, int shownElements)
: START_PX(startPX), START_PY(startPY), SHOWN_ELEMENTS(shownElements), startIndex(0) { }