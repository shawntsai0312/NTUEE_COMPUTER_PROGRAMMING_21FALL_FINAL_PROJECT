#include "Game.h"
//Initializer Function
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(600, 800), "CM Kuan with stairs");
	this->window->setFramerateLimit(60);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window,&this->states));
}

//Constructors and Destructors
Game::Game()
{
	srand(time(0));
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	//std::cout << this->dt << "\n";
}

//Functions
void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
