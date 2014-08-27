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
	bool drawSubCanvas(Canvas* , pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int> ); //!< draw a sub canvas onto the main canvas
};

