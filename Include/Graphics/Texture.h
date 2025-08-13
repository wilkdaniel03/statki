#pragma once

#include <SDL2/SDL.h>

// Abstract class being use in any texture
class Texture {
public:
	virtual SDL_Texture* GetRawTexture() const = 0;

	~Texture() {}
};
