#pragma once
#include "State.h"
#include <vector>

#define MAX_COLOR_SIZE 18

class GameState :
    public State
{
private:
	sf::Color colors[MAX_COLOR_SIZE];
	std::vector<sf::RectangleShape*> cells;
	std::vector<sf::Vector2i*> trail;
	unsigned int size;

	void resetSnake();
	void addTrail(const int& x, const int& y);
	void move(const int& dx, const int& dy);

public:
	GameState();
	virtual ~GameState();

	void init();
	void updateEvent(const sf::Event& event);
	void update();
	void render(sf::RenderTarget* window);
	bool changeState(std::stack<State*>* states);
};

