#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Enemy
{
private:
	unsigned pointsCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void startVariables();
	void startShape();

public:

	Enemy(float pos_X, float pos_Y);
	virtual ~Enemy();

	//accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	
	
	//functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H