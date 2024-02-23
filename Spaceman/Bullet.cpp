#include "Bullet.h"


//Bullet Constructor
Bullet::Bullet(Texture* texture, Vector2f position, Vector2f direction,
	float initialVelocity, float maxVelocity,
	float acceleration)
{
	this->texture = texture;                            // Bullet texture = sfml texture loaded in Game class
	this->sprite.setTexture(*this->texture);            // Bullet sprite points to bullet texture
	this->maxVelocity = maxVelocity;                    // Set Bullet speed
	this->acceleration = acceleration;
	this->direction = direction;
	this->currentVelocity = Vector2f(
		initialVelocity * this->direction.x,
		initialVelocity * this->direction.y);

	this->sprite.setScale(0.2f, 0.2f);                  // Set the size of bullets sprite

	this->sprite.setPosition(
		Vector2f(position.x - this->sprite.getGlobalBounds().width/2,     // Precision postion of bullets
		position.y - this->sprite.getGlobalBounds().height/2));           // with respect to player
}


//Bullet Destructor
Bullet::~Bullet()
{

}


//Bullet Movement Definition (Bullet controls its own speed)
void Bullet::Movement()
{

	// Bullet Velocity And Acceleration
	if (this->acceleration > 1.f)
	{
		if (this->currentVelocity.x < this->maxVelocity)
			this->currentVelocity.x += this->acceleration * this->direction.x;

		if (this->currentVelocity.y < this->maxVelocity)
			this->currentVelocity.y += this->acceleration * this->direction.y;
	}
	else
	{
		this->currentVelocity = Vector2f(
			this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}

	this->sprite.move(this->currentVelocity); 
}



//Bullet Update Definition (Bullet Update() is controlled by Player Class)
void Bullet::Update()
{
	this->Movement();                               // Bullet movement is updated
}



//Bullet Draw Definition 
void Bullet::Draw(RenderTarget& target)               
{
	target.draw(this->sprite);                       // Player calls Bullet Draw()
}