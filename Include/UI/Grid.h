#pragma once

#include <vector>

#include "Core/Mouse.h"
#include "Graphics/Point.hh"
#include "Graphics/Rectangle.h"
#include "Utils/Color.h"
#include "UI/Element.h"
#include "UI/Button.h"

class Grid {
	std::vector<Element*> mat;
public:
	Grid() {
		mat.push_back(new Button({Point(-0.5,0.5),Point(0.5,0.5),Point(0.5,-0.5),Point(-0.5,-0.5)},{Colors::RED,Colors::BLUE,Colors::RED},255));
	}

	Grid(const unsigned int rows, const unsigned int cols) {
		float cellWidth = 1.4 / cols;
		float cellHeight = 1.4 / rows;

		float currentX = -0.7;
		float currentY = 0.7;

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				this->mat.push_back(
					new Button({
						Point(currentX,currentY),
						Point(currentX+cellWidth,currentY-cellHeight),
						Point(currentX+cellWidth,currentY-cellHeight),
						Point(currentX,currentY-cellHeight)},
						{Colors::BLUE,Colors::BLUE,Colors::RED},100)
				);
				currentX += cellWidth;
			}
			currentX = -0.7;
			currentY -= cellHeight;
		}
	}

	std::vector<Rectangle> GetRenderInfo() const {
		std::vector<Rectangle> res;

		for(int i = 0; i < this->mat.size(); i++) {
			auto rects = this->mat[i]->GetRenderInfo();
			res.insert(res.end(),rects.begin(),rects.end());
		}

		return res;
	}

	void CheckMouse(Mouse& mouse, bool isClicked) {
		for(int i = 0; i < this->mat.size(); i++) {
			this->mat[i]->CheckMousePos(mouse);
		}
	}

	std::vector<Element*>& GetMatrix() {
		return this->mat;
	}

	~Grid() {
		for(int i = 0; i < this->mat.size(); i++) {
			delete this->mat[i];
		}
	}
};
