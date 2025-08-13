#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <SDL2/SDL.h>

class Mouse {
	int x,y;
	int onClickX,onClickY;
	bool wasMoved = false;
	bool isClicked = false;
public:
	Mouse() {}
	Mouse(const int x, const int y) : x(x), y(y) {}

	int operator[](int index) const {
		if(index == 0) {
			return this->x;
		} else if(index == 1) {
			return this->y;
		}

		throw std::runtime_error("Index of Mouse cannot be bigger than 1");
	}

	void UpdateState() {
		SDL_GetMouseState(&this->x,&this->y);
	}

	void Mark() {
		this->onClickX = this->x;
		this->onClickY = this->y;
	}

	bool GetIsClicked() const {
		return this->isClicked;
	}

	void SetIsClicked(bool val) {
		this->isClicked = val;
		this->onClickX = this->x;
		this->onClickY = this->y;
	}

	bool GetWasMoved() const {
		return this->wasMoved;
	}

	void SetWasMoved(bool val) {
		this->wasMoved = val;
	}

	int GetOnClickX() const {
		return this->onClickX;
	}

	int GetOnClickY() const {
		return this->onClickY;
	}

	~Mouse() {}
};

inline std::ostream& operator<<(std::ostream& out, Mouse& mouse) {
	std::stringstream stream;

	stream << "Mouse -> x: " << mouse[0] << ", y: " << mouse[1];

	return out << stream.str();
}
