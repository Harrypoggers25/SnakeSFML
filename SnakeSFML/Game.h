#pragma once
#include <stack>
#include "State.h"

class Game
{
public:
	Game(std::string title = "", unsigned int w = 400, unsigned int h = 400, State* state = nullptr);
	virtual ~Game();
	void run();
	void setInitialState(State* state);
	void setWindow(std::string title, unsigned int w = 0, unsigned int h = 0);

private:
	sf::RenderWindow* window;
	std::stack<State*>* states;

	void init();
	void updateEvent();
	void update();
	void render();
};

