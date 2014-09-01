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
#include "scopeView.h"
#include "menuContainer.h"
using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	std::ofstream f; 
	f.open("log.txt"); //clear out the log file
	f.close();

	logSys::putMessage("Startup", logSys::info, LOGINFO(0));
	LogiLCD lcd;

	//scopeView s(col);
	
	PNGHandler png(&lcd);
	
	UICanvasCore uiCore;
	Color col;
	Color replaced;
	Color replacement;

	replaced.a = 255;
	replaced.r = 0;
	replaced.g = 0;
	replaced.b = 255;
	replacement.r = 255;
	replacement.g = 255;
	replacement.b = 255;
	replacement.a = 255;
	col.a = 255;
	scopeView s(replacement);
	Canvas can(150, 40);
	FontBase fonts(&can);
	/*
	//menuContainer cont;
	cont.setSize(make_pair(75, 237));
	cont.setPosition(make_pair(3, 1));
	cont.setBackground(replaced);
	cont.setForegound(replacement);
	cont.addEntry("one");
	cont.addEntry("two");
	cont.addEntry("three");
	cont.addEntry("four");
	cont.addEntry("five");
	cont.addEntry("six");
	cont.addEntry("seven");
	cont.addEntry("eight");
	cont.addEntry("nine");
	cont.addEntry("ten");
	cont.addEntry("eleven");
	cont.addEntry("twelve");*/
	while (
		LogiLcdIsConnected(LOGI_LCD_TYPE_COLOR) && 
		(!LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_CANCEL))
		)
	{

		col.g = 255;
		col.r = 255;
		col.b = 255;
		//uiCore.drawCanvasBorder(col);
		//uiCore.floodFill(make_pair(200, 50), replaced, replacement);
		/*
		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_UP))
		{
			cont.selectUp();
		}
		else if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_DOWN))
		{
			cont.selectDown();
		}

		cont.redraw();
		uiCore.drawSubCanvas(cont.canvas, cont.getLocation(), cont.getSize());
		*/

		//uiCore.circle(make_pair(50, 50), 25, col);
		//for (int i = 0; i < lcd.getWidth(); i++)
	//	{
	//		uiCore.canvas->shiftLeft();
	//		lcd.setCanvas(uiCore.getCanvas()); //leaky...
	//		lcd.SetImg();
	//		
	//	}
		s.refresh();
		lcd.setCanvas(s.getCanvas()); //leaky...
		lcd.SetImg();
		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_OK))
		{
			png.saveImage("test.png");
			Sleep(100);
		}
	}
	logSys::putMessage("exit", logSys::info, LOGINFO(0));
	return 0;
}

