#include "SDLManager.h"
#include "Game.h"


int main( int argc, char* args[] )
{
	
	Game * game = new Game();
    SDLManager * sdl = new SDLManager();
	//Start up SDL and create window
	bool quit = false;

   
    //While application is running
    while (!quit)
    {	
		USER_INPUT input = sdl->inputHandling();

		if(input == QUIT)
			quit = true;
		else{
			game->movePiece(input);

			//collision check, then floodfill, then collision check again, etc.
		}
        sdl->drawBoard(game->getBoard());
    }
    
	
	

	//Free resources and close SDL
	sdl->close();

	return 0;
}