#pragma once
#include "State.h"
#include <vector>

#define MAX_COLOR_SIZE 34

class GameState :
    public State
{
private:
	sf::Color colors[MAX_COLOR_SIZE * 2];
	std::vector<sf::RectangleShape*> cells;
	std::vector<sf::Vector2i> trail;
	unsigned int size;
	char dir;


	void resetSnake();
	void addTrail(const int& x, const int& y);
	void move(const char& key);

public:
	GameState();
	virtual ~GameState();

	void init();
	void updateEvent(const sf::Event& event);
	void update();
	void render(sf::RenderTarget* window);
	bool changeState(std::stack<State*>* states);
};

