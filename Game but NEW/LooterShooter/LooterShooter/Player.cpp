#include "Player.h"

void Player::startVariavles()
{
	this->movementSpeed = 9.f;

	this->attackCooldowMax = 5.f;
	this->attackCooldown = this->attackCooldowMax;

	this->hpMax = 100;
	this->hp = this->hpMax;

}

void Player::startTexture()
{ 
	//load texture from file
	if (this->texture.loadFromFile("Textures/ship.png"));
	{
		std::cout << "ERROR::PLAYER::startTexture::can not load texture file." << "\n";
	}



}

void Player::startSprite()
{
	//set the texture to sprite
	this->sprite.setTexture(this->texture);

	//resize this sprite
	this->sprite.scale(0.14f, 0.14f);


}

Player::Player()
{
	
	this->startVariavles();
	this->startTexture(); //only first
	this->startSprite();
}

Player::~Player()
{
}

const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}



void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldowMax)
	{
		this->attackCooldown = 0.f;
			return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldowMax)
	{
		this->attackCooldown += 0.5f;

	}

}

//functions
void Player::update()
{
	this->updateAttack();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite); 
}
