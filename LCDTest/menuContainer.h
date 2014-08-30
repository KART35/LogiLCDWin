#pragma once
#include "menuItem.h"
#include <string>

class menuContainer :
	public menuItem
{
	std::pair<unsigned int, unsigned int> entrySize;
	std::vector<menuItem> entryList;
	std::vector<menuItem>::iterator selectedEntry;
	Point location;
	std::pair<unsigned int, unsigned int> size;
	Color bg;
	Color fg;

public:
	menuContainer();

	std::pair<unsigned int, unsigned int> getSize()
	{
		return this->size;
	}

	void setSize(std::pair<unsigned int, unsigned int> size)
	{
		this->size = size;
	}

	Point getLocation()
	{
		return this->location;
	}

	menuContainer(Point location, Color foreground, Color background, std::pair<unsigned int, unsigned int> size)
	{
		this->fg = foreground;
		this->bg = background;
		this->location = location;
		this->size = size;
	}

	void addEntry(std::string label)
	{
		this->entryList.push_back(menuItem(label, make_pair(entrySize.first, entrySize.second), bg, fg, this->entryList.size()+1));
		unsigned int cHehight = this->canvas->getHeight();

		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) //resize & replace canvases.
		{
			iter->setSize(make_pair(this->size.first, this->size.second / this->entryList.size()));
			iter->setPosition(make_pair(0, (iter->getIndex()-1) * (this->size.second / this->entryList.size())));
			iter->redraw();
		}
	}

	void setBackground(Color col)
	{
		this->bg = col;
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) iter->setBackground(col);
	}

	void setForegound(Color col)
	{
		this->fg = col;
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) iter->setForeground(col);
	}

	void redraw()
	{
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++)
		{
			iter->redraw();
			this->drawSubCanvas(iter->canvas, iter->getLocation(), iter->getSize());
		}
	}
		
};

