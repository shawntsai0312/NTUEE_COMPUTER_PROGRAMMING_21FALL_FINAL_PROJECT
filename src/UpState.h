#pragma once
#include "State.h"
#include "Button.h"
#include "CMKuan.h"
#include "OrdinaryStair.h"
class UpState :
	public State
{
private:
	sf::RectangleShape background;
	sf::RectangleShape scoreblock;
	sf::RectangleShape wordsblock;

	Button* backToMenu;

	CMKuan* cmkuan;
	
	const float jump_speed = -5.5;
	const float x_speed = 3;
	float vy;
	float delta_h;

	int score;
	int prev_score;
	bool wordchange;
	sf::Text scoreText;

	int blood;
	bool hurt;

	OrdinaryStair* oStair;
	int stair_n;
	int curr_stair;
	const float stair_speed = 3;

	void initButtons();
	void initBackground();
	void initTextures();
	void initCMKuan();
	void initOStairs(int stair_n);
	void initScore();
	void initWords();

public:
	UpState(sf::RenderWindow* window, std::stack<State*>* states, int stair_n);
	virtual ~UpState();

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