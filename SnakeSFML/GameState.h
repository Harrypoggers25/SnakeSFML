#pragma once
#include "State.h"
#include <vector>

class GameState :
    public State
{
private:
	std::vector<sf::RectangleShape*> cells;

public:
	GameState();

	void init();
	void updateEvent(const sf::Event& event);
	void update();
	void render(sf::RenderTarget* window);
	bool changeState(std::stack<State*>* states);
};

