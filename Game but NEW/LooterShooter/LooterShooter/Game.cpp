#include "Game.h"

//private funtions
void Game::startWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Looter Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);


}

void Game::startTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}

void Game::startGUI()
{
	//load font
	if(!this->font.loadFromFile("Fonts/VarelaRound-Regular.ttf"));
	{
		std::cout << "Error::GAME::Failed to load font" << "\n";
	}

	//start point text
	this->pointText.setPosition(1100.f,25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//start player GUI
	this->playerHpBar.setSize(sf::Vector2f(100.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::startWorld()
{
	if(!this->worldBackgroundTex.loadFromFile("Textures/background.jpg"));
	{
		std::cout << "ERROR::GAME::CAN NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::startSystems()
{
	this->points = 0;
}

void Game::startPlayer()
{
	this->player = new Player();

}

void Game::startEnemies()
{
	this->spawnTimer = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//constructor //destructor
Game::Game()
{
	this->startWindow();
	this->startTextures();
	this->startGUI();
	this->startWorld();
	this->startSystems();
	this->startPlayer();
	this->startEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}
	
	//delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//delete enemies
	for (auto *i : this->enemies)
	{
		delete i;
	}



}

//functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp()>0)
		{
			this->update();
		}
		this->render();
	}
	

}

void Game::updatePollEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)//esc
		{
			this->window->close();
		}
	}

}

void Game::updateInput()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->player->move(0.f, 1.f);
	}

	//bullet player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x + this->player->getBounds().width/2.2f,
		this->player->getPos().y, 0.f, -1.f, 5.f));



	}

}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * this->playerHpBar.getSize().x * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//botton world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}


}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		//bullet culling (top of screen)
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//delete buller
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
					
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimer)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-50.f, -100.f));//x,y
		this->spawnTimer = 0.f;
	}
	
	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		
		enemy->update();
		
		//bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
		}
		//enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		
		++counter;
	}

}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k <this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin()+i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				
				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();
	
	this->updateCombat();
	
	this->updateGUI();

	this->updateWorld();

}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);


}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//draw world
	this->renderWorld();

	//draw all the stuffs
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy: this->enemies)
	{
		enemy->render(this->window);
	}


	this->renderGUI();
	
	//game over screen
	if (this-> player->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

