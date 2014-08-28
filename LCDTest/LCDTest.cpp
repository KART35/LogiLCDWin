// LCDTest.cpp : Defines the entry point for the console application.
//
#include "LCD.h"
#include "Draw.h"
#include "FontBase.h"
#include "PNGHandler.h"
#include "Canvas.h"
#include "UICanvasCore.h"
#include <Windows.h>
#include <math.h>
using namespace std;

//TODO: screenshot. on press of OK button, save to PNG in working dir.
int _tmain(int argc, _TCHAR* argv[])
{
	LogiLCD lcd;
	
	PNGHandler png(&lcd);
	//Draw draw;
	
	UICanvasCore uiCore;
	Color col;
	while (
		LogiLcdIsConnected(LOGI_LCD_TYPE_COLOR) && 
		(!LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_CANCEL))
		)
	{
		//lcd.showTestImage();
		//for (int i = 0; i < (320*240); i++)
		//{
		//	lcd.page[i][0] = 0;
		//	lcd.page[i][1] = 0;
		//}
		
		Point a(0, 0);
		Point b(140, 150);
		Point c(100, 100);
		Point d(0, 200);
		Point e(30, 100);
		Point center(160, 120);

		vector<Point> ser;
		ser.push_back(a);
		ser.push_back(b);
		ser.push_back(c);
		ser.push_back(d);
		ser.push_back(e);
		ser.push_back(center);
		//drw.nLine(ser, col);

		//col.b = 255;
		//col.r = 255;
		//col.g = 255;
		//drw.line(a, e, col);
		//drw.line(a, c, col);
		//col.b = 0;
		//col.g = 0;
		//drw.line(e, b, col);
		//drw.line(b, d, col);
		//col.r = 0;
		//col.b = 255;
		//drw.line(e, c, col);
		//drw.line(c, b, col);//m=7.5, down to right; up to right on normal graph
		//col.b = 0;
		//col.g = 255;
		//drw.line(d, e, col);//m=-4.33333349, up to right; down to right on normal graph
		//drw.line(d, a, col);
		/*
		col.r = 255;
		col.b = 255;
		col.g = 255;
		for (int i = 0; i < lcd.img_width; i += 1)
		{
			drw.line(center, Draw::Point(i, 239), col);
			lcd.SetImg();
		}
		col.r = 255;
		col.b = 0;
		col.g = 0;

		for (int i = 0; i < lcd.img_height; i += 1)
		{
			
			drw.line(center, Draw::Point(319, i), col);
			lcd.SetImg();
		}
		col.r = 0;
		col.b = 255;
		col.g = 0;
		for (int i = 0; i < lcd.img_width; i += 1)
		{
			drw.line(center, Draw::Point(i, 0), col);
			lcd.SetImg();
		}
		col.r = 0;
		col.b = 0;
		col.g = 255;

		for (int i = 0; i < lcd.img_height; i += 1)
		{
			drw.line(center, Draw::Point(0, i), col);
			lcd.SetImg();
		}
		*/
		//uiCore.plot(make_pair(0, 0), col);
		//uiCore.circle(center, 110, col);

		uiCore.drawString(std::string("This is on the primary canvas."), col, make_pair(0, 12));
		Canvas can(200, 150);
		FontBase fonts(&can);
		col.g = 0;
		col.r = 0;
		col.a = 128;
		
		
		fonts.circle(make_pair(100, 50), 30, col);
		fonts.line(make_pair(1, 1), make_pair(199, 99), col);
		fonts.line(make_pair(1, 99), make_pair(199, 1), col);
		//fonts.drawString(std::string("this is on a second canvas"), col, make_pair(0, 20));
		for (int i = 0; i != 10; i++)
		{
			//fonts.line(make_pair(0, 0), make_pair(i, 19), col);
		}
		uiCore.drawSubCanvas(&can, make_pair(30, 30), can.getSize());
		col.g = 255;
		col.r = 255;

		lcd.setCanvas(uiCore.getCanvas());
		//lcd.setCanvas(&can);
		lcd.SetImg();
		if (LogiLcdIsButtonPressed(LOGI_LCD_COLOR_BUTTON_OK))
		{
			png.saveImage("test.png");
		}
	}
	return 0;
}

