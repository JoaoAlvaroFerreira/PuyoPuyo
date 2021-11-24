#ifndef SDLManager_H
#define SDLManager_H

#include <stdio.h>
#include <iostream>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 600;
    int board_start_h = (SCREEN_HEIGHT - 512)/2;
    int board_start_w = (SCREEN_WIDTH - 256)/2;

    SDL_Event e;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;

    SDL_Texture *mTexture = NULL;
    SDL_Texture *backgroundTex = NULL;
    SDL_Texture *jackTex = NULL;
    SDL_Texture *pacmanTex = NULL;
    SDL_Texture *angryBirdTex = NULL;
    SDL_Texture *greenTex = NULL;

    //Current displayed PNG image
    SDL_Surface *backgroundPNG = NULL;
    SDL_Surface *jackPNG = NULL;
    SDL_Surface *pacmanPNG = NULL;
    SDL_Surface *angryBirdPNG = NULL;
    SDL_Surface *greenPNG = NULL;

public:
    SDLManager();

    bool init();

    bool loadMedia();

    USER_INPUT inputHandling();

    void drawBoard(std::array<std::array<char, 16>, 8> board, int score, float delay);

    void keys();

    void close();
};

#endif
