#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class State
{
protected:
	sf::Texture* tBackground;
	sf::RectangleShape background;

	std::stack<State*>* states;

	sf::Font* font;

	sf::RenderWindow* window;

	std::map < std::string, sf::Texture > textures;

	const int words_n = 15;
	sf::Texture* words;
	sf::Texture* word_dead;

	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	virtual void initBackground() = 0;
	virtual void initWords();

public: 
	//Constructors and Destructors
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateMousePosition();
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

