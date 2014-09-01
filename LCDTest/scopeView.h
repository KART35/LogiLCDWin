#pragma once
#include "UICanvasCore.h"
#include <queue>
#include "audioHandler.h"


class scopeView :
	public UICanvasCore
{
	//std::queue<int16_t> samples;
	audioHandler aud;
public:
	scopeView(Color c) :
		aud()
	{
		col = c;
	}
	Color col;
	void refresh(int16_t sample = 0)
	{
		aud.checkState();
		for (; data._My_val.size() > 100;) data._My_val.pop();
		if (data._My_val.size() > 0)
		{
			audPacket level = data._My_val.back();
			data._My_val.pop();
			this->canvas->shiftLeft();

			int lvl = (abs(level.r) - 100000000000);// +(this->canvas->getHeight() / 2);
			lvl = (lvl / 1200000);
			lvl = (this->canvas->getHeight() / 2, lvl+235);
			this->plot(make_pair(this->canvas->getWidth()-1, lvl), this->col);

			    lvl = (abs(level.l) - 100000000000);
			lvl = (lvl / 1200000);
			lvl = (this->canvas->getHeight() / 2, lvl+235);
			this->plot(make_pair(this->canvas->getWidth() - 1, lvl), this->col);

			lvl = level.l - level.r;
			lvl = abs(lvl / 10000000);
			//this->plot(make_pair(this->canvas->getWidth() - 1, lvl), this->col);
		}
	}

	void redraw()
	{

		
	}

};

