#pragma once
#include "LCD.h"
#include "PNGHandler.h"
#include "Draw.h"
#include "FontBase.h"
#include "Canvas.h"
class UICanvasCore : public FontBase
{
	

public:

	//!let the core manage the LCD
	UICanvasCore()
	{
	}
	bool drawSubCanvas(Canvas* , pair<unsigned int, unsigned int> location, pair<unsigned int, unsigned int> size); //!< draw a sub canvas onto the main canvas
	Color blendPixel(Color fg, Color bg)//!<blend two RGBA pixels together
	{
		Color pixel;
		memset(&pixel, 0, sizeof(Color));
		unsigned int alpha = fg.a + 1;
		unsigned int inv_alpha = 256 - fg.a;
		pixel.r = ((alpha * fg.r + inv_alpha * bg.r) >> 8);
		pixel.g = ((alpha * fg.g + inv_alpha * bg.g) >> 8);
		pixel.b = ((alpha * fg.b + inv_alpha * bg.b) >> 8);
		pixel.a = 255;
		return pixel;
	}
};

