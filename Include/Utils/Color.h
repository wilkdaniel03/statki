#pragma once

#include <array>
#include <stdexcept>

class Color {
	std::array<unsigned char,4> data;
public:
	Color() {}
	Color(const unsigned char red, const unsigned char green, const unsigned char blue) :
		data({red,green,blue,255})
	{}

	unsigned char operator[](const int index) {
		if(index < 4) {
			return this->data[index];
		}

		throw std::runtime_error("Index of color cannot be larger than 3");
	}

	void SetAlpha(const unsigned alpha) {
		this->data[3] = alpha;
	}
};

namespace Colors {

static Color RED(0xff,0x00,0x00);
static Color GREEN(0x00,0xff,0x00);
static Color BLUE(0x00,0x00,0xff);
static Color LIGHTBLUE(0x44,0x44,0xff);
static Color BLACK(0x00,0x00,0x00);
static Color WHITE(0xff,0xff,0xff);
static Color BROWN(0x83,0x64,0x3e);
//static Color LIGHTBROWN(0xc2,0x9b,0x6c);
static Color LIGHTBROWN(0xd3,0xac,0x7d);

};
