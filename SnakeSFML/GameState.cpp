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

	auto fpos = sf::Vector2i(
		(int)(this->fruit->getPosition().x / 25.f),
		(int)(this->fruit->getPosition().y / 25.f)
	);
	
	if (pos == fpos) {
		this->addFruit();
		this->addTrail(pos.x, pos.y);
	}
	else this->trail.pop_back();
	this->trail.insert(this->trail.begin(), pos);
}

void GameState::addFruit()
{
	sf::Vector2i pos;
	while (true) {
		pos = sf::Vector2i(
			(float)(rand() % 32), 
			(float)(rand() % 32)
		);
		auto isTrailExist = [](const std::vector<sf::Vector2i>& trail, const sf::Vector2i& pos) {
			for (size_t i = 0; i < trail.size(); i++) {
				if (trail[i] == pos) return true;
			}
			return false;
		};
		if (!isTrailExist(this->trail, pos)) break;
	}
	this->fruit->setPosition(
		(float) pos.x * 25.f,
		(float) pos.y * 25.f
	);
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
	this->fruit = new sf::CircleShape(12.5f);
	this->fruit->setFillColor(sf::Color::Red);
	this->init();
	std::srand((unsigned)time(0));
}

GameState::~GameState()
{
	this->resetSnake();
	delete this->fruit;
}

void GameState::init()
{
	// Reset values
	this->resetSnake();
	this->addTrail(15, 15);
	this->trail.push_back(sf::Vector2i(15, 15));
	this->dir = '0';
	this->addFruit();
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
	window->draw(*this->fruit);
}

bool GameState::changeState(std::stack<State*>* states)
{
	return false;
}
