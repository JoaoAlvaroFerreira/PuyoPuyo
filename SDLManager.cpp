#include "SDLManager.h"

bool SDLManager::init()
{

    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Puyo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                //gScreenSurface = SDL_GetWindowSurface(gWindow);

                renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
            }
        }
    }

    return success;
}

bool SDLManager::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load PNG surface
    gPNGSurface = IMG_Load("./res/sonic.png");
    if (gPNGSurface == NULL)
    {
        printf("Failed to load PNG image!\n");
        success = false;
    }

    bmpTex = SDL_CreateTextureFromSurface(renderer, gPNGSurface);
    SDL_FreeSurface(gPNGSurface);

    //Make a target texture to render too
    texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    return success;
}

SDL_Surface *SDLManager::loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void SDLManager::screenLoop()
{
    SDL_Rect spritePosition;
    SDL_Rect DestR;

    spritePosition.x = 0;
    spritePosition.y = 0;
    spritePosition.h = sonic_height;
    spritePosition.w = sonic_width;

    DestR.x = 0;
    DestR.y = 0;
    DestR.w = sonic_width;
    DestR.h = sonic_height;

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    spritePosition.y -= 2;

                    break;

                case SDLK_DOWN:
                    spritePosition.y += 2;
                    break;

                case SDLK_LEFT:
                    spritePosition.x -= 2;
                    break;

                case SDLK_RIGHT:
                    spritePosition.x += 2;
                    break;

                default:
                    break;
                }
            }
        }

        //Now render to the texture

        SDL_RenderCopy(renderer, bmpTex, &DestR, &spritePosition);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        //Detach the texture
        //SDL_SetRenderTarget(renderer, NULL);
        //Apply the PNG image
        //SDL_RenderClear(gScreenSurface);
        //SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, &spritePosition);

        //Update the surface
        //SDL_UpdateWindowSurface(gWindow);
    }
}

void SDLManager::keys()
{
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //Set default current surface
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    //While application is running
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            //User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;

                case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;

                case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;

                case SDLK_RIGHT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;

                default:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        //Apply the current image
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

        //Update the surface
        SDL_UpdateWindowSurface(gWindow);
    }
}

void SDLManager::close()
{
    //Deallocate surfaces
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}