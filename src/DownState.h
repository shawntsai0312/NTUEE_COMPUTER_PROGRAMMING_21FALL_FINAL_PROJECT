#pragma once
#include "State.h"
#include "Button.h"
#include "CMKuan.h"
#include "OrdinaryStair.h"
class DownState :
    public State
{
private:
    sf::RectangleShape background;
	sf::RectangleShape scoreblock;
	sf::RectangleShape wordsblock;

    Button* backToMenu;

    CMKuan* cmkuan;
	bool prev_state;
	bool curr_state;
	//true for falling

	int prev_score;
	int score;
	bool wordchange;
	sf::Text scoreText;

	int blood;
	bool hurt;

    OrdinaryStair* oStair;
    int stair_n;
	const float stair_speed = -3;
	const float falling_speed = 3;
	const float x_speed = 3;

    void initButtons();
    void initBackground();
    void initTextures();
    void initCMKuan();
    void initOStairs(int stair_n);
	void initScore();
	void initWords();

public:
    DownState(sf::RenderWindow* window, std::stack<State*>* states,int stair_n);
    virtual ~DownState();

    void endState();

    void updateKeybinds(const float& dt);
    void updateButtons();
    void updateInput(const float& dt);
    void updateCMKuan(const float& dt);
    void updateOstair(const float& dt);
	void updateScore();
	void updateWords();
    void update(const float& dt);

    void renderButtons(sf::RenderTarget* target = NULL);
    void renderCMKuan(sf::RenderTarget* target = NULL);
    void renderOStair(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};