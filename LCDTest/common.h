#pragma once

#include <utility>
#include <stdint.h> 

typedef std::pair<float, float> Point; //!< X,Y
struct Color
{
	uint8_t r = 255;
	uint8_t b = 255;
	uint8_t g = 255;
	uint8_t a = 255;
};