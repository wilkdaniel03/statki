#include "Core/Window.h"

/// Method being used to init necessary objects and run game the game loop
void Window::Show() {
	this->win = SDL_CreateWindow(
		"Statki",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		DEFAULT_WIDTH * this->ratio,
		DEFAULT_HEIGHT * this->ratio,
		0
	);

	if(!this->win) {
		throw Errors::SDLError("Failed to create window");
	}

	SDL_GetWindowSize(this->win,&globals.winWidth,&globals.winHeight);

	std::shared_ptr<Renderer> renderer(new Renderer(this->win));

	bool isRunning;

	std::array<std::vector<Rectangle>,2> data;
	unsigned int dataIdx = 0;

	Widget btn(
		new Button({Point(-0.3,0.3),Point(0.3,0.3),Point(-0.3,0.05),Point(0.3,0.05)},{Colors::LIGHTBROWN,Colors::BROWN,Colors::BROWN},255),
		[](){},
		[&dataIdx,&renderer]() mutable { dataIdx = 1; renderer->RenderClear(); renderer->Present(); }
	);

	Widget btn2(
		new Button({Point(-0.3,-0.05),Point(0.3,-0.05),Point(-0.3,-0.3),Point(0.3,-0.3)},{Colors::BROWN,Colors::LIGHTBROWN,Colors::BROWN},255),
		[]() {},
		[&isRunning]() mutable { isRunning = false; }
	);

	std::vector<std::vector<int>> p1Board{
		{ 0,0,0,0,1,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,1,0,0 },
		{ 0,1,0,1,1,1,0,0,0,0 },
		{ 0,1,0,0,0,0,0,1,0,0 },
		{ 0,1,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,1 }
	};

	std::vector<std::vector<int>> p2Board{
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 1,0,1,0,1,0,0,0,1,1 },
		{ 1,0,1,0,1,0,0,0,0,0 },
		{ 0,0,1,0,1,0,1,0,0,0 },
		{ 0,0,0,0,1,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,1 }
	};

	std::array<std::pair<Board*,Board*>,2> boards{
		std::make_pair(new Board(BOARD_TYPE::PLAYER,10,10,-0.7,p1Board,"Player 1"),new Board(BOARD_TYPE::OPPONENT,10,10,0.1,p2Board,"Player 1")),
		std::make_pair(new Board(BOARD_TYPE::PLAYER,10,10,-0.7,p2Board,"Player 2"),new Board(BOARD_TYPE::OPPONENT,10,10,0.1,p1Board,"Player 2")),
	};

	std::shared_ptr<Texture> background(new BmpTexture("Assets/Textures/Background.bmp",renderer));
	std::shared_ptr<Texture> gameBackground(new BmpTexture("Assets/Textures/Background2.bmp",renderer));
	std::shared_ptr<Texture> play(new BmpTexture("Assets/Textures/Play.bmp",renderer));
	std::shared_ptr<Texture> exit(new BmpTexture("Assets/Textures/Exit.bmp",renderer));
	std::shared_ptr<Texture> p1TurnTxt(new BmpTexture("Assets/Textures/P1turn.bmp",renderer));
	std::shared_ptr<Texture> p2TurnTxt(new BmpTexture("Assets/Textures/P2turn.bmp",renderer));
	std::shared_ptr<Texture> approvedTxt(new BmpTexture("Assets/Textures/Approved.bmp",renderer));

	Rectangle p1Turn({Point(-1.0,1.0),Point(-0.5,1.0),Point(-0.5,0.8),Point(-1.0,0.8)},Colors::BLACK);
	p1Turn.SetAlpha(0);

	//BoardGrid grid(12,12);

	bool isFirstPlayer = true;

	Widget approved(
		new Button({Point(-0.92,-0.5),Point(-0.77,-0.5),Point(-0.77,-0.7),Point(-0.92,-0.7)},{Colors::BLACK,Colors::BLACK,Colors::BLACK},0),
		[]() {},
		[&boards,&isFirstPlayer]() { 
			bool shoot;
			if(isFirstPlayer) {
				shoot = boards[0].second->TryShot(); 
			} else {
				shoot = boards[1].second->TryShot(); 
			}

			if(shoot) {
				isFirstPlayer = !isFirstPlayer;
			}
		}
	);

	Mouse mouse;

	isRunning = true;
	while(isRunning) {
		SDL_Event event;
		while(SDL_PollEvent(&event) > 0) {
			if(event.type == SDL_QUIT) {
				isRunning = false;
			} else if(event.type == SDL_MOUSEMOTION) {
				mouse.UpdateState();
				mouse.SetWasMoved(true);
			} else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				mouse.SetIsClicked(true);
			} else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
				mouse.SetIsClicked(false);
				//grid.Fit();
				//grid.FitAll();
			} else {
				mouse.SetWasMoved(false);
			}
		}

		renderer->Clear();

		if(dataIdx == 0) {

			btn.CheckMousePos(mouse);
			btn2.CheckMousePos(mouse);

			auto btnData = btn.GetRenderInfo();

			data[dataIdx].insert(data[dataIdx].end(),btnData.begin(),btnData.end());
			btnData = btn2.GetRenderInfo();
			data[dataIdx].insert(data[dataIdx].end(),btnData.begin(),btnData.end());

			renderer->LoadBackground(background);

			for(int i = 0; i < data[dataIdx].size(); i++) {
				renderer->DrawRectangle(data[dataIdx][i]);
			}

			SDL_RenderCopy(**renderer,play->GetRawTexture(),nullptr,*data[dataIdx][0]);
			SDL_RenderCopy(**renderer,exit->GetRawTexture(),nullptr,*data[dataIdx][1]);

		} else if(dataIdx == 1) {

			Board *board,*board2;

			if(isFirstPlayer) {
				board = boards[0].first;
				board2 = boards[0].second;
			} else {
				board = boards[1].first;
				board2 = boards[1].second;
			}

			board->CheckMouse(mouse,mouse.GetIsClicked());
			board2->CheckMouse(mouse,mouse.GetIsClicked());
			approved.CheckMousePos(mouse);
			
			auto boardData = board->GetRenderInfo();
			data[dataIdx].insert(data[dataIdx].end(),boardData.begin(),boardData.end());
			boardData = board2->GetRenderInfo();
			data[dataIdx].insert(data[dataIdx].end(),boardData.begin(),boardData.end());

			data[dataIdx].push_back(p1Turn);

			boardData = approved.GetRenderInfo();
			data[dataIdx].insert(data[dataIdx].end(),boardData.begin(),boardData.end());

			renderer->LoadBackground(gameBackground);

			for(int i = 0; i < data[dataIdx].size(); i++) {
				renderer->DrawRectangle(data[dataIdx][i]);
			}

			if(isFirstPlayer) {
				SDL_RenderCopy(**renderer,p1TurnTxt->GetRawTexture(),nullptr,*data[1][data[1].size()-2]);
			} else {
				SDL_RenderCopy(**renderer,p2TurnTxt->GetRawTexture(),nullptr,*data[1][data[1].size()-2]);
			}

			SDL_RenderCopy(**renderer,approvedTxt->GetRawTexture(),nullptr,*data[1][data[1].size()-1]);

		}

		renderer->Present();

		data[dataIdx].clear();
	}
}
