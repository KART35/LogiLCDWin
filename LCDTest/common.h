#pragma once

#include <utility>
#include <stdint.h> 

typedef std::pair<float, float> Point; //!< X,Y

typedef struct Color
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;
};

inline bool operator==(const Color& lhs, const Color& rhs)
{
	return
		(
		(lhs.r == rhs.r) &&
		(lhs.g == rhs.g) &&
		(lhs.b == rhs.b) &&
		(lhs.a == rhs.a)
		);
}
inline bool operator!=(const Color& lhs, const Color& rhs)
{
	return
		!(
		(lhs.r == rhs.r) &&
		(lhs.g == rhs.g) &&
		(lhs.b == rhs.b) &&
		(lhs.a == rhs.a)
		);
}
