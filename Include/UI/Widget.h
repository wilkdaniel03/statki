#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include "Core/Mouse.h"
#include "UI/Element.h"
#include "Graphics/Rectangle.h"

class Widget {
	std::unique_ptr<Element> element;
	std::function<void()> onHover;
	std::function<void()> onClick;
public:
	Widget() {}

	Widget(Element *element, std::function<void()> f1, std::function<void()> f2) :
		element(element), onHover(f1), onClick(f2) {}

	void CheckMousePos(Mouse& mouse) {
		//if(!this->element->CheckMousePos(mouse)) return;

		bool isInside = this->element->CheckMousePos(mouse);

		if(isInside && mouse.GetIsClicked()) {
			this->onClick();
		} else {
			this->onHover();
		}
	}

	std::vector<Rectangle> GetRenderInfo() const {
		return this->element->GetRenderInfo();
	}

	~Widget() {}
};
