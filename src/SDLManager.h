#ifndef SDLManager_H
#define SDLManager_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif
#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>

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

    const int puyo_size = 40;
    //Screen dimension constants
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 800;
    int board_start_h = (SCREEN_HEIGHT - (puyo_size * 16)) / 2;
    int board_start_w = (SCREEN_WIDTH - (puyo_size * 8)) / 2;

    SDL_Event e;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;

    SDL_Texture *mTexture = NULL;
    SDL_Texture *startMenuTex = NULL;
    SDL_Texture *gameOverTex = NULL;
    SDL_Texture *backgroundTex = NULL;
    SDL_Texture *blueTex = NULL;
    SDL_Texture *yellowTex = NULL;
    SDL_Texture *redTex = NULL;
    SDL_Texture *greenTex = NULL;

    //Current displayed PNG image
    SDL_Surface *startMenuPNG = NULL;
    SDL_Surface *gameOverPNG = NULL;
    SDL_Surface *backgroundPNG = NULL;
    SDL_Surface *bluePNG = NULL;
    SDL_Surface *yellowPNG = NULL;
    SDL_Surface *redPNG = NULL;
    SDL_Surface *greenPNG = NULL;

    ///audio
    //The music that will be played
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *tone1 = NULL;
    Mix_Chunk *tone2 = NULL;
    Mix_Chunk *tone3 = NULL;

    SDL_Color textColor = {255, 255, 255, 0};
    SDL_Surface *textSurface;
    SDL_Texture *text;
    int text_width;
    int text_height;
    SDL_Rect renderQuad;

public:
    SDLManager();

    bool init();

    bool loadMedia();

    USER_INPUT inputHandling();

    void drawGame(std::array<std::array<char, 16>, 8> board, int score, std::vector<int> scores, std::array<std::array<char, 2>, 3> pieceList, char holding[2], std::string message, float delay);

    void drawBlock(char block);

    void drawBoard(std::array<std::array<char, 16>, 8> board);

    void drawPieceList( std::array<std::array<char, 2>, 3> pieceList);

    void drawHolding(char holding[2]);

    void drawMessage(std::string message, int x, int y);

    void drawScores(std::vector<int> scores);

    void playSoundEffect(int i);

    void drawScene(int scene);

    void keys();

    void close();
};

#endif
