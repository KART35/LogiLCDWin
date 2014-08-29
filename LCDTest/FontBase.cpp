#include "FontBase.h"
#include "vectorFont.h"
void FontBase::init()
{
	this->charMap.insert(make_pair('A', mono::A));
	this->charMap.insert(make_pair('B', mono::B));
	this->charMap.insert(make_pair('C', mono::C));
	this->charMap.insert(make_pair('D', mono::D));
	this->charMap.insert(make_pair('E', mono::E));
	this->charMap.insert(make_pair('F', mono::F));
	this->charMap.insert(make_pair('G', mono::G));
	this->charMap.insert(make_pair('H', mono::H));
	this->charMap.insert(make_pair('I', mono::I));
	this->charMap.insert(make_pair('J', mono::J));
	this->charMap.insert(make_pair('K', mono::K));
	this->charMap.insert(make_pair('L', mono::L));
	this->charMap.insert(make_pair('M', mono::M));
	this->charMap.insert(make_pair('N', mono::N));
	this->charMap.insert(make_pair('O', mono::O));
	this->charMap.insert(make_pair('P', mono::P));
	this->charMap.insert(make_pair('Q', mono::Q));
	this->charMap.insert(make_pair('R', mono::R));
	this->charMap.insert(make_pair('S', mono::S));
	this->charMap.insert(make_pair('T', mono::T));
	this->charMap.insert(make_pair('U', mono::U));
	this->charMap.insert(make_pair('V', mono::V));
	this->charMap.insert(make_pair('W', mono::W));
	this->charMap.insert(make_pair('X', mono::X));
	this->charMap.insert(make_pair('Y', mono::Y));
	this->charMap.insert(make_pair('Z', mono::Z));

	this->charMap.insert(make_pair('a', mono::a));
	this->charMap.insert(make_pair('b', mono::b));
	this->charMap.insert(make_pair('c', mono::c));
	this->charMap.insert(make_pair('d', mono::d));
	this->charMap.insert(make_pair('e', mono::e));
	this->charMap.insert(make_pair('f', mono::f));
	this->charMap.insert(make_pair('g', mono::g));
	this->charMap.insert(make_pair('h', mono::h));
	this->charMap.insert(make_pair('i', mono::i));
	this->charMap.insert(make_pair('j', mono::j));
	this->charMap.insert(make_pair('k', mono::k));
	this->charMap.insert(make_pair('l', mono::l));
	this->charMap.insert(make_pair('m', mono::m));
	this->charMap.insert(make_pair('n', mono::n));
	this->charMap.insert(make_pair('o', mono::o));
	this->charMap.insert(make_pair('p', mono::p));
	this->charMap.insert(make_pair('q', mono::q));
	this->charMap.insert(make_pair('r', mono::r));
	this->charMap.insert(make_pair('s', mono::s));
	this->charMap.insert(make_pair('t', mono::t));
	this->charMap.insert(make_pair('u', mono::u));
	this->charMap.insert(make_pair('v', mono::v));
	this->charMap.insert(make_pair('w', mono::w));
	this->charMap.insert(make_pair('x', mono::x));
	this->charMap.insert(make_pair('y', mono::y));
	this->charMap.insert(make_pair('z', mono::z));

	this->charMap.insert(make_pair('0', mono::num0));
	this->charMap.insert(make_pair('1', mono::num1));
	this->charMap.insert(make_pair('2', mono::num2));
	this->charMap.insert(make_pair('3', mono::num3));
	this->charMap.insert(make_pair('4', mono::num4));
	this->charMap.insert(make_pair('5', mono::num5));
	this->charMap.insert(make_pair('6', mono::num6));
	this->charMap.insert(make_pair('7', mono::num7));
	this->charMap.insert(make_pair('8', mono::num8));
	this->charMap.insert(make_pair('9', mono::num9));

	this->charMap.insert(make_pair(' ', mono::space));
	this->charMap.insert(make_pair('!', mono::excPoint));
	this->charMap.insert(make_pair('|', mono::pipe));
	this->charMap.insert(make_pair('?', mono::qMark));
	this->charMap.insert(make_pair(',', mono::comma));
	this->charMap.insert(make_pair('\'', mono::singleQuote));
	this->charMap.insert(make_pair('"', mono::doubleQuote));
	this->charMap.insert(make_pair(';', mono::semicolon));
	this->charMap.insert(make_pair(':', mono::colon));
	this->charMap.insert(make_pair('.', mono::period));
	this->charMap.insert(make_pair('/', mono::fSlash));
	this->charMap.insert(make_pair('\\', mono::bSlash));
	this->charMap.insert(make_pair('+', mono::plus));
	this->charMap.insert(make_pair('-', mono::minus));
	this->charMap.insert(make_pair('_', mono::underscore));
	this->charMap.insert(make_pair('=', mono::equals));

	this->charMap.insert(make_pair(0, mono::placeholder));
}

vector<Point> FontBase::getCharVectorGraphic(char c)
{
	std::map<char, vector<Point> >::iterator iter = this->charMap.find(c);
	if (iter != charMap.end())
	{
		return iter->second;
	}
	else
	return mono::placeholder;
}

void FontBase::drawCharacter(char ltr, Color color, Point p)
{
	vector<Point>::iterator iter;
	vector<Point> characterVec = this->getCharVectorGraphic(ltr);
	for (iter = characterVec.begin(); iter != characterVec.end(); iter++)
	{
		iter->first += p.first;
		iter->second += p.second;
	}
	this->nLine(characterVec, color);
	
}

void FontBase::drawString(std::string str, Color col, Point p)
{
	std::string::iterator iter;
	int xOrig =(int) p.first;
	for (iter = str.begin(); iter != str.end(); iter++)
	{
		if (*iter == '\n')
		{
			p.second += 19;
			p.first = (float)xOrig;
		} 
		else
		{
			
			if (p.first > (this->canvas->getWidth() - 10)) // word wrap.. kinda
			{
				p.first = (float)xOrig;
				p.second += 19;
				if (*iter == ' ') iter++;
			}
			this->drawCharacter(*iter, col, p);
			p.first += 10;
		}
	}
}