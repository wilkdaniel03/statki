#pragma once

#include <stdexcept>
#include <cmath>

#include "Core/Globals.h"

/// Class being used to store points and map them into coordinates on screen
class Point {
	int x,y;

	int convertX(const float);
	int convertY(const float);
public:
	Point() {}
	Point(const float x, const float y) : x(this->convertX(x)), y(convertY(y)) {}

	int operator[](int index) const {
		if(index == 0) {
			return this->x;
		} else if(index == 1) {
			return this->y;
		}

		throw std::runtime_error("Index of point cannot be bigger than 2");
	}
};
