#include "Graphics/Point.hh"

int Point::convertX(const float val) {
	int midpoint = globals.winWidth / 2;

	int res;

	if(val < 0) {
		res = globals.winWidth * (1 - std::abs(val)) / 2;
	} else if(val > 0) {
		res = midpoint + globals.winWidth * std::abs(val) / 2;
	} else {
		res = midpoint;
	}

	return res;
}

int Point::convertY(const float val) {
	int midpoint = globals.winHeight / 2;

	int res;

	if(val < 0) {
		res = midpoint + globals.winHeight * std::abs(val) / 2;
	} else if(val > 0) {
		res = globals.winHeight * (1 - std::abs(val)) / 2;
	} else {
		res = midpoint;
	}

	return res;
}
