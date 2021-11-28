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
		sdl->drawScene(0);
	}
}

void GameOverLoop(SDLManager *sdl)
{

	bool quit = false;

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
			currentScene = START_MENU;
			return;
		}
		sdl->drawScene(1);
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
			break;
		case GAME:
			game = new Game();
			game->setGraphics(sdl);

			end_game_state = game->gameLoop();

			if (end_game_state == 0)
				currentScene = QUIT_GAME;
			else if (end_game_state == 1)
				currentScene = GAME_OVER;

			break;

		case GAME_OVER:
			GameOverLoop(sdl);
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