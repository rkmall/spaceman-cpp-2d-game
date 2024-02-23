#include "Player.h"

unsigned Player::players = 0;                                // definition of static unsigned player

enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT};            // enums controls for keyboard press  

//Player Constructor
Player::Player(std::vector<Texture>& textures,
	int UP, int DOWN, int LEFT, int RIGHT, int SHOOT)
	:level(1), exp(0), expNext(100), hp(10), hpMax(10),
	damage(1), damageMax(2), score(0)
{
	//Player Center
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	//Textures and Sprites
	this->sprite.setTexture(textures[0]);                
	this->sprite.setScale(0.13f, 0.13f);                    // Set player sprite size

	this->bulletTexture = &textures[1];

	this->mainGunSprite.setTexture(textures[2]);
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2);
	this->mainGunSprite.rotate(90);

	//Set the position of gun to follow player
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y);


	//Timers
	this->shootTimerMax = 13;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;

	// Controls Keyboard press assignments 
	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	//Velocity & Acclerations
	this->maxVelocity = 25.f;
	this->acceleration = 1.f;
	this->stabilizerForce = 0.3f;

	//Add number of player
	//this->playerNr = Player::players;
	//Player::players++;                                     // Everytime we create a player, player++

	std::cout << this->playerNr << "\n";                   // Logs number of players
	
}

//Player Destructor
Player::~Player()
{

}

void Player::UpdateAccessories()
{
	//Set the position of gun to follow player
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y);

	//Animate main gun and correct it after firing
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.move(1.f + this->currentVelocity.x, 0.f);
	}

	if (this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.setPosition(
			this->playerCenter.x + 20.f, this->playerCenter.y);
	}
}




/*------------------------------------------------------------------------
Player Movement Definition [ Movement => (x-axis, y-axis) = (.f, .f) ]
                           [ UP => (x-axis, y-axis) = (0, -) ]
                         [ DOWN => (x-axis, y-axis) = (0, +) ]
                         [ LEFT => (x-axis, y-axis) = (-, 0) ]
                        [ RIGHT => (x-axis, y-axis) = (+, 0) ]
--------------------------------------------------------------------------*/

void Player::Movement()
{
	//UP
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
		//std::cout << "W" << "\n";
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}
		
	//DOWN
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
		//std::cout << "S" << "\n";
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}
		
	//LEFT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
		//std::cout << "A" << "\n";
	{
		this->direction.x = -1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//RIGHT
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
		//std::cout << "D" << "\n";
	{
		this->direction.x = 1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//STABILIZER FORCE (Between Ship and Gun)
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}

	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}
		



	//FINAL MOVE
	this->sprite.move(this->currentVelocity);


	//PLAYER CENTER 
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	
}

//Player Combat Definition
void Player::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT]))
		&& this->shootTimer >= this->shootTimerMax)
	{
		this->bullets.push_back(
			Bullet(bulletTexture,
				Vector2f(this->playerCenter.x +50.f, this->playerCenter.y),
				Vector2f(1.f, 0.f), 2.f, 
				50.f, 2.f));
		

		//Animate main gun
		this->mainGunSprite.move(-15.f, 0.f);             


		this->shootTimer = 0; //RESET TIMER
	}
}


//Player Update Definition
void Player::Update(Vector2u windowBounds)
{ 
	//Update Timers
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;

	this->Movement();                                    // Player movement is updated
	this->UpdateAccessories();
	this->Combat();
}


//Player Draw Definition
void Player::Draw(RenderTarget& target)                  
{
	target.draw(this->sprite);                            // Draw player sprite                           

	for (size_t i = 0; i < this->bullets.size(); i++)  
	{                                              
		this->bullets[i].Draw(target);                    // Draw bullet sprite
	}

	target.draw(this->mainGunSprite);

	target.draw(this->sprite);                            // Draw player sprite
}
