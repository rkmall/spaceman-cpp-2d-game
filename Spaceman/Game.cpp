#include "Game.h"

enum textures {player = 0, bullet, mainGun01, enemy01 };

//Game constructor
Game::Game(RenderWindow* window)                      // Game Ctor takes in pointer to window
{
	this->window = window;                            // Create window. Our Game window = SFML window 
	this->window->setFramerateLimit(60);              // Set the relative fps fo the window

	//Init textures (Load images for the textures)
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/ship.png");                // Player(ship) texture
	this->textures.push_back(Texture()); 
	this->textures[bullet].loadFromFile("Textures/rayTex01.png");            // Laser(bullet) texture
	this->textures.push_back(Texture());
	this->textures[mainGun01].loadFromFile("Textures/gun01.png");            // Gun(in the ship) texture
	this->textures.push_back(Texture());
	this->textures[enemy01].loadFromFile("Textures/enemyMoveLeft.png");      // Enemy texture


	//Init player
	this->players.push_back(Player(this->textures));                         // Player 1 pushed into players vector


	//Init enemies
	Enemy e1(
		&this->textures[enemy01], this->window->getSize(),                   
		Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0,
		rand() % 3 + 1, 3, 1 );
	
	this->enemiesSaved.push_back(Enemy(e1));                                  // Enemy e1 pushed back to enemySaved vector
	this->enemySpawnTimerMax = 30;                                            // Enemy spawn timer max
	this->enemySpawnTimer = this->enemySpawnTimerMax;


	this->players.push_back(Player(this->textures,
		Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::LShift));  // Player 2
    
	//player = new Player(&this->playerTexture);                                 // If no vector, single player

	//Init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");     // Load Fonts

	this->InitUI();
}

//Game Destructor
Game::~Game()
{
	
}


// InitUI Definition
void Game::InitUI()
{
	Text tempText;

	for (size_t i = 0; i < this->players.size(); i++)
	{
		//Follow Text Init
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(Color::White);
		tempText.setString(std::to_string(i));        //Initialization

		this->followPlayerTexts.push_back(Text(tempText));


		//Static Text Init
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(Color::White);
		tempText.setString("");                        //Initialization

		this->staticPlayerTexts.push_back(Text(tempText));
		
	}
}

//UpdateUI definition
void Game::UpdateUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->followPlayerTexts[i].setPosition(this->players[i].getPosition().x, this->players[i].getPosition().y - 20.f);
		this->followPlayerTexts[i].setString(std::to_string(i) + "			  " + this->players[i].getHpAsString());
	}

	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{

	}
}


//Game Update Definition
void Game::Update()
{
	//Update timers
	if (this->enemySpawnTimer < this->enemySpawnTimerMax)
		this->enemySpawnTimer++;

	//Spawn enemies
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		this->enemies.push_back(Enemy(
			&this->textures[enemy01], this->window->getSize(),
			Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 0,
			rand() % 3 + 1, 3, 1));
		
		this->enemySpawnTimer = 0;
	}


	for (size_t i = 0; i < this->players.size(); i++)
	{
		//UPDATE PLAYERS
		this->players[i].Update(this->window->getSize());                   // Send in the size of the window

		//UPDATE BULLET
		for (size_t k = 0; k < this->players[i].getBullet().size(); k++)
		{
			this->players[i].getBullet()[k].Update();                       // Bullet Update() called which calls Bullet Movements()            
			   

			//ENEMY BULLET COLLISION CHECK
			for (size_t j = 0; j < this->enemies.size(); j++)
			{

				if (this->players[i].getBullet()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
				{
					this->players[i].getBullet().erase(this->players[i].getBullet().begin() + k);
					this->enemies.erase(this->enemies.begin() + j);
					return;
				}
					
			}
			
			//WINDOW BOUND CHECK
			if (this->players[i].getBullet()[k].getPosition().x > this->window->getSize().x)
			{
				this->players[i].getBullet().erase(this->players[i].getBullet().begin() + k);
				break;
			}
		}

	}

	//UPDATE ENEMIES
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Update();
	}
	

	//UPDATE UI
	this->UpdateUI();
}

void Game::DrawUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->window->draw(this->followPlayerTexts[i]);
	}

	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->window->draw(this->staticPlayerTexts[i]);
	}

}

//Game Draw Definition 
void Game::Draw()
{
	this->window->clear();                             // Clears previous target contents every frame            
	
	for (size_t i = 0; i < this->players.size(); i++)     
	{                                                     
		this->players[i].Draw(*this->window);          // Player Draw() defined in Player Class               
	}                                                  // Draw Player in the Game window

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
	}

	this->DrawUI();

	this->window->display();                           // Display player(s) 
}