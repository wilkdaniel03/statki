#pragma once

#include <array>
#include <vector>
#include <memory>

#include "Core/Mouse.h"
#include "Graphics/Point.hh"
#include "Graphics/Rectangle.h"
#include "Graphics/Texture.h"
#include "UI/Element.h"

class Button : public Element {
	Rectangle rect;
	std::array<Color,3> colors;
	unsigned int alpha;
public:
	Button() {}
	Button(const Rectangle& rect, const std::array<Color,3> colors, const unsigned int alpha) :
		rect(rect), colors(colors), alpha(alpha)
	{
		this->colors[0].SetAlpha(alpha);
		this->colors[1].SetAlpha(alpha);
		this->colors[2].SetAlpha(alpha);
	}

	Button(const std::array<Point,4> points, const std::array<Color,3> colors, const unsigned int alpha) :
		rect(Rectangle(points,colors[0])), colors(colors), alpha(alpha)
	{
		this->colors[0].SetAlpha(alpha);
		this->colors[1].SetAlpha(alpha);
		this->colors[2].SetAlpha(alpha);
	}

	std::vector<Rectangle> GetRenderInfo() override {
		return std::vector<Rectangle>{ this->rect };
	}

	bool CheckMousePos(Mouse& mouse) override {
		auto rect = *this->rect;
		bool isInside = mouse[0] > rect->x && mouse[0] < rect->x + rect->w && mouse[1] > rect->y && mouse[1] < rect->y + rect->h;
		if(isInside && mouse.GetIsClicked()) {
			this->rect.SetColor(this->colors[2]);
			return true;
		} else if(isInside) {
			this->rect.SetColor(this->colors[1]);
			return true;
		} else {
			this->rect.SetColor(this->colors[0]);
		}

		return false;
	}

	void AttachTexture(const Texture& texture) {}

	void SetColor(const std::array<Color,3> colors, const unsigned int alpha) {
		this->colors[0] = colors[0];
		this->colors[1] = colors[1];
		this->colors[2] = colors[2];

		this->colors[0].SetAlpha(alpha);
		this->colors[1].SetAlpha(alpha);
		this->colors[2].SetAlpha(alpha);
	}

	Rectangle& GetRawRect() {
		return this->rect;
	}

	~Button() {}
};
