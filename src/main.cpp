#include "SDLManager.h"
#include "Game.h"
#include "Utils.h"


#include <chrono>

enum SCENE
{
	START_MENU,
	HOW_TO_PLAY,
	GAME,
	GAME_OVER,
	QUIT_GAME
};

SCENE currentScene = START_MENU;


void startMenuLoop(SDLManager *sdl)
{

	bool quit = false;

	sdl->drawScene(0, true);
	//While application is running
	while (!quit)
	{
		USER_INPUT input = sdl->inputHandling();

		if (input == QUIT)
		{
			quit = true;
			currentScene = QUIT_GAME;
		}
		else if (input != NONE)
		{
			currentScene = HOW_TO_PLAY;
			return;
		}
		sdl->drawScene(0, false);
	}
}

void howToPlayLoop(SDLManager *sdl)
{

	bool quit = false;
	
	sdl->drawScene(1, true);
	//While application is running
	while (!quit)
	{
		USER_INPUT input = sdl->inputHandling();

		if (input == QUIT)
		{
			quit = true;
			currentScene = QUIT_GAME;
		}
		else if (input != NONE)
		{
			currentScene = GAME;
			return;
		}
		sdl->drawScene(1, false);
	}
}

void gameOverLoop(SDLManager *sdl)
{

	bool quit = false;

	//While application is running
	sdl->drawScene(2, true);
	while (!quit)
	{
		USER_INPUT input = sdl->inputHandling();

		if (input == QUIT)
		{
			quit = true;
			currentScene = QUIT_GAME;
		}
		else if (input != NONE)
		{
			currentScene = START_MENU;
			return;
		}
		sdl->drawScene(2, false);
	}
}

void sceneManagement(SDLManager *sdl)
{
	int end_game_state = 1;
	Game *game;
	while (currentScene != QUIT_GAME)
	{
		switch (currentScene)
		{
		case START_MENU:
			
			startMenuLoop(sdl);
			sdl->clearKeyEventsQueue();
			break;
		case HOW_TO_PLAY:
			
			howToPlayLoop(sdl);
			sdl->clearKeyEventsQueue();
			break;
		case GAME:
			game = new Game();
			game->setGraphics(sdl);

			end_game_state = game->gameLoop();
			sdl->clearKeyEventsQueue();

			if (end_game_state == 0)
				currentScene = QUIT_GAME;
			else if (end_game_state == 1)
				currentScene = GAME_OVER;

			break;

		case GAME_OVER:
			
			gameOverLoop(sdl);
			sdl->clearKeyEventsQueue();
			break;
		default:
			currentScene = START_MENU;
			break;
		}
	}
}

int main(int argc, char *args[])
{

	SDLManager *sdl = new SDLManager();

	sceneManagement(sdl);

	sdl->close();

	return 0;
}