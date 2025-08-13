#pragma once

#include <vector>
#include <memory>

#include "Core/Mouse.h"
#include "Graphics/Rectangle.h"

enum class STATE {
	DEFAULT,
	HOVERED,
	CLICKED
};

class Element {
public:
	virtual std::vector<Rectangle> GetRenderInfo() = 0;
	virtual bool CheckMousePos(Mouse&) = 0;
	virtual ~Element() {}
};
