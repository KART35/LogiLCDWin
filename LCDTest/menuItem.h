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
	bool isSelected = false;

public:
	menuItem();
	menuItem(std::string label, pair<unsigned int, unsigned int> size, Color bgc, Color fgc, uint16_t fieldID)
	{
		this->name = label;
		this->fieldID = fieldID;
		this->bgColor = bgc;
		this->fgColor = fgc;
		this->size = size;
	}

	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->size = size;
	}

	void setPosition(std::pair<unsigned int, unsigned int> position)
	{
		this->position = position;
	}

	unsigned int getIndex()
	{
		return this->fieldID;
	}
	void redraw()
	{
		this->drawCanvasBorder(fgColor);
		this->floodFill(make_pair(3, 3), this->canvas->getPixel(make_pair(3, 3)), bgColor);
		this->drawString(name, fgColor, make_pair(13, 3));
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

