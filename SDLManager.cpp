#include "SDLManager.h"

SDLManager::SDLManager()
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
    }
}
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
};

bool SDLManager::loadMedia()
{
    //Loading success flag
    bool success = true;

    backgroundPNG = IMG_Load("./res/background.png");
    backgroundTex = SDL_CreateTextureFromSurface(renderer, backgroundPNG);
    SDL_FreeSurface(backgroundPNG);
    //Load PNG surface
    jackPNG = IMG_Load("./res/jack32.png");
    jackTex = SDL_CreateTextureFromSurface(renderer, jackPNG);
    SDL_FreeSurface(jackPNG);

    pacmanPNG = IMG_Load("./res/pacman32.png");
    pacmanTex = SDL_CreateTextureFromSurface(renderer, pacmanPNG);
    SDL_FreeSurface(pacmanPNG);

    //Make a target texture to render too
    //texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    return success;
};

void SDLManager::drawBoard(std::array<std::array<char, 16>, 8> board)
{
    SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);

    dest.x = 0;
    dest.y = 0;
    dest.h = puyo_size;
    dest.w = puyo_size;

    sprite.x = 0;
    sprite.y = 0;
    sprite.h = puyo_size;
    sprite.w = puyo_size;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.at(i).size(); j++)
        {
            if (board.at(i).at(j) != 0)
            {
                dest.x = i * puyo_size;
                dest.y = j * puyo_size;
            }

            switch (board.at(i).at(j))
            {
            
            case '1':
                SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
                break;
            case '2':
                SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
                break;

            default:
                break;
            }
        }
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
};

USER_INPUT SDLManager::inputHandling()
{
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            return QUIT;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                return UP;
                break;

            case SDLK_DOWN:
                return DOWN;
                break;

            case SDLK_LEFT:
                return LEFT;
                break;

            case SDLK_RIGHT:
                return RIGHT;
                break;

            default:
                return NONE;
                break;
            }
        }
    }

    return NONE;
};

void SDLManager::close()
{

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
};

////old screen loop

/*
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

        SDL_RenderCopy(renderer, jackTex, &DestR, &spritePosition);
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

    */
