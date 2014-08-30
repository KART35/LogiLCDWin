#pragma once
#include "LCD.h"
#include <stdint.h>
#include <utility>
#include <vector>
#include "common.h"

class Canvas 
{
	
	unsigned int 
		height, 
		width, 
		posX, 
		posY = 0;
	
public:
	std::vector<Color> page;

	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->height = size.second;
		this->width = size.first;
		this->page.resize(this->height * this->width);
	}

	void setPosition(std::pair<unsigned int, unsigned int> position)
	{
		this->posX = position.first;
		this->posX = position.second;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	Canvas(unsigned int width = 320, unsigned int height = 240, unsigned int posX = 0, unsigned int posY = 0) :
		page(height*width)
	{
		this->height = height;
		this->width = width;
		this->posX = posX;
		this->posY = posY;
	}
	
	std::pair<unsigned int, unsigned int> getLoc()
	{
		return std::make_pair(this->posX, this->posY);
	}

	std::pair<unsigned int, unsigned int> getSize()
	{
		return std::make_pair(this->height, this->width);
	}
	
	std::vector<Color> *getCanvas()
	{
		return &this->page;
	}

	unsigned int getOffset(Point location)
	{
		return (this->getWidth() * location.second) + location.first;
	}
	
	Color getPixel(Point location)
	{
		return this->page[getOffset(location)];
	}
	
};


