#include "Enemy.h"


void Enemy::startVariables()
{
	this->pointsCount	= rand() % 8 + 3; //min = 3 max = 10
	this->type			= 0;
	this->speed			= static_cast<float>(this->pointsCount/2);
	this->hpMax			= static_cast<int>(this->pointsCount);
	this->hp			= this->hpMax;
	this->damage		= this->pointsCount;
	this->points		= this->pointsCount;
}

void Enemy::startShape()
{
	this->shape.setRadius(this->pointsCount * 4 );
	this->shape.setPointCount(this->pointsCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_X,float pos_Y)
{
	
	this->startVariables();
	this->startShape();
	this->shape.setPosition(pos_X, pos_Y);
	
}

Enemy::~Enemy()
{
}

//accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}


//functions
void Enemy::update()
{
	this->shape.move(0.f, 5.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

