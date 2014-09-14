#pragma once
#include "UICanvasCore.h"
#include <queue>
#include "audioHandler.h"


class scopeView :
	public UICanvasCore

{

	double max = 0.0;
	double scaleFact;
	uint32_t refreshCount=0;
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
		//for (; data._My_val.size() > 100;) data._My_val.pop();
		if (data._My_val.size() > 0)
		{
			refreshCount++;
			audPacket level = data._My_val.front();
			data._My_val.pop();
			this->canvas->shiftLeft();
			/*
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
			*/

			//float left = 0;
			//float right = 0;
			//level.l > 0 ? left = level.l : left = level.r;
		//	level.r > 0 ? right = level.r : right = level.l;
		//	float diff = left - right;
		//	float d2 = right - left;


			double lef = level.l;
			double rgh = level.r;
			if (this->refreshCount >= 200)
			{
				this->refreshCount = 0;
				this->max = 0;
			}
			if (abs(lef) > this->max) this->max = abs(lef);
			this->scaleFact = 1200/ this->max;
			long int lev = 0;
			if (isnan(lef))
				lef = 0.0;
			lev = abs(lef)*(this->scaleFact*4);
			this->col.b = 0;
			this->plot(make_pair(this->canvas->getWidth() - 1, -log2(abs(lev))+138), this->col);
			if (isnan(rgh))
				rgh = 0.0;
			lev = abs(rgh)*(this->scaleFact*4);
			this->col.b = 255;
			this->plot(make_pair(this->canvas->getWidth() - 1, -log2(abs(lev))+138), this->col);

		}
	}

	void redraw()
	{

		
	}

};

