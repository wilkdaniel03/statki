#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

#include "SDL2/SDL.h"

namespace Errors {

/// Helpful wrapper around SDL
/// The idea is to call runtime_error constructor using stream outputted from stringstream which contains error message
class SDLError : public std::runtime_error {
	std::string init(const std::string& error) {
		std::stringstream stream;
		stream << "[SDL] " << error << ". " << SDL_GetError();
		return stream.str();
	}
public:
	SDLError(const std::string error) : std::runtime_error(init(error)) {}
};

};
