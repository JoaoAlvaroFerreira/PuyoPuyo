#ifndef SDLManager_H
#define SDLManager_H

#include <stdio.h>
#include <iostream>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

enum USER_INPUT
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    SPACE,
    QUIT,
    NONE
};

class SDLManager
{
public:
    //Key press surfaces constants

    SDL_Rect sprite;
    SDL_Rect dest;

    const int puyo_size = 32;
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 640;

    SDL_Event e;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    SDL_Renderer *renderer = NULL;

    SDL_Texture *jackTex = NULL;

    //SURFACES ARE GARBAGE, REMOVE

    //Current displayed image
    SDL_Surface *gCurrentSurface = NULL;

    //Current displayed PNG image
    SDL_Surface *jackPNG = NULL;
    SDL_Surface *pacmanPNG = NULL;

    SDLManager();

    bool init();

    bool loadMedia();

    USER_INPUT inputHandling();

    void drawBoard(std::array<std::array<char, 16>, 8> board);

    void keys();

    void close();
};

#endif
