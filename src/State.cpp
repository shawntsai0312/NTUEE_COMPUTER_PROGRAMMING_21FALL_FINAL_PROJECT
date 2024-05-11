#include "State.h"

void State::initWords()
{
	this->words = new sf::Texture[this->words_n];
	for (int i = 0; i < this->words_n; i++)
	{
		sf::Texture temp;
		std::string tempPos = "../resource/words/word";
		tempPos += std::to_string(i + 1);
		tempPos += ".png";
		temp.loadFromFile(tempPos);
		this->words[i] = temp;
	}
	this->word_dead = new sf::Texture;
	this->word_dead->loadFromFile("../resource/words/word_dead.png");
}

//Constructors and Destructors
State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
	this->font = new sf::Font;
	this->font->loadFromFile("fonts/msjh.ttc");
	this->initWords();
}

State::~State()
{
	delete this->font;
	delete [] this->words;
	delete this->word_dead;
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
