#include "GameState.h"

GameState::GameState()
{
	sf::Color colors[18] = {
		sf::Color(86, 255, 1),
		sf::Color(170, 255, 3),
		sf::Color(255, 255, 1),
		sf::Color(255, 170, 1),
		sf::Color(255, 84, 0),
		sf::Color(254, 0, 2),
		sf::Color(255, 0, 86),
		sf::Color(255, 0, 172),
		sf::Color(255, 0, 255),
		sf::Color(171, 1, 255),
		sf::Color(86, 0, 254),
		sf::Color(0, 0, 254),
		sf::Color(0, 85, 254),
		sf::Color(0, 170, 255),
		sf::Color(1, 255, 255),
		sf::Color(0, 255, 169),
		sf::Color(0, 255, 85),
		sf::Color(1, 255, 2)
	};
	for (size_t i = 0; i < 25; i++) {
		this->cells.push_back(new sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
		this->cells.back()->setFillColor(colors[i % 18]);
		this->cells.back()->setPosition(i * 25, 0);
	}
}

void GameState::init()
{
}

void GameState::updateEvent(const sf::Event& event)
{
}

void GameState::update()
{
}

void GameState::render(sf::RenderTarget* window)
{
	for (size_t i = 0; i < this->cells.size(); i++) {
		window->draw(*this->cells[i]);
	}
}

bool GameState::changeState(std::stack<State*>* states)
{
	return false;
}
