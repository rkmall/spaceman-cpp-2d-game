#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	RenderWindow* window;                // Pointer to window 

	//Text
	Font font;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;

	//Players
	std::vector<Player> players;         // Vector of players, might be multiple player

	//Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	int enemySpawnTimer;
	int enemySpawnTimerMax;

	//Textures
	std::vector<Texture> textures;

public:
	Game(RenderWindow* window);           // Constructor
	virtual ~Game();                      // Destructor

	//Setters

	//Getters
	inline RenderWindow& getWindow() { return *this->window; }      //?

	//Functions
	void InitUI();
	void UpdateUI();
	void Update();
	void DrawUI();
	void Draw();
};

