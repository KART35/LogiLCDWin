#pragma once
#include "UICanvasCore.h"
#include <string>


//! a menu item class. best used inside of a menuContainer.
class menuItem :
	public UICanvasCore
{
	string name; //!< string to be printed in the menu item
	uint16_t fieldID; //!< ID number of this menu item.
	Color bgColor; //!< background color
	Color fgColor; //!< foregournd color
	pair<unsigned int, unsigned int> size; //!< size of the menu item
	pair<unsigned int, unsigned int> position; //!< position of the menu item

public:
	//! default constructor. menu item with default (and not useful) values
	menuItem();
	
	//! construct a menu item with meaningful data
	menuItem(std::string label, pair<unsigned int, unsigned int> size, Color bgc, Color fgc, uint16_t fieldID)
	{
		this->name = label;
		this->fieldID = fieldID;
		this->bgColor = bgc;
		this->fgColor = fgc;
		this->size = size;
		this->canvas->setSize(size);
	}

	//! set the size of the menu item
	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->size = size;
		this->canvas->setSize(size);
	}

	//! set the position of this menu item
	void setPosition(std::pair<unsigned int, unsigned int> position)
	{
		this->position = position;
	}

	//! get this menu items index
	unsigned int getIndex()
	{
		return this->fieldID;
	}
	
	//! Redraw the menu item. If selected, swap the foreground and background colors
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
	
	//! set the background color
	void setBackground(Color col)
	{
		this->bgColor = col;
	}
	
	//! Set the foreground color
	void setForeground(Color col)
	{
		this->fgColor = col;
	}

	//! set the size of this menu item
	std::pair<unsigned int, unsigned int> getSize()
	{
		return this->size;
	}
	
	//! get the location of this menu item
	Point getLocation()
	{
		return this->position;
	}
};

