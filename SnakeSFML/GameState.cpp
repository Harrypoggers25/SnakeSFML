#include "GameState.h"
#include <iostream>

void GameState::resetSnake()
{
	this->size = 0;
	while (!this->cells.empty()) {
		delete this->cells.back();
		this->cells.pop_back();
	}
	while (!this->trail.empty()) {
		delete this->trail.back();
		this->trail.pop_back();
	}
}

void GameState::addTrail(const int& x, const int& y)
{
	this->cells.push_back(new sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
	this->cells.back()->setFillColor(this->colors[this->size++ % MAX_COLOR_SIZE]);
	this->trail.push_back(new sf::Vector2i(x, y));
}

void GameState::move(const int& dx, const int& dy)
{
	auto pos = this->trail.back();
	this->trail.pop_back();
	*pos = *pos + sf::Vector2i(dx, dy);
	this->trail.insert(this->trail.begin(), pos);
}

GameState::GameState()
{
	this->colors[0] = sf::Color(86, 255, 1),
	this->colors[1] = sf::Color(170, 255, 3);
	this->colors[2] = sf::Color(255, 255, 1);
	this->colors[3] = sf::Color(255, 170, 1);
	this->colors[4] = sf::Color(255, 84, 0);
	this->colors[5] = sf::Color(254, 0, 2);
	this->colors[6] = sf::Color(255, 0, 86);
	this->colors[7] = sf::Color(255, 0, 172);
	this->colors[8] = sf::Color(255, 0, 255);
	this->colors[9] = sf::Color(171, 1, 255);
	this->colors[10] = sf::Color(86, 0, 254);
	this->colors[11] = sf::Color(0, 0, 254);
	this->colors[12] = sf::Color(0, 85, 254);
	this->colors[13] = sf::Color(0, 170, 255);
	this->colors[14] = sf::Color(1, 255, 255);
	this->colors[15] = sf::Color(0, 255, 169);
	this->colors[16] = sf::Color(0, 255, 85);
	this->colors[17] = sf::Color(1, 255, 2);
	/*for (size_t i = 0; i < 25; i++) {
		this->cells.push_back(new sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
		this->cells.back()->setFillColor(colors[i % 18]);
		this->cells.back()->setPosition(i * 25, 0);
	}*/
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
}

void GameState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->move(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->move(0, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->move(1, 0);
	}
}

void GameState::update()
{
}

void GameState::render(sf::RenderTarget* window)
{
	for (size_t i = 0; i < this->cells.size(); i++) {
		auto pos = sf::Vector2f(
			(float)this->trail[i]->x * 25.f, 
			(float)this->trail[i]->y * 25.f
		);
		this->cells[i]->setPosition(pos);
		window->draw(*this->cells[i]);
	}
}

bool GameState::changeState(std::stack<State*>* states)
{
	return false;
}
