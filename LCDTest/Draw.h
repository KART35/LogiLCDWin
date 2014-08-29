#pragma once
#include "lcd.h"

#include <utility>
#include <vector>
#include "common.h"
using namespace std;


class Draw 
{

	bool circlePts(Point, Point, Color);
public:
	Canvas *canvas; //!< draw on this.

	Draw()
	{
		this->canvas = new Canvas;
	}
	Draw(Canvas * can)
	{
		this->canvas = can;
	}
	
	bool circle(Point, int, Color); //!< draw an unfilled circle
	void fillNgon(Point, vector<Point>, Color); //!< fill a polygon with solid color 
	bool plot(Point, Color); //!< point; RGBA; 0-255
	bool line(Point start, Point end, Color); //!< draw a line from Point start to Point end

	//! draw a border around the edge of the canvas.
	void drawCanvasBorder(Color);
	Canvas * getCanvas() //!< get a pointer to the main canvas
	{
		return this->canvas;
	}
	bool nLine(vector<Point>, Color); 
};

