#include "GameState.h"
#include <iostream>

void GameState::resetSnake()
{
	this->size = 0;
	while (!this->cells.empty()) {
		delete this->cells.back();
		this->cells.pop_back();
	}
	this->trail.clear();
}

void GameState::addTrail(const int& x, const int& y)
{
	this->cells.push_back(new sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
	int index = this->size++ % MAX_COLOR_SIZE * 2;
	this->cells.back()->setFillColor(this->colors[index < MAX_COLOR_SIZE ? index : MAX_COLOR_SIZE * 2 - 1 - index]);
}

void GameState::move(const char& key)
{
	auto pos = this->trail.front();
	int dx = 0, dy = 0;
	switch (key)
	{
	case 'w':
		dy = -1;
		break;
	case 'a':
		dx = -1;
		break;
	case 's':
		dy = 1;
		break;
	case 'd':
		dx = 1;
		break;
	}
	this->dir = key;
	pos = pos + sf::Vector2i(dx, dy);

	addTrail(pos.x, pos.y);
	this->trail.insert(this->trail.begin(), pos);
}

GameState::GameState()
{
	int r = 0, g = 255;
	for (int i = 0; i < MAX_COLOR_SIZE / 2; i++) {
		this->colors[i] = sf::Color(r, g, 0);
		r += 15;
	}
	for (int i = 0; i < MAX_COLOR_SIZE / 2; i++) {
		this->colors[i + MAX_COLOR_SIZE / 2] = sf::Color(r, g, 0);
		g -= 15;
	}
	this->init();
}

GameState::~GameState()
{
	this->resetSnake();
}

void GameState::init()
{
	// Reset values
	this->resetSnake();
	this->addTrail(15, 15);
	this->trail.push_back(sf::Vector2i(15, 15));
	this->dir = '0';
}

void GameState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->dir != 's') this->move('w');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->dir != 'd') this->move('a');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->dir != 'w') this->move('s');
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->dir != 'a') this->move('d');
	}
}

void GameState::update()
{
}

void GameState::render(sf::RenderTarget* window)
{
	for (size_t i = 0; i < this->cells.size(); i++) {
		auto pos = sf::Vector2f(
			(float)this->trail[i].x * 25.f, 
			(float)this->trail[i].y * 25.f
		);
		this->cells[i]->setPosition(pos);
		window->draw(*this->cells[i]);
	}
}

bool GameState::changeState(std::stack<State*>* states)
{
	return false;
}
