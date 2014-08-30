// LCDTest.cpp : Defines the entry point for the console application.
//


#include <stdlib.h>
#include <crtdbg.h>
#include "LCD.h"
#include "Draw.h"
#include "FontBase.h"
#include "PNGHandler.h"
#include "Canvas.h"
#include "UICanvasCore.h"
#include <Windows.h>
#include <math.h>
#include <stdexcept>
#include "menuContainer.h"

using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	LogiLCD lcd;
	
	PNGHandler png(&lcd);
	
	UICanvasCore uiCore;
	Color col;
	Color replaced;
	Color replacement;
	col.a = 255;
	Canvas can(150, 40);
	FontBase fonts(&can);
	menuContainer cont;
	cont.setSize(make_pair(300, 200));
	cont.addEntry("one");
	cont.addEntry("two");
	cont.addEntry("three");
	while (
		LogiLcdIsConnected(LOGI_LCD_TYPE_COLOR) && 
		(!LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_CANCEL))
		)
	{

		col.g = 255;
		col.r = 255;
		col.b = 255;
		replaced.a = 0;
		replaced.r = 0;
		replaced.g = 0;
		replaced.b = 255;
		replacement.r = 0;
		replacement.g = 255;
		replacement.b = 0;
		replacement.a = 255;
		uiCore.drawCanvasBorder(col);
		uiCore.floodFill(make_pair(200, 50), replaced, replacement);
		
		cont.setBackground(replaced);
		cont.setForegound(replacement);
		cont.redraw();
		uiCore.drawSubCanvas(cont.canvas, cont.getLocation(), cont.getSize());
		
		
		

		lcd.setCanvas(uiCore.getCanvas()); //leaky...
		lcd.SetImg();
		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_OK))
		{
			png.saveImage("test.png");
		}
	}

	return 0;
}

