#include "Enemy.h"

enum eTypes {MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT};

Enemy::Enemy(Texture* texture, Vector2u windowBounds, Vector2f position,
	Vector2f direction, Vector2f scale, int type, int hpMax, int damageMax,
	int damageMin)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;

	this->direction = direction;
	this->sprite.setPosition(windowBounds.x, rand() % windowBounds.y 
		+ this->sprite.getGlobalBounds().height);

	this->type = type;

	this->hpMax = hpMax;
	this->hp = hp;

	this->damageMax = damageMax;
	this->damageMin = damageMin;
}


Enemy::~Enemy()
{
}


void Enemy::Update()
{
		this->sprite.move(-10.f, 0.f);
}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}


