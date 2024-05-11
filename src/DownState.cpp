#include "DownState.h"

void DownState::initScore()
{
	this->prev_score = 0;
	this->score = 0;
	this->scoreblock.setFillColor(sf::Color(255, 255, 255, 255));
	this->scoreblock.setPosition(sf::Vector2f(this->backToMenu->getXPosition() + this->backToMenu->getWidth(), this->backToMenu->getYPosition()));
	this->scoreblock.setSize(sf::Vector2f(100, this->backToMenu->getHeight()));
	
	this->scoreText.setString("00:00");
	this->scoreText.setFillColor(sf::Color::Black);
	this->scoreText.setCharacterSize(35);
	this->scoreText.setFont(*this->font);
	this->scoreText.setPosition(
		this->scoreblock.getPosition().x + 10,
		this->scoreblock.getPosition().y + this->scoreblock.getGlobalBounds().height / 2.f - this->scoreblock.getGlobalBounds().height / 2.f + 5
	);
}

void DownState::initWords()
{
	this->wordchange = false;
	this->wordsblock.setFillColor(sf::Color(255, 255, 255, 255));
	this->wordsblock.setTexture(&this->words[0]);
	this->wordsblock.setPosition(sf::Vector2f(this->scoreblock.getPosition().x + this->scoreblock.getSize().x, this->backToMenu->getYPosition()));
	this->wordsblock.setSize(sf::Vector2f(this->window->getSize().x - this->wordsblock.getPosition().x, this->backToMenu->getHeight()));
}

void DownState::initButtons()
{
	this->backToMenu = new Button(0, 750, 50, 50, "<", this->font, 30,
		sf::Color(100, 100, 100, 200), sf::Color(20, 20, 20, 250), sf::Color(220, 220, 220, 50),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
}

void DownState::initBackground()
{
	this->background.setTexture(&this->textures["BACKGROUND"]);
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

void DownState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("../resource/images/background2.png");
	this->textures["BACKGROUND"] = temp;
	temp.loadFromFile("../resource/images/cm kuan left.png");
	this->textures["CM_KUAN_L"] = temp;
	temp.loadFromFile("../resource/images/cm kuan right.png");
	this->textures["CM_KUAN_R"] = temp;
	temp.loadFromFile("../resource/images/platform2.png");
	this->textures["OSTAIR"] = temp;
}

void DownState::initCMKuan()
{
	this->prev_state = false;
	this->curr_state = false;
	this->cmkuan = new CMKuan(250, 100, &this->textures["CM_KUAN_L"]);
	this->blood = 10;
	this->hurt = false;
}

void DownState::initOStairs(int stair_n)
{
	this->stair_n = stair_n;
	this->oStair = new OrdinaryStair[stair_n];

	this->oStair[0].createSprite(&this->textures["OSTAIR"]);
	this->oStair[0].setPosition(250, this->textures["CM_KUAN_L"].getSize().y + 100);

	int gap = (this->window->getSize().y - this->backToMenu->getHeight()) / (float)stair_n;

	for (int i = 1; i < stair_n; i++)
	{
		this->oStair[i].createSprite(&this->textures["OSTAIR"]);
		this->oStair[i].setPosition(rand() % (this->window->getSize().x - this->textures["OSTAIR"].getSize().x ),
			gap * i + this->textures["OSTAIR"].getSize().y + rand() % (gap - this->textures["OSTAIR"].getSize().y));
	}
}

DownState::DownState(sf::RenderWindow* window, std::stack<State*>* states,int stair_n)
	:State(window, states)
{
	this->initTextures();
	this->initButtons();
	this->initBackground();
	this->initCMKuan();
	this->initOStairs(stair_n);
	this->initScore();
	this->initWords();
}

DownState::~DownState()
{
	delete this->backToMenu;
	delete this->cmkuan;
	delete [] this->oStair;
}

void DownState::endState()
{
	std::cout << "Ending DownState!\n";
}

void DownState::updateKeybinds(const float& dt)
{

	this->checkForQuit();
}

void DownState::updateButtons()
{
	backToMenu->update(this->mousePosView);

	if (this->backToMenu->isPressed())
	{
		std::cout << "Returning back to MainMenuState\n";
		this->states->pop();
	}
}

void DownState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->cmkuan->move(dt, -this->x_speed, 0.f);
		this->cmkuan->changeTexture(&this->textures["CM_KUAN_L"]);
	}
		

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->cmkuan->move(dt, this->x_speed, 0.f);
		this->cmkuan->changeTexture(&this->textures["CM_KUAN_R"]);
	}
}

void DownState::updateCMKuan(const float& dt)
{
	this->prev_state = this->curr_state;
	if (this->cmkuan->getXPosition() > this->window->getSize().x)
	{
		this->cmkuan->setPosition(0, this->cmkuan->getYPosition());
	}
	if (this->cmkuan->getXPosition() < 0)
	{
		this->cmkuan->setPosition(this->window->getSize().x, this->cmkuan->getYPosition());
	}
	bool touch = false;
	for (int i = 0; i < this->stair_n; i++)
	{
		if ((this->cmkuan->getXPosition() >= this->oStair[i].getXPosition() - this->textures["CM_KUAN_L"].getSize().x) &&
			(this->cmkuan->getXPosition() <= this->oStair[i].getXPosition() + this->textures["OSTAIR"].getSize().x) &&
			(this->cmkuan->getYPosition() + this->textures["CM_KUAN_L"].getSize().y >= this->oStair[i].getYPosition()) &&
			(this->cmkuan->getYPosition() + this->textures["CM_KUAN_L"].getSize().y <= this->oStair[i].getYPosition() + this->textures["OSTAIR"].getSize().y))
		{
			touch = true;
			if (this->cmkuan->getYPosition() > 0)
				this->cmkuan->setPosition(this->cmkuan->getXPosition(),
											this->oStair[i].getYPosition() - this->textures["CM_KUAN_L"].getSize().y);
			this->curr_state = true;
		}
			
	}
	if (!touch)
	{
		this->cmkuan->move(dt, 0.f, this->falling_speed);
		this->curr_state = false;
		if (this->cmkuan->getYPosition() > 0)
			this->hurt = false;
	}
	else
	{
		this->prev_score = this->score;
		if (this->prev_state != this->curr_state)
			this->score++;
	}

	if (this->cmkuan->getYPosition() <= 0 && !this->hurt)
	{
		blood--;
		this->hurt = true;
	}

	if (this->cmkuan->getYPosition() >= this->window->getSize().y - this->backToMenu->getHeight())
	{
		this->blood = 0;
	}
}

void DownState::updateOstair(const float& dt)
{
	for (int i = 0; i < this->stair_n; i++)
	{
		oStair[i].move(dt, 0.f, this->stair_speed);
		if (oStair[i].getYPosition() < 0)
			oStair[i].setPosition(rand() % (this->window->getSize().x - this->textures["OSTAIR"].getSize().x),
				this->window->getSize().y - this->backToMenu->getHeight() - this->textures["OSTAIR"].getSize().y);
	}
}

void DownState::updateScore()
{
	std::string a;
	if (this->blood < 10)
		a += "0" + std::to_string(this->blood % 100);
	else
		a += std::to_string(this->blood % 100);
	a += ":";
	if ((this->score % 100) < 10)
		a += "0" + std::to_string(this->score % 100);
	else
		a += std::to_string(this->score % 100);
	
	this->scoreText.setString(a);
}

void DownState::updateWords()
{
	if (this->prev_score < this->score && !this->wordchange && this->prev_state != this->curr_state)
	{
		this->wordsblock.setTexture(&this->words[rand() % this->words_n]);
		this->wordchange = true;
	}
	else
	{
		this->wordchange = false;
	}
	if (blood <= 0)
		this->wordsblock.setTexture(this->word_dead);
}

void DownState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeybinds(dt);
	this->updateButtons();
	if (this->blood != 0)
	{
		this->updateInput(dt);
		this->updateCMKuan(dt);
		this->updateOstair(dt);
		this->updateScore();
	}
	this->updateWords();
}

void DownState::renderButtons(sf::RenderTarget* target)
{
	this->backToMenu->render(target);
}

void DownState::renderCMKuan(sf::RenderTarget* target)
{
	this->cmkuan->render(target);
}

void DownState::renderOStair(sf::RenderTarget* target)
{
	for (int i = 0; i < this->stair_n; i++)
	{
		this->oStair[i].render(target);
	}
}

void DownState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderOStair(target);
	this->renderCMKuan(target);
	this->renderButtons(target);
	target->draw(this->scoreblock);
	target->draw(this->scoreText);
	target->draw(this->wordsblock);
}
