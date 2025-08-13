#pragma once

#include <vector>
#include <memory>

#include "Core/Mouse.h"
#include "Graphics/Rectangle.h"
#include "UI/Element.h"
#include "UI/Grid.h"

enum class BOARD_TYPE {
	PLAYER,
	OPPONENT
};

class Board {
	std::vector<std::vector<int>> ships;
	std::vector<std::pair<Element*,bool>> mat;
	int selected = -1;
	BOARD_TYPE type;
	int points = 20;
	std::string player;
public:
	Board() {}
	Board(BOARD_TYPE type, const unsigned int rows, const unsigned int cols, const float startX, std::vector<std::vector<int>>& ships,const std::string& player) :
		type(type),
		ships(ships),
		player(player)
	{
		float cellWidth = 0.7 / cols;
		float cellHeight = 1.4 / rows;

		float currentX = startX;
		float currentY = 0.7;

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				Color color;
				int alpha = 100;
				if(ships[i][j] == 0) {
					color = Colors::BLUE;
				} else if(ships[i][j] == 1) {
					color = Colors::BROWN;
					alpha = 255;
				} else if(ships[i][j] == 2) {
					color = Colors::GREEN;
				} else {
					color = Colors::RED;
				}

				this->mat.push_back(
					std::make_pair(
						new Button({
							Point(currentX,currentY),
							Point(currentX+cellWidth,currentY-cellHeight),
							Point(currentX+cellWidth,currentY-cellHeight),
							Point(currentX,currentY-cellHeight)},
							{color,color,Colors::LIGHTBLUE},alpha),
						false
					)
				);
				currentX += cellWidth;
			}
			currentX = startX;
			currentY -= cellHeight;
		}
	}

	void CheckMouse(Mouse& mouse, bool isClicked) {
		for(int i = 0; i < this->mat.size(); i++) {
			bool isInside = this->mat[i].first->CheckMousePos(mouse);
			if(isInside && !this->mat[i].second && isClicked && this->type == BOARD_TYPE::OPPONENT) {
				auto button = dynamic_cast<Button*>(this->mat[i].first);
				if(this->selected >= 0) {
					auto btn = dynamic_cast<Button*>(this->mat[this->selected].first);
					//btn->SetColor({Colors::BLUE,Colors::LIGHTBLUE,Colors::RED},100);
				}
				//button->SetColor({Colors::LIGHTBLUE,Colors::LIGHTBLUE,Colors::LIGHTBLUE},100);
				this->selected = i;
			}
		}
	}

	bool TryShot() {
		if(this->selected >= 0) {
			auto button = dynamic_cast<Button*>(this->mat[this->selected].first);
			int col = this->selected % 10;
			int row = this->selected / 10;

			if(this->ships[row][col] == 1) {
				this->ships[row][col] = 2;
				this->points--;
			} else if(this->ships[row][col] == 0) {
				this->ships[row][col] = 3;
			}

			//button->SetColor({Colors::RED,Colors::RED,Colors::RED},100);
			this->mat[this->selected].second = true;
			this->selected = -1;
			return true;
		}
		return false;
	}

	std::vector<Rectangle> GetRenderInfo() const {
		if(this->points == 0 && this->type == BOARD_TYPE::OPPONENT) {
			SDL_Delay(2000);
			std::cout << this->player << " won!" << std::endl;
			exit(0);
		}

		std::vector<Rectangle> res;

		for(int i = 0; i < this->ships.size(); i++) {
			for(int j = 0; j < this->ships[i].size(); j++) {
				auto current = dynamic_cast<Button*>(this->mat[i*10+j].first)->GetRawRect();

				if(this->ships[i][j] == 0) {
					current.SetColor(Colors::BLUE);
					current.SetAlpha(100);
				} else if(this->ships[i][j] == 1) {
					current.SetColor(Colors::BROWN);
					current.SetAlpha(255);
					if(this->type == BOARD_TYPE::OPPONENT) {
						current.SetColor(Colors::BLUE);
						current.SetAlpha(100);
					}
				} else if(this->ships[i][j] == 2) {
					current.SetColor(Colors::GREEN);
					current.SetAlpha(100);
				} else if(this->ships[i][j] == 3) {
					current.SetColor(Colors::RED);
					current.SetAlpha(100);
				}

				res.push_back(current);
			}
		}

		return res;
	}

	~Board() {}
};
