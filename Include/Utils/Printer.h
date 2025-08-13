#pragma once

#include <iostream>
#include <string>

namespace Printer {

inline void printRed(const std::string& text) {
	std::cerr << "\033[1;31m" << text << "\033[0m" << std::endl;
}

inline void printYellow(const std::string& text) {
	std::cout << "\033[1;33m" << text << "\033[0m" << std::endl;
}

inline void printGreen(const std::string& text) {
	std::cout << "\033[1;32m" << text << "\033[0m" << std::endl;
}

};
