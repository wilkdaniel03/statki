#pragma once

#include <string>
#include <memory>

#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Errors/FileSystemError.h"

#include <SDL2/SDL.h>

/// Class implementing texture abstract class
/// Being used to parse and load bitmap into screen
class BmpTexture : public Texture {
	SDL_Surface *surface = nullptr;
	SDL_Texture *texture = nullptr;
public:
	BmpTexture() {}
	BmpTexture(const std::string& path, std::shared_ptr<Renderer> renderer) :
		surface(SDL_LoadBMP(path.c_str())),
		texture(SDL_CreateTextureFromSurface(**renderer,this->surface))
	{
		if(!this->surface) {
			throw Errors::FileSystemError(path,Errors::TYPE::FAILED_TO_FIND);
		}
	}

	SDL_Texture* GetRawTexture() const override {
		return this->texture;
	}
	
	~BmpTexture() {
		SDL_DestroyTexture(this->texture);
		SDL_FreeSurface(this->surface);
	}
};
