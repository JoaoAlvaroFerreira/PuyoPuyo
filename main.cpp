#include "SDLManager.h"
#include "Game.h"

#include <chrono>

enum SCENE{
	START_MENU,
	HOW_TO_PLAY,
	GAME,
	GAME_OVER
};

SCENE currentScene = START_MENU;

int main(int argc, char *args[])
{

	
	SDLManager *sdl = new SDLManager();

	updateScene()
	Game *game = new Game();
	game->setGraphics(sdl);
	//Start up SDL and create window
	game->gameLoop();

	//Free resources and close SDL
	sdl->close();

	return 0;
}