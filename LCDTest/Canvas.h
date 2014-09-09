#pragma once
#include "LCD.h"
#include <stdint.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <utility>
#include "common.h"
#include "log.h"

//TODO: redo this to use an array of Color structs instead of a vector

class Canvas 
{
	
	unsigned int height = 0; //!< height of canvas 
	unsigned int width = 0;  //!< width of canvas
	unsigned int posX = 0; //!< horizontal position
	unsigned int posY = 0; //!< vertical position
	
public:
	//! image data stored in this
	std::vector<Color> page; 

	//! set the canvas size. Takes an X Y dimension pair
	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->height = size.second;
		this->width = size.first;
		this->page.resize(this->height * this->width);
	}

	//! set the canvas position. Takes an X Y coord pair.
	void setPosition(std::pair<unsigned int, unsigned int> position)
	{
		this->posX = position.first;
		this->posX = position.second;
	}

	//! return the width of the canvas
	int getWidth()
	{
		return width;
	}

	//! return the height of the canvas
	int getHeight()
	{
		return height;
	}

	//! create a canvas. 
	Canvas(
		unsigned int width = 320, //!< canvas width
		unsigned int height = 240, //!< canvas height
		unsigned int posX = 0, //!< canvas horizontal position
		unsigned int posY = 0 //!< canvas vertical position
		) :
		page(height*width)
	{
		this->height = height;
		this->width = width;
		this->posX = posX;
		this->posY = posY;
	}
	
	//! return an X Y coord pair for the canvas location
	std::pair<unsigned int, unsigned int> getLoc()
	{
		return std::make_pair(this->posX, this->posY);
	}

	//! return an X Y dimension pair
	std::pair<unsigned int, unsigned int> getSize()
	{
		return std::make_pair(this->height, this->width);
	}
	
	//! return a pointer to the canvas
	std::vector<Color> *getCanvas()
	{
		return &this->page;
	}

	//! utility function to calculate the offest for an X Y coord pair.
	
	//! Since the image is stored in a 1 dimensional array instead of a two 
	//! dimensional array, this is used to reliably get the proper offset.
	//! positon = (width_of_a_scan_line * y_coord) + x_coord
	//! first, calculate which line we are on, then tack on the X value.
	unsigned int getOffset(Point location)
	{
		return (this->getWidth() * location.second) + location.first;
	}
	
	//! get the color of a point on the canvas
	Color getPixel(Point location)
	{
		return this->page[getOffset(location)];
	}

	//! clear out the entire canvas. 
	void erase()
	{
		for (std::vector<Color>::iterator  iter = this->page.begin(); iter != this->page.end(); iter++)
		{
			iter->a = 0;
			iter->r = 0;
			iter->g = 0;
			iter->b = 0;
		}
	}

	//! shift the entire image one pixel to the left
	void shiftLeft()
	{
		std::rotate(this->page.begin(), this->page.begin() + 1, this->page.end());
		for (int i = 0; i < this->getHeight()*this->getWidth(); i += this->getWidth())
		{
			for (int j = 1; j < 2; j++)
			{
				this->page[i + this->getWidth() - j].r = 0;
				this->page[i + this->getWidth() - j].g = 0;
				this->page[i + this->getWidth() - j].b = 0;
			}
		}
		
	}
	
};


