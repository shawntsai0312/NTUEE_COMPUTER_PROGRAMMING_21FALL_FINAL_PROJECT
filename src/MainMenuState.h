#pragma once
#include "State.h"
#include "UpState.h"
#include "DownState.h"
#include "Button.h"
class MainMenuState :
    public State
{
private:
    std::map<std::string, Button*> buttons;

	const int up_stair = 10;
	const int down_stair = 15;

    void initButtons();
    void initBackground();
public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~MainMenuState();

    void endState();

    void updateKeybinds(const float& dt);
    void updateButtons();
    void update(const float& dt);

    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};

