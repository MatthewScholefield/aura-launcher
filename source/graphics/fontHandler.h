#include "TextEntry.h"
#include "TextPane.h"
#include "Font.h"

#pragma once

void fontInit();
void updateText(bool top);
void clearText(bool top);
void clearText();
void printSmall(bool top, int x, int y, const char *message);
void printLarge(bool top, int x, int y, const char *message);
void animateTextIn(bool top);
void scrollTextVert(bool top, bool up, TextEntry &newEntry);
TextEntry *getPreviousTextEntry(bool top);
TextPane &createTextPane(int startX, int startY, int shownElements);
Font &getFont(bool large);