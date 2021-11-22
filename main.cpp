#include "SDLManager.h"
#include "Game.h"

int main(int argc, char *args[])
{

	Game *game = new Game();
	SDLManager *sdl = new SDLManager();
	//Start up SDL and create window
	bool quit = false;

	

	//While application is running
	while (!quit)
	{
		USER_INPUT input = sdl->inputHandling();

		

		if (input == QUIT)
			quit = true;
		else
		{


			if (game->collisionCheck()) //MAYBE TO SHOW ALL OF THIS ON SCREEN, CREATE COLLISION VARIABLE THAT ACTIVATES ON COLLISION CHECK AND ONLY DEACTIVATES ON GENERATE PIECE, CYCLING THROUGH EACH STEP
			{	
				
				
				game->contactDrop(); 
				

				//////////while loop for floodfills that only ends once no more floodfills are available
				//check for floodfills on collCheck
				game->generatePiece();
				
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