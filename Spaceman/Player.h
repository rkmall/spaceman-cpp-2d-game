#pragma once

#include "Bullet.h"

class Player
{
private:
	unsigned playerNr;                // Number of players in Game

	Vector2f playerCenter;            // Centers the player position

	int shootTimer;
	int shootTimerMax;
	int damageTimer;                  // How long after player gets hit again
	int damageTimerMax;

	Sprite sprite;                    // Player sprite 
	RectangleShape hitBox;

	//Accessories
	Texture* mainGunTexture;
	Sprite mainGunSprite;
	Texture* bulletTexture;           // Player owns bullet
	std::vector<Bullet> bullets;

	
	int controls[5];                   // enums controls
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;

public:
	Player(std::vector<Texture>& textures,
		int UP = 22, int DOWN = 18, int LEFT = 0,
		int RIGHT = 3, int SHOOT = 57);

	virtual ~Player();

	//Getters
	inline std::vector<Bullet>& getBullet() { return this->bullets; } // get reference for bullets
	inline const Vector2f getPosition()const { return this->sprite.getPosition();} // get position
	inline const String getHpAsString() const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);}

	//Functions
	void UpdateAccessories();
	void Combat();
	void Movement();
	void Update(Vector2u windowBounds);
	void Draw(RenderTarget& target);               
	


	//Statics
	static unsigned players;

};

