#include "lcd.h"
#include <Windows.h>
#define PI (3.141592653589793)

LogiLCD::LogiLCD()
{
	if (!LogiLcdInit(initMsg, LOGI_LCD_TYPE_COLOR))
	{
		cout << "init failed" << endl;
		this->initOK = init_err_init_fail;
	}
	if (!LogiLcdIsConnected(LOGI_LCD_TYPE_COLOR))
	{
		cout << "lcd not connected" << endl;
		this->initOK = init_err_not_conn;
	}
	else
	{
		this->initOK = init_ok;
	}
}

//! Display a test image
void LogiLCD::showTestImage()
{
	for (int i = 0; i < img_height; i++)
	{
		for (int j = 0; j < img_width; j++)
		{ 
			float height = 0;
			height =( i / (float)img_height)*PI*4;
			this->page[(i * img_width) + j][pix::r] = 255 * abs(sin(height + (PI / 3)));
			this->page[(i * img_width) + j][pix::g] = 255 * abs(sin(height + (2 * PI / 3)));
			this->page[(i * img_width) + j][pix::b] = 255 * abs(sin(height));
			this->page[(i * img_width) + j][pix::a] = 255;
		}
	}
}

//! Display a background image
void LogiLCD::SetImg()
{
	
	unsigned int pixels = this->canvas->getHeight() * this->canvas->getWidth();
	for (int i = 0; i != pixels; i++)
	{
		this->page[i][pix::b] = this->canvas->page[i].b;
		this->page[i][pix::g] = this->canvas->page[i].g;
		this->page[i][pix::r] = this->canvas->page[i].r;
		this->page[i][pix::a] = this->canvas->page[i].a;
	}

	BYTE* page = reinterpret_cast<BYTE*>(this->page);
	LogiLcdColorSetBackground(page);
	LogiLcdUpdate();
}
uint8_t LogiLCD::getHeight()
{
	return img_height;
}
uint8_t LogiLCD::getWidth()
{
	return img_width;
}