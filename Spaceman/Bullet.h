#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <vector>

using namespace sf;


class Bullet
{
private:
	Texture* texture;
	Sprite sprite;        

	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;


public:
	Bullet(Texture* texture, Vector2f position, Vector2f direction,
		 float initialVelocity, float maxVelocity,
		 float acceleration);
	virtual ~Bullet();

	//Getters
	inline FloatRect getGlobalBounds()const           // We can everything do with its Global bounds
	{                                                 // directly
		return this->sprite.getGlobalBounds(); 
	}

	inline const Vector2f& getPosition()const         // Return position to Global bounds
	{                                                 
		return this->sprite.getPosition();
	}

	

	//Functions
	void Movement();

	void Update();
	void Draw(RenderTarget& target);
};

