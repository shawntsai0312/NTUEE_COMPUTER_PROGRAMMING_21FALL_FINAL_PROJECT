#include "UpState.h"

void UpState::initScore()
{
	this->score = 0;
	this->prev_score = 0;
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

void UpState::initWords()
{
	this->wordchange = false;
	this->wordsblock.setFillColor(sf::Color(255, 255, 255, 255));
	this->wordsblock.setTexture(&this->words[0]);
	this->wordsblock.setPosition(sf::Vector2f(this->scoreblock.getPosition().x + this->scoreblock.getSize().x , this->backToMenu->getYPosition()));
	this->wordsblock.setSize(sf::Vector2f(this->window->getSize().x - this->wordsblock.getPosition().x , this->backToMenu->getHeight()));
}

void UpState::initButtons()
{
	this->backToMenu = new Button(0, 750, 50, 50, "<", this->font, 30,
		sf::Color(100, 100, 100, 200), sf::Color(20, 20, 20, 250), sf::Color(220, 220, 220, 50),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255));
}

void UpState::initBackground()
{
	this->background.setTexture(&this->textures["BACKGROUND"]);
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

void UpState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("./resource/images/background2.png");
	this->textures["BACKGROUND"] = temp;
	temp.loadFromFile("./resource/images/cm kuan left.png");
	this->textures["CM_KUAN_L"] = temp;
	temp.loadFromFile("./resource/images/cm kuan right.png");
	this->textures["CM_KUAN_R"] = temp;
	temp.loadFromFile("./resource/images/platform2.png");
	this->textures["OSTAIR"] = temp;
}

void UpState::initCMKuan()
{
	this->delta_h = 0;
	this->vy = 0;
	this->cmkuan = new CMKuan(250, 500, &this->textures["CM_KUAN_L"]);
	this->blood = 10;
	this->hurt = false;
}

void UpState::initOStairs(int stair_n)
{
	this->curr_stair = 0;
	this->stair_n = stair_n;
	this->oStair = new OrdinaryStair[stair_n];

	this->oStair[0].createSprite(&this->textures["OSTAIR"]);
	this->oStair[0].setPosition(250, this->textures["CM_KUAN_L"].getSize().y + 500);

	int gap = (this->window->getSize().y - this->backToMenu->getHeight()) / (float)stair_n;

	for (int i = 1; i < stair_n; i++)
	{
		this->oStair[i].createSprite(&this->textures["OSTAIR"]);
		this->oStair[i].setPosition(rand() % (this->window->getSize().x - this->textures["OSTAIR"].getSize().x),
			gap * i + this->textures["OSTAIR"].getSize().y + rand() % (gap - this->textures["OSTAIR"].getSize().y));
	}
}

UpState::UpState(sf::RenderWindow* window, std::stack<State*>* states, int stair_n)
	:State(window, states)
{
	srand(time(0));
	this->initTextures();
	this->initButtons();
	this->initBackground();
	this->initCMKuan();
	this->initOStairs(stair_n);
	this->initScore();
	this->initWords();
}

UpState::~UpState()
{
	delete this->backToMenu;
	delete this->cmkuan;
	delete[] this->oStair;
}

void UpState::endState()
{
	std::cout << "Ending UpState!\n";
}

void UpState::updateKeybinds(const float& dt)
{

	this->checkForQuit();
}

void UpState::updateButtons()
{
	backToMenu->update(this->mousePosView);

	if (this->backToMenu->isPressed())
	{
		std::cout << "Returning back to MainMenuState\n";
		this->states->pop();
	}
}

void UpState::updateInput(const float& dt)
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

void UpState::updateCMKuan(const float& dt)
{
	if (this->cmkuan->getXPosition() > this->window->getSize().x)
	{
		this->cmkuan->setPosition(0, this->cmkuan->getYPosition());
	}
	if (this->cmkuan->getXPosition() < 0)
	{
		this->cmkuan->setPosition(this->window->getSize().x, this->cmkuan->getYPosition());
	}
	bool touch = false;
	int now_stair_n = 0;
	for (int i = 0; i < this->stair_n; i++)
	{
		if ((this->cmkuan->getXPosition() >= this->oStair[i].getXPosition() - this->textures["CM_KUAN_L"].getSize().x) &&
			(this->cmkuan->getXPosition() <= this->oStair[i].getXPosition() + this->textures["OSTAIR"].getSize().x ) &&
			(this->cmkuan->getYPosition() + this->textures["CM_KUAN_L"].getSize().y >= this->oStair[i].getYPosition()) &&
			(this->cmkuan->getYPosition() + this->textures["CM_KUAN_L"].getSize().y <= this->oStair[i].getYPosition() + this->textures["OSTAIR"].getSize().y))
		{
			touch = true;
			now_stair_n = i;
		}

	}
	if (!touch)
	{
		this->delta_h += vy * dt;
		this->vy += 0.2;	//right hand side is the acceleration
		this->cmkuan->move(dt, 0.f, this->vy);
	}
	else
	{
		this->prev_score = this->score;
		if (now_stair_n != this->curr_stair && this->delta_h < 0)
		{
			this->score++;
			this->curr_stair = now_stair_n;
		}
		this->delta_h = 0;
		this->vy = this->jump_speed;
		this->cmkuan->move(dt, 0.f, this->vy);
		this->hurt = false;
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

void UpState::updateOstair(const float& dt)
{
	for (int i = 0; i < this->stair_n; i++)
	{
		oStair[i].move(dt, 0.f, 2.f);
		if (oStair[i].getYPosition() > this->window->getSize().y)
			oStair[i].setPosition(rand() % (this->window->getSize().x - this->textures["OSTAIR"].getSize().x), 0);
	}
}

void UpState::updateScore()
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

void UpState::updateWords()
{
	if (this->prev_score < this->score && !this->wordchange && this->vy == this->jump_speed)
	{
		this->wordsblock.setTexture(&this->words[rand() % this->words_n]);
		this->wordchange = true;
	}
	else
		this->wordchange = false;
	if (blood <= 0)
		this->wordsblock.setTexture(this->word_dead);
}

void UpState::update(const float& dt)
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

void UpState::renderButtons(sf::RenderTarget* target)
{
	this->backToMenu->render(target);
}

void UpState::renderCMKuan(sf::RenderTarget* target)
{
	this->cmkuan->render(target);
}

void UpState::renderOStair(sf::RenderTarget* target)
{
	for (int i = 0; i < this->stair_n; i++)
	{
		this->oStair[i].render(target);
	}
}

void UpState::render(sf::RenderTarget* target)
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
