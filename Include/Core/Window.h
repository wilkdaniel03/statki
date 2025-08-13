#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <thread>

#include "Core/Globals.h"
#include "Core/Mouse.h"
#include "Core/Board.h"
#include "Errors/SDLError.h"
#include "Errors/FileSystemError.h"
#include "Graphics/Renderer.h"
#include "Graphics/Rectangle.h"
#include "Graphics/Texture.h"
#include "Graphics/BmpTexture.h"
#include "UI/Element.h"
#include "UI/Button.h"
#include "UI/Widget.h"
#include "UI/Grid.h"

#include <SDL2/SDL.h>

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGHT = 1080;

class Window {
	float ratio = 1.0;
	SDL_Window *win = nullptr;
	int framerate = -1;
	std::chrono::time_point<std::chrono::high_resolution_clock> lasttime;

public:
	Window() {
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			throw Errors::SDLError("Failed to init SDL");
		}
	};

	Window(const float ratio) : Window() {
		if(ratio < 0.0 || ratio > 1.0) {
			throw std::runtime_error("Failed to create window object: ratio must be specified between 0 and 1");
		}

		this->ratio = ratio;
	}

	void Show();

	~Window() {
		SDL_DestroyWindow(this->win);
		SDL_Quit();
	}
};
