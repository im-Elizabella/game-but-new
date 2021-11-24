#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <string>
#include <sstream>


class Game
{
private:
	//window
	sf::RenderWindow* window;

	//resources
	std::map<std::string,sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;


	//world
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//systems
	unsigned points;

	//Player
	Player* player;

	//playerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	//private functions
	void startWindow();
	void startTextures();
	void startGUI();
	void startWorld();
	void startSystems();

	void startPlayer();
	void startEnemies();

public:
	Game();
	virtual ~Game();


	//functions

	void run();
	
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();

};

