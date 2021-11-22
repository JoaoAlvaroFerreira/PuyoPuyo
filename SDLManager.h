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
    ROTATE_RIGHT,
    ROTATE_LEFT,
    SPACE,
    QUIT,
    NONE
};

class SDLManager
{

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

    SDL_Renderer *renderer = NULL;

    SDL_Texture *backgroundTex = NULL;
    SDL_Texture *jackTex = NULL;
    SDL_Texture *pacmanTex = NULL;

    //Current displayed PNG image
    SDL_Surface *backgroundPNG = NULL;
    SDL_Surface *jackPNG = NULL;
    SDL_Surface *pacmanPNG = NULL;

public:
    SDLManager();

    bool init();

    bool loadMedia();

    USER_INPUT inputHandling();

    void drawBoard(std::array<std::array<char, 16>, 8> board);

    void keys();

    void close();
};

#endif
