#pragma once
#include "menuItem.h"
#include <string>

//! This will keep track of menuItem entries, and render them properly.
class menuContainer :
	public menuItem
{
	std::pair<unsigned int, unsigned int> entrySize;
	std::vector<menuItem> entryList;
	std::vector<menuItem>::iterator selectedEntry;
	Color bg;
	Color fg;

public:
	//! default constructor. not too useful.
	menuContainer();

	//! create a menu container with useful information
	menuContainer(Point location, Color foreground, Color background, std::pair<unsigned int, unsigned int> size)
	{
		this->fg = foreground;
		this->bg = background;
		this->setPosition( location);
		this->setSize(size);
	}

	//! add an entry to the menu. entry position and size are automatically calculated.
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

	//! set the background color for all entries
	void setBackground(Color col)
	{
		this->bg = col;
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) iter->setBackground(col);
	}

	//! set the foreground color for all entries
	void setForegound(Color col)
	{
		this->fg = col;
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++) iter->setForeground(col);
	}

	//! redraw the menu.
	void redraw()
	{
		//this->drawCanvasBorder(this->fg);
		for (std::vector<menuItem>::iterator iter = this->entryList.begin(); iter != this->entryList.end(); iter++)
		{
			iter->redraw(this->selectedEntry == iter ? true : false);
			this->drawSubCanvas(iter->canvas, iter->getLocation(), iter->getSize());
		}
	}

	//! select the next item. wrap around included
	void selectUp()
	{
		this->selectedEntry == this->entryList.begin() ? this->selectedEntry = this->entryList.end() :
			this->selectedEntry--;
	}

	//! select the previous item. wrap around included
	void selectDown()
	{
		this->selectedEntry == this->entryList.end() ? this->selectedEntry = this->entryList.begin() :
			this->selectedEntry++;
	}
};

