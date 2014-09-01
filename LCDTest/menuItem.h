#pragma once
#include "UICanvasCore.h"
#include <string>

class menuItem :
	public UICanvasCore
{
	string name;
	uint16_t fieldID;
	Color bgColor;
	Color fgColor;
	pair<unsigned int, unsigned int> size;
	pair<unsigned int, unsigned int> position;

public:
	menuItem();
	menuItem(std::string label, pair<unsigned int, unsigned int> size, Color bgc, Color fgc, uint16_t fieldID)
	{
		this->name = label;
		this->fieldID = fieldID;
		this->bgColor = bgc;
		this->fgColor = fgc;
		this->size = size;
		this->canvas->setSize(size);
	}

	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->size = size;
		this->canvas->setSize(size);
	}


	void setPosition(std::pair<unsigned int, unsigned int> position)
	{
		this->position = position;
	}

	unsigned int getIndex()
	{
		return this->fieldID;
	}
	void redraw(bool isSel)
	{

		this->canvas->erase();
		if (!isSel)
		{
			
			this->drawCanvasBorder(fgColor);
			this->floodFill(make_pair(3, 3), this->canvas->getPixel(make_pair(3, 3)), bgColor);
			this->drawString(name, fgColor, make_pair(2, 12));
		}
		else
		{
			this->drawCanvasBorder(bgColor);
			this->floodFill(make_pair(3, 3), this->canvas->getPixel(make_pair(3, 3)), fgColor);
			this->drawString(name, bgColor, make_pair(2, 12));
		}
	}
	void setBackground(Color col)
	{
		this->bgColor = col;
	}
	void setForeground(Color col)
	{
		this->fgColor = col;
	}

	std::pair<unsigned int, unsigned int> getSize()
	{
		return this->size;
	}

	Point getLocation()
	{
		return this->position;
	}
};

