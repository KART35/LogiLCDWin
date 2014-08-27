#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#define PNG_DEBUG 3
#include <png.h>
#include "LCD.h"

class PNGHandler
{
	int x, y;
	LogiLCD * lcd;
	int width = LogiLCD::img_width;
	int height = LogiLCD::img_height;
	png_byte color_type = PNG_COLOR_TYPE_RGB;
	png_byte bit_depth =8; //4 bits per channel (unsigned char)
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep row_pointer;
public:
	bool saveImage(char* file_name);
	PNGHandler(LogiLCD *);
};

