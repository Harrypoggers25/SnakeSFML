#include "Game.h"

Game::Game(std::string title, unsigned int w, unsigned int h, State* state)
{
	this->states = new std::stack<State*>;
	this->window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Titlebar | sf::Style::Close);
	this->setInitialState(state);
}

Game::~Game()
{
	delete this->window;
	while (!this->states->empty()) {
		delete this->states->top();
		this->states->pop();
	}
	delete this->states;
}

void Game::run()
{
	this->init();
	while (this->window->isOpen()) {
		this->updateEvent();
		this->update();
		this->render();
	}
}

void Game::setInitialState(State* state)
{
	if (state != nullptr && this->states->empty()) this->states->push(state);
}

void Game::setWindow(std::string title, unsigned int w, unsigned int h)
{
	this->window->setTitle(title);
	if (w != 0 && h != 0) this->window->setSize(sf::Vector2u(w, h));
}

void Game::init()
{
}

void Game::updateEvent()
{
	sf::Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) this->window->close();
		if (!this->states->empty()) this->states->top()->updateEvent(event);
	}
}

void Game::update()
{
	if (!this->states->empty()) {
		this->states->top()->update();
		if (this->states->top()->isChangedState) {
			if (this->states->top()->changeState(this->states)) {
				delete this->states->top();
				this->states->pop();
				this->states->top()->isChangedState = false;
			}
		}
	}

}

void Game::render()
{
	this->window->clear();

	if (!this->states->empty()) this->states->top()->render(this->window);

	this->window->display();
}
