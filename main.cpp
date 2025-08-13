#include <iostream>
#include <vector>

#include "Utils/Printer.h"
#include "Core/Window.h"

int main(void) {
	std::unique_ptr<Window> win;
	try {
		win = std::make_unique<Window>(Window(0.95));
		win->Show();
	} catch(std::runtime_error& err) {
		Printer::printRed(err.what());
	}

	return 0;
}
