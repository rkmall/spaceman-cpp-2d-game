#include "Game.h"

int main()
{	
	// Size, title and style of the main application window                                      // RenderWindow SFML graphics API 
	RenderWindow window(VideoMode(1920, 1080), "Spaceman", Style::Fullscreen);                   // VideoMode supports compatibility with graphics  
																			                     // driver and monitor support when creating full 
	                                                                                             // screen window. Only applies in full screen window
	Game game(&window);                           // Init game                
	                                                
	/*--------------------------------------------
	                   GAME LOOP
	---------------------------------------------*/
	while (window.isOpen())                     
	{
		Event event;                                                                              // pollEvent
		while (window.pollEvent(event))                                                           // This is a thread in main() that waits for other event thread
		{                                                                                         // to finish execution  
			if (event.type == Event::Closed)                                                      // It sleeps until a new event is received just like .join() in C++
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();                                                                   // When pressed esc key, window closes
		}

		game.Update();                                                                            // Defined and handled by Game class
		game.Draw();                                                                              // Defined and handled by Game class
	}

	return 0;
}