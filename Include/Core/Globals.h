#pragma once

#include <iostream>
#include <sstream>

/// Structure being used as helpful source for commonly used data in multiple places

struct Globals {
	int winWidth,winHeight;
};

inline std::ostream& operator<<(std::ostream& out, Globals& globals) {
	std::stringstream stream;

	stream << "width: " << globals.winWidth << " , height: " << globals.winHeight;

	return out << stream.str();
}

inline Globals globals = {};
