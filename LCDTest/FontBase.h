#pragma once
#include "vectorFont.h"
#include <map>
#include <vector>
#include "common.h"
#include "Draw.h"

class FontBase : public Draw
{
	//! contains the character map
	std::map<char, std::vector<Point> > charMap;


public:
	FontBase();
	//! determine what vector to use for a given char
	std::vector<Point> getCharVectorGraphic(char); 

	//! draw a single character
	void drawCharacter(char, Color, Point); 

	//! draw an entire string of characters.
	void drawString(std::string, Color, Point);
};

