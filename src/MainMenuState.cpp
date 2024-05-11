#include "MainMenuState.h"

void MainMenuState::initButtons()
{
	this->buttons["UP_STATE"] = new Button(200, 300, 200, 80, "UP", this->font, 35,
		sf::Color(40, 40, 40, 220), sf::Color(0, 0, 0, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["DOWN_STATE"] = new Button(200, 475, 200, 80, "DOWN", this->font, 35,
		sf::Color(40, 40, 40, 220), sf::Color(0, 0, 0, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(200, 650, 200, 80, "QUIT", this->font, 35,
		sf::Color(40, 40, 40, 220), sf::Color(0, 0, 0, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::initBackground()
{
	this->tBackground = new sf::Texture;
	this->tBackground->loadFromFile("../resource/images/menu.png");
	this->background.setTexture(tBackground);
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	this->initButtons();
	this->initBackground();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	delete tBackground;
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!\n";
}

void MainMenuState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	//Up
	if (this->buttons["UP_STATE"]->isPressed())
	{
		std::cout << "Entering Upstate\n";
		this->states->push(new UpState(this->window, this->states, this->up_stair));
	}
	//Down
	if (this->buttons["DOWN_STATE"]->isPressed())
	{
		std::cout << "Entering Downstate\n";
		this->states->push(new DownState(this->window, this->states, this->down_stair));
	}
	//Quit
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeybinds(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(target);
}
