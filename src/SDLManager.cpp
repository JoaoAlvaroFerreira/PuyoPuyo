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

            //Initialize SDL_ttf
            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
            {
                printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                success = false;
            }
        }
    }

    return success;
};

bool SDLManager::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS("res/fh.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    gScratch = Mix_LoadWAV("res/hammer.wav");
    if (gScratch == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    ///////////images

    startMenuPNG = IMG_Load("./res/start_menu.png");
    startMenuTex = SDL_CreateTextureFromSurface(renderer, startMenuPNG);
    SDL_FreeSurface(startMenuPNG);

    gameOverPNG = IMG_Load("./res/game_over.png");
    gameOverTex = SDL_CreateTextureFromSurface(renderer, gameOverPNG);
    SDL_FreeSurface(gameOverPNG);

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

    angryBirdPNG = IMG_Load("./res/Red32.png");
    angryBirdTex = SDL_CreateTextureFromSurface(renderer, angryBirdPNG);
    SDL_FreeSurface(angryBirdPNG);

    greenPNG = IMG_Load("./res/1Up32.png");
    greenTex = SDL_CreateTextureFromSurface(renderer, greenPNG);
    SDL_FreeSurface(greenPNG);

    //Make a target texture to render too
    //texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    font = TTF_OpenFont("res/Tactico.ttf", 40);

    return success;
};

void SDLManager::drawBoard(std::array<std::array<char, 16>, 8> board, int score, std::array<std::array<char, 2>, 3> pieceList, char holding[2], std::string message, float delay) /////////////CLEAN UP ASAP
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
                dest.x = i * puyo_size + board_start_w;
                dest.y = j * puyo_size + board_start_h;
            }

            switch (board.at(i).at(j))
            {

            case '1':
                SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
                break;
            case '2':
                SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
                break;
            case '3':
                SDL_RenderCopy(renderer, angryBirdTex, &sprite, &dest);
                break;
            case '4':
                SDL_RenderCopy(renderer, greenTex, &sprite, &dest);
                break;

            default:
                break;
            }
        }
    }

    for (int k = 0; k < pieceList.size(); k++)
    {

        dest.x = board_start_w + (puyo_size * 8);
        dest.y = k * puyo_size + board_start_h;

        switch (pieceList[k][0])
        {

        case '1':
            SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
            break;
        case '2':
            SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
            break;
        case '3':
            SDL_RenderCopy(renderer, angryBirdTex, &sprite, &dest);
            break;
        case '4':
            SDL_RenderCopy(renderer, greenTex, &sprite, &dest);
            break;

        default:
            break;
        }

        dest.x = board_start_w + (puyo_size * 9);

        switch (pieceList[k][1])
        {

        case '1':
            SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
            break;
        case '2':
            SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
            break;
        case '3':
            SDL_RenderCopy(renderer, angryBirdTex, &sprite, &dest);
            break;
        case '4':
            SDL_RenderCopy(renderer, greenTex, &sprite, &dest);
            break;

        default:
            break;
        }
    }


    dest.x = board_start_w - puyo_size * 2;
    dest.y = board_start_h;
    switch (holding[0])
    {

    case '1':
        SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
        break;
    case '2':
        SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
        break;
    case '3':
        SDL_RenderCopy(renderer, angryBirdTex, &sprite, &dest);
        break;
    case '4':
        SDL_RenderCopy(renderer, greenTex, &sprite, &dest);
        break;

    default:
        break;
    }

    dest.x = board_start_w - puyo_size;

    switch (holding[1])
    {

    case '1':
        SDL_RenderCopy(renderer, jackTex, &sprite, &dest);
        break;
    case '2':
        SDL_RenderCopy(renderer, pacmanTex, &sprite, &dest);
        break;
    case '3':
        SDL_RenderCopy(renderer, angryBirdTex, &sprite, &dest);
        break;
    case '4':
        SDL_RenderCopy(renderer, greenTex, &sprite, &dest);
        break;

    default:
        break;
    }

    ////WRITE TEXT

    std::string score_text = "Score: " + std::to_string(score);
    drawMessage(score_text, 50, SCREEN_HEIGHT - 50);

    if(message.compare(" "))
        drawMessage(message, 50, 50);

    SDL_RenderPresent(renderer);

    SDL_Delay(delay);

    SDL_RenderClear(renderer);
};

void SDLManager::playSoundEffect(){
    Mix_PlayChannel(-1, gScratch, 0);
}

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
            case SDLK_w:
                return UP;
                break;

            case SDLK_DOWN:
            case SDLK_s:
                return DOWN;
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                return RIGHT;
                break;

            case SDLK_LEFT:
            case SDLK_a:
                return LEFT;
                break;
            case SDLK_c:
            case SDLK_q:
                return ROTATE_RIGHT;
                break;
            case SDLK_z:
            case SDLK_e:
                return ROTATE_LEFT;
                break;
            case SDLK_SPACE:
                return SPACE;
                break;
            default:
                return NONE;
                break;
            }
        }
    }

    return NONE;
};

void SDLManager::drawMessage(std::string message,  int x, int y){
    
    textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    text_width = textSurface->w;
    text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    renderQuad = {x, y, text_width, text_height};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);

}

void SDLManager::drawScene(int scene)
{
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(gMusic, -1);
    }

    if (scene == 0)
        SDL_RenderCopy(renderer, startMenuTex, NULL, NULL);
    else if (scene == 1)
        SDL_RenderCopy(renderer, gameOverTex, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);
}

void SDLManager::close()
{

    Mix_FreeChunk(gScratch);
    Mix_FreeMusic(gMusic);
    //Destroy window;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}