#pragma once

#include <memory>

#include "Errors/SDLError.h"
#include "Utils/Color.h"
#include "Graphics/Rectangle.h"
#include "Graphics/Texture.h"
#include "UI/Widget.h"

#include <SDL2/SDL.h>

/// Class being used as abstraction around SDL renderer
class Renderer {
	SDL_Renderer *renderer;
public:
	Renderer() {}
	Renderer(SDL_Window *win) : renderer(SDL_CreateRenderer(win,-1,0)) {
		if(!this->renderer) {
			throw Errors::SDLError("Failed to create renderer");
		}
	}

	void Clear() {
		SDL_SetRenderDrawColor(this->renderer,Colors::BLACK[0],Colors::BLACK[1],Colors::BLACK[2],Colors::BLACK[3]);
		SDL_RenderClear(this->renderer);
	}

	void DrawRectangle(Rectangle& rect) {
		Color color = rect.GetColor();
		SDL_SetRenderDrawColor(this->renderer,color[0],color[1],color[2],color[3]);
		SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderDrawRect(this->renderer,*rect);
		SDL_RenderFillRect(this->renderer,*rect);
	}

	void RenderClear() {
		SDL_SetRenderDrawColor(this->renderer,Colors::WHITE[0],Colors::WHITE[1],Colors::WHITE[2],Colors::WHITE[3]);
		SDL_RenderClear(this->renderer);
	}

	void LoadBackground(std::shared_ptr<Texture> texture) {
		SDL_RenderCopy(this->renderer,texture->GetRawTexture(),nullptr,nullptr);
	}

	void LoadTexture(std::shared_ptr<Texture> texture, Widget& element) {
		auto rects = element.GetRenderInfo();
		for(int i = 0; i < rects.size(); i++) {
			SDL_RenderCopy(this->renderer,texture->GetRawTexture(),nullptr,*rects[i]);
		}
	}

	void Present() {
		SDL_RenderPresent(this->renderer);
	}

	SDL_Renderer* operator*() const {
		return this->renderer;
	}

	~Renderer() {
		SDL_DestroyRenderer(this->renderer);
	}
};
