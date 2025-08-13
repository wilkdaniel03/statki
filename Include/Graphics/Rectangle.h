#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <memory>

#include "Graphics/Point.hh"
#include "Utils/Color.h"

#include <SDL2/SDL.h>

/// Class being used as abstraction around SDL rectangles
class Rectangle {
	SDL_Rect rect;
	Color color;
public:
	Rectangle() {}
	Rectangle(const std::array<Point,4>& points, const Color& color) :
		rect({ points[0][0], points[0][1], (points[1][0] - points[0][0]), (points[3][1] - points[0][1])}),
		color(color)
	{}

	SDL_Rect* operator*() {
		return &this->rect;
	}

	const Color GetColor() const {
		return this->color;
	}

	void SetColor(const Color color) {
		this->color = color;
	}

	void SetAlpha(const unsigned int alpha) {
		this->color.SetAlpha(alpha);
	}

};
