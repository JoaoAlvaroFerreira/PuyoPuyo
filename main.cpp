#include "SDLManager.h"
#include "Game.h"

#include <chrono>

int main(int argc, char *args[])
{

	Game *game = new Game();
	SDLManager *sdl = new SDLManager();
	//Start up SDL and create window
	bool quit = false;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::duration<double> time_aux;
	start = std::chrono::system_clock::now();
	double duration_speed = 0.5;
	

	//While application is running
	while (!quit)
	{
		USER_INPUT input = sdl->inputHandling();

		

		if (input == QUIT)
			quit = true;
		else
		{
			time_aux = std::chrono::system_clock::now() - start;

			if(time_aux.count() > duration_speed){
				game->movePiece(DOWN);
				start = std::chrono::system_clock::now();
			}

			if (game->collisionCheck()) //MAYBE TO SHOW ALL OF THIS ON SCREEN, CREATE COLLISION VARIABLE THAT ACTIVATES ON COLLISION CHECK AND ONLY DEACTIVATES ON GENERATE PIECE, CYCLING THROUGH EACH STEP
			{	
				
				
				game->contactDrop(); 
				

				//////////while loop for floodfills that only ends once no more floodfills are available
				//check for floodfills on collCheck

				if(game->checkLose()){
					quit = true;
				}
				else{
				game->generatePiece();
				}
				
			}
			else
			{
				game->movePiece(input);
			}
			//collision check, then floodfill, then collision check again, etc.
		}
		sdl->drawBoard(game->getBoard());
	}

	//Free resources and close SDL
	sdl->close();

	return 0;
}