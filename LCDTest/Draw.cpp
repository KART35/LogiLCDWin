#include "Draw.h"
#include "LCD.h"
#include "common.h"
/*
DrawCore::DrawCore(Canvas * lcd)
{
	canvas = lcd;
}

Draw::Draw(DrawCore * core):
FontBase(core)
{
	this->core = core;
}
*/
//! Plot a single pixel with the specified Color
bool Draw::plot(Point p, Color c)
{
	
	//bounds checking
	if (
		(p.first < 0) || (p.first > this->canvas->getWidth() - 1) ||
		(p.second < 0) || (p.second > this->canvas->getHeight()-1)
		)
	{
		return false;
	}
	this->canvas->page[(this->canvas->getWidth() * (int)p.second) + (int)p.first].r = c.r;
	this->canvas->page[(this->canvas->getWidth() * (int)p.second) + (int)p.first].g = c.g;
	this->canvas->page[(this->canvas->getWidth() * (int)p.second) + (int)p.first].b = c.b;
	this->canvas->page[(this->canvas->getWidth() * (int)p.second) + (int)p.first].a = c.a;
	return true;
}

//! Draw a line segment between start and end of the specified Color.
bool Draw::line(Point start, Point end, Color col)
{
	//bounds checking. 
	//{x|0 <= x <= img_width -1 }
	//{x|0 <= y <= img_height}
	// if either are false, return without
	// plotting anything.
	if (
		(start.first < 0)  || (start.first > this->canvas->getWidth() - 1) ||
		(start.second < 0) || (start.second > this->canvas->getHeight()) ||
		(end.first < 0)    || (end.first > this->canvas->getWidth() - 1) ||
		(end.second < 0)   || (end.second > this->canvas->getHeight())
		)
	{
		return false;
	}

	if (start.first > end.first) //swap if points are backwards
	{
		Point tmp = end;
		end = start;
		start = tmp;
	}

	int dy = end.second - start.second;
	int dx = end.first - start.first;
	float m = (float)dy / (float)dx;
	if (abs(m) >= 1)
	{
		m = 1 / m;
		if (start.second > end.second && m == 0) //swap if points are backwards
		{
			Point tmp = end;
			end = start;
			start = tmp;
		}
		float x = start.first;

		// this approach only works when abs(m) > 1.
		float y = start.second;
		float y2 = end.second;
		if (m < 0)
		{

			for (; y >= end.second; y--)
			{
				plot(make_pair((int)round(x), y), col);
				x -= m;
			}
		}
		else
		{

			for (; y <= end.second; y++)
			{
				plot(make_pair((int)round(x), y), col);
				x += m;
			}
		}
	}
	else
	{
		float y = start.second;
		// this approach only works when abs(m) <= 1.
		for (float x = start.first; x <= end.first; x++)
		{
			plot(make_pair(x, (int)round(y)), col);
			y += m;
		}
	}
	return true;
}

//! Draw a series of line segments end to end, all of the same color
bool Draw::nLine(vector<Point> series, Color col)
{
	vector<Point>::iterator iterA;
	vector<Point>::iterator iterB;
	if (series.size() < 2)
	{
		return false;
	}
	iterA = iterB = series.begin();
	for (iterB++; iterB != series.end(); iterA++, iterB++)
	{
		if (iterB->first == INFINITY || iterA->first == INFINITY) //lift pen
		{
			//mark nothing
		}
		else if(!this->line(*iterA, *iterB, col)) return false;
	}
	return true;
}

bool Draw::circlePts(Point pt, Point center, Color col)
{
	int x = pt.first;
	int y = pt.second;
	int nx = (pt.first *-1);
	int ny = (pt.second *-1);

	int res = 0;
	Point tmp;
	
	res += this->plot(Point(x + center.first, y + center.second), col);
	res += this->plot(Point(x + center.first, y + center.second), col);
	res += this->plot(Point(y + center.first, x + center.second), col);
	res += this->plot(Point(y + center.first, nx + center.second), col);
	res += this->plot(Point(x + center.first, ny + center.second), col);
	res += this->plot(Point(nx + center.first, ny + center.second), col);
	res += this->plot(Point(ny + center.first, nx + center.second), col);
	res += this->plot(Point(ny + center.first, x + center.second), col);
	res += this->plot(Point(nx + center.first, y + center.second), col);
	
	
	//verify that everything went OK.
	if (res != 7)
		return true;
	else
		return true;
}

bool Draw::circle(Point pt, int radius, Color col)
{
	int x, y, d;
	x = 0;
	y = radius;
	d = 1 - radius;
	int dE = 3;
	int dSE = (-2 * radius) + 5;
	if (!circlePts(Point(x, y), pt, col)) 
		return false;
	while (y>x)
	{
		if (d < 0)
		{
			d += dE;
			dE += 2;
			dSE += 2;
			x++;
		}
		else
		{
			d += dSE;
			dE += 2;
			dSE += 4;
			x++;
			y--;
		}
		if(!circlePts(Point(x, y), pt, col)) 
			return false;
	}
	
	return true;
}

void Draw::drawCanvasBorder(Color col)
{
	unsigned int h = this->canvas->getHeight();
	unsigned int w = this->canvas->getWidth();

	line(make_pair(0, 0), make_pair(0, h - 1), col);
	line(make_pair(0, 0), make_pair(w - 1, 0), col);
	line(make_pair(0, h - 1), make_pair(w - 1, h - 1), col);
	line(make_pair(w - 1, 0), make_pair(w - 1, h - 1), col);
}

void Draw::floodFill (Point location, Color oldCol, Color newCol)
{
	Color exist = this->canvas->getPixel(location);
	if (newCol == exist) return;
	std::queue<Point> Q;
	Q.push(location);
	Point newLoc;
	while (Q.size() != 0)
	{
		Point n = Q.front();
		Q.pop();
		if (isValidCoord(n)) exist = this->canvas->getPixel(n);
		if (exist == oldCol)
		{
			this->plot(n, newCol);
			

				newLoc = make_pair(n.first - 1, n.second);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}
			
				newLoc = make_pair(n.first + 1, n.second);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first, n.second + 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first, n.second - 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first + 1, n.second + 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first + 1, n.second - 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first - 1, n.second - 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				newLoc = make_pair(n.first - 1, n.second + 1);
				if (isValidCoord(newLoc))
				{
					exist = this->canvas->getPixel(newLoc);
					if (newCol != exist)
						Q.push(newLoc);
				}

				try
				{
				}
			catch (std::exception &e)
			{
				FILE*fp = NULL;
				fopen_s(&fp, "err.txt", "w");
				fputs(e.what(), fp);
				fclose(fp);
				abort();
			}
		}
	}

}



