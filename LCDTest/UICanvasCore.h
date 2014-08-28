#pragma once
#include "LCD.h"
#include "PNGHandler.h"
#include "Draw.h"
#include "FontBase.h"
#include "Canvas.h"
class UICanvasCore : public FontBase
{
	

public:
	//Draw * draw = NULL;
	//FontBase * fonts = NULL;
	// LCD already exists
	/*UICanvasCore(FontBase *fnt)
	{
		
		this->fonts = fnt;
		if (fnt == NULL)
		{
			this->fonts = new FontBase();
		}
	}*/

	//let the core manage the LCD
	UICanvasCore()
	{
		//this->fonts = new FontBase();
	}
	bool drawSubCanvas(Canvas* , pair<unsigned int, unsigned int> location, pair<unsigned int, unsigned int> size); //!< draw a sub canvas onto the main canvas
	Canvas::pix blendPixel(Canvas::pix fg, Canvas::pix bg)//!blend two RGBA pixels together
	{
		Canvas::pix pixel;
		memset(&pixel, 0, sizeof(Canvas::pix));
		unsigned int alpha = fg.a + 1;
		unsigned int inv_alpha = 256 - fg.a;
		pixel.r = ((alpha * fg.r + inv_alpha * bg.r) >> 8);
		pixel.g = ((alpha * fg.g + inv_alpha * bg.g) >> 8);
		pixel.b = ((alpha * fg.b + inv_alpha * bg.b) >> 8);
		pixel.a = 255;
		return pixel;
	}
};

