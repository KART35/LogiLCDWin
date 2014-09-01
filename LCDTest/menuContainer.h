#pragma once
#include "menuItem.h"
#include <string>

class menuContainer :
	public menuItem
{
	std::pair<unsigned int, unsigned int> entrySize;
	std::vector<menuItem> entryList;
	std::vector<menuItem>::iterator selectedEntry;
	Color bg;
	Color fg;

public:
	menuContainer();


	menuContainer(Point location, Color foreground, Color background, std::pair<unsigned int, unsigned int> size)
	{
		this->fg = foreground;
		this->bg = background;
		this->setPosition( location);
		this->setSize(size);
	}

	void addEntry(std::string label)
	{
		this->entryList.push_back(menuItem(label, make_pair(entrySize.first, entrySize.second), bg = this->bg, fg = this->fg, this->entryList.size()+1));
		unsigned int cHehight = this->canvas->getHeight();

		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) //resize & replace canvases.
		{
			iter->setSize(make_pair(this->getSize().first, this->getSize().second / this->entryList.size() - 1));
			iter->setPosition(make_pair(0, (iter->getIndex()-1) * (this->getSize().second / this->entryList.size())));
			iter->redraw(false);
		}
		this->selectedEntry = this->entryList.begin();
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
		//this->drawCanvasBorder(this->fg);
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++)
		{
			iter->redraw(this->selectedEntry == iter ? true : false);
			this->drawSubCanvas(iter->canvas, iter->getLocation(), iter->getSize());
		}
	}

	void selectUp()
	{
		this->selectedEntry == this->entryList.begin() ? this->selectedEntry = this->entryList.end() :
			this->selectedEntry--;
	}

	void selectDown()
	{
		this->selectedEntry == this->entryList.end() ? this->selectedEntry = this->entryList.begin() :
			this->selectedEntry++;
	}
};

