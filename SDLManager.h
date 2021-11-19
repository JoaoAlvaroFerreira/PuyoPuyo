#ifndef SDLManager_H
#define SDLManager_H

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDLManager
{
public:
    //Key press surfaces constants
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    const int sonic_width = 392;
    const int sonic_height = 350;
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //CHANGE THIS TO LOAD TEXTURE
    SDL_Surface *loadSurface(std::string path);

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    
    SDL_Renderer *renderer = NULL;

    SDL_Texture *texTarget = NULL;

    SDL_Texture *bmpTex = NULL;

    //SURFACES ARE GARBAGE, REMOVE

    //The images that correspond to a keypress
    SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    //Current displayed image
    SDL_Surface *gCurrentSurface = NULL;

    //Current displayed PNG image
    SDL_Surface *gPNGSurface = NULL;

    bool init();

    bool loadMedia();

    void screenLoop();

    void keys();

    void close();
};

#endif
