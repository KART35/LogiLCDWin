#pragma once
#include <stdint.h>
#include "stdafx.h"
#define BYTE uint8_t
#include <LogitechLCD.h>
#include <stdio.h>
#include <iostream>
#include <wchar.h>
#include <vector>

#include "Canvas.h"
#define WIN32_LEAN_AND_MEAN
using namespace std;

/*! \brief LogiLCD interface class
*    manages the initialization
*    of the G19s LCD
*/
class Canvas;
class LogiLCD
{
	wchar_t *initMsg = L"LCDTest"; //!< LCD app name
	BYTE* bPage; //!< pointer to pixel array that the logitech libs can read.
	//! Note the exit status of LogiLCD::LogiLCD
	enum {
		init_err_not_conn = -3, //!< couldn't find device
		init_err_init_fail = -2, //!< some fail in initialization
		init_err_not_init = -1, //!< default state; indicates that init has not run
		init_ok = 0 //!< everything checked out; ready for use.
	};

	short int initOK = init_err_not_init;
	
public:
	enum {
		img_height = 240, //!< height of display, in pixels
		img_width = 320,  //!< Width of display, in pixels
	};
	enum pix {
		r = 2, //!< red index
		g = 1, //!< blue index
		b = 0, //!< green index
		a = 3  //!< alpha index
	};
	Canvas *canvas;
	BYTE page[img_height*img_width][4];
	void setCanvas(Canvas* can)
	{
		this->canvas = can;
	}
	LogiLCD();
	void SetImg();
	void showTestImage();
	uint8_t getHeight();
	uint8_t getWidth();

};