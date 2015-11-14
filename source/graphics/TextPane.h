
/* 
 * File:   TextPane.h
 * Author: Matthew Scholefield
 *
 * Created on November 11, 2015, 2:54 PM
 */
#include <list>
#include <vector>
#include <string>
#include "TextEntry.h"

#ifndef TEXTPANE_H
#define	TEXTPANE_H

class TextPane
{
	const int START_PX, START_PY, SHOWN_ELEMENTS;
	int startIndex;
	std::list<TextEntry> shownText;
	std::vector<const char *> text;
	void wrapTransition();
public:
	void createDefaultEntries();
	void slideTransition(bool transitionIn);
	void scroll(bool up);
	void addLine(const char *line);
	bool update(bool top);
	TextPane(int startPX, int startPY, int shownElements);
};

#endif	/* TEXTPANE_H */

