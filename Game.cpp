#include "Game.h"

Game::Game()
{
    for (int i = 0; i < game_board.size(); i++)
    {
        for (int j = 0; j < game_board.at(i).size(); j++)
        {
            game_board[i][j] = EMPTY_SPACE;
        }
    }

    generatePiece();
};

int Game::gameLoop()
{

    bool quit = false;
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::duration<double> time_aux;
    start = std::chrono::system_clock::now();
    double duration_speed = 0.5;

    //While application is running
    while (!quit)
    {
        USER_INPUT input = sdl->inputHandling();

        if (input == QUIT){
            quit = true;
        }
        else
        {
            time_aux = std::chrono::system_clock::now() - start;

            if (time_aux.count() > duration_speed)
            {
                movePiece(DOWN);
                start = std::chrono::system_clock::now();
            }

            if (collisionCheck()) //MAYBE TO SHOW ALL OF THIS ON SCREEN, CREATE COLLISION VARIABLE THAT ACTIVATES ON COLLISION CHECK AND ONLY DEACTIVATES ON GENERATE PIECE, CYCLING THROUGH EACH STEP
            {

                contactDrop();

                if (checkLose())
                {
                    quit = true;
                    return 1;
                }
                else
                {
                    generatePiece();
                }
            }
            else
            {
                movePiece(input);
            }
            //collision check, then floodfill, then collision check again, etc.
        }
        sdl->drawBoard(getBoard(), getScore(), 0);
    }

    return 0;
}

void Game::generatePiece()
{

    int cOne = rand() % 4;
    int cTwo = rand() % 4;

    firstBlock = {possibleBlocks[cOne],
                  start_x,
                  start_y};

    secondBlock = {possibleBlocks[cTwo],
                   start_x + 1,
                   start_y};

    player = {
        firstBlock,
        secondBlock,
        NEUTRAL};

    game_board[firstBlock.posX][firstBlock.posY] = firstBlock.num;
    game_board[secondBlock.posX][secondBlock.posY] = secondBlock.num;
    boardMovement(0, 0);

    checkedBlocks = {};
}

bool Game::checkLose()
{
    if (game_board[start_x][start_y] != EMPTY_SPACE || game_board[start_x + 1][start_y] != EMPTY_SPACE)
    {
        return true;
    }

    return false;
}

void Game::clearPieceOnBoard()
{
    game_board[player.a.posX][player.a.posY] = EMPTY_SPACE;
    game_board[player.b.posX][player.b.posY] = EMPTY_SPACE;
}

void Game::printPieceOnBoard()
{
    game_board[player.a.posX][player.a.posY] = player.a.num;
    game_board[player.b.posX][player.b.posY] = player.b.num;
}

void Game::rotatePiece(bool right)
{

    clearPieceOnBoard();

    if (right)
    {
        switch (player.orientation)
        {
        case NEUTRAL:

            if (player.a.posY < 15 && game_board[player.a.posX][player.a.posY + 1] == EMPTY_SPACE)
            {
                player.orientation = CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY + 1;
            }

            break;

        case CLOCKWISE:
            if (player.a.posX > 0 && game_board[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = REVERSE;

                player.b.posX = player.a.posX - 1;
                player.b.posY = player.a.posY;
            }
            break;
        case REVERSE:

            if (player.a.posY > 0 && game_board[player.a.posX][player.a.posY - 1] == EMPTY_SPACE)
            {
                player.orientation = COUNTER_CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY - 1;
            }
            break;
        case COUNTER_CLOCKWISE:

            if (player.a.posX < 7 && game_board[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = NEUTRAL;

                player.b.posX = player.a.posX + 1;
                player.b.posY = player.a.posY;
            }
            break;
        default:
            break;
        }
    }

    else
    {
        switch (player.orientation)
        {
        case NEUTRAL:

            if (player.a.posY > 0 && game_board[player.a.posX][player.a.posY - 1] == EMPTY_SPACE)
            {
                player.orientation = COUNTER_CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY - 1;
            }

            break;

        case CLOCKWISE:

            if (player.a.posX < 7 && game_board[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = NEUTRAL;

                player.b.posX = player.a.posX + 1;
                player.b.posY = player.a.posY;
            }
            break;
        case REVERSE:

            if (player.a.posY < 15 && game_board[player.a.posX][player.a.posY + 1] == EMPTY_SPACE)
            {
                player.orientation = CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY + 1;
            }
            break;
        case COUNTER_CLOCKWISE:

            if (player.a.posX > 0 && game_board[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = REVERSE;

                player.b.posX = player.a.posX - 1;
                player.b.posY = player.a.posY;
            }
            break;
        default:
            break;
        }
    }

    printPieceOnBoard();
}

void Game::movePiece(USER_INPUT input)
{

    switch (input)
    {

    case UP: ////////////CHECK THAT YOU CAN'T DELETE PIECES FROM BELOW OR BY SPINNING

        ///INSTA-DROP

        break;

    case DOWN:
        if (player.a.posY < 15 && player.b.posY < 15)
        {
            boardMovement(0, 1);
        }
        break;
    case LEFT:
        if (player.a.posX > 0 && player.b.posX > 0 && leftCheck()) /////////WRITE THE CHECKS FOR WHEN YOU BUMP INTO PIECES SIDEWAYS, INCLUDING ALL ORIENTATIONS, ALSO FIX CHECK DROP
        {
            boardMovement(-1, 0);
        }
        break;
    case RIGHT:
        if (player.a.posX < 7 && player.b.posX < 7 && rightCheck())
        {
            boardMovement(1, 0);
        }
        break;

    case ROTATE_RIGHT:
        rotatePiece(true);
        break;

    case ROTATE_LEFT:
        rotatePiece(false);
        break;

    case SPACE:
        if (player.a.posY < 15 && player.b.posY < 15)
        {
            boardMovement(0, 1);
        }
        break;

    default:
        break;
    }
}

bool Game::leftCheck()
{
    switch (player.orientation)
    {
    case NEUTRAL:
        if (game_board[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    case REVERSE:
        if (game_board[player.b.posX - 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    default:
        if (game_board[player.a.posX - 1][player.a.posY] == EMPTY_SPACE || game_board[player.b.posX - 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
    }

    return true;
}

bool Game::rightCheck()
{

    switch (player.orientation)
    {
    case REVERSE:
        if (game_board[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    case NEUTRAL:
        if (game_board[player.b.posX + 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    default:
        if (game_board[player.a.posX + 1][player.a.posY] == EMPTY_SPACE || game_board[player.b.posX + 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
    }

    return true;
}

void Game::boardMovement(int shiftX, int shiftY)
{
    clearPieceOnBoard();

    player.a.posX = player.a.posX + shiftX;
    player.b.posX = player.b.posX + shiftX;

    player.a.posY = player.a.posY + shiftY;
    player.b.posY = player.b.posY + shiftY;

    printPieceOnBoard();
}

bool Game::collisionCheck()
{

    if (groundCheck() || pieceCollisionCheck())
    {
        return true;
    }

    return false;
}

bool Game::groundCheck()
{
    if (player.a.posY == 15 || player.b.posY == 15)
    {
        return true;
    }

    return false;
}

bool Game::pieceCollisionCheck()
{
    switch (player.orientation)
    {

    case CLOCKWISE:

        if (game_board[player.b.posX][player.b.posY + 1] != EMPTY_SPACE)
        {
            return true;
        }

        return false;
        break;

    case COUNTER_CLOCKWISE:

        if (game_board[player.a.posX][player.a.posY + 1] != EMPTY_SPACE)
        {
            return true;
        }

        return false;
        break;

    default: //////////bug is here

        if (game_board[player.a.posX][player.a.posY + 1] != EMPTY_SPACE)
        {

            return true;
        }
        else if (game_board[player.b.posX][player.b.posY + 1] != EMPTY_SPACE)
        {

            return true;
        }

        return false;

        break;
    }
}

void Game::contactDrop()
{

    if (game_board[player.a.posX][player.a.posY + 1] == EMPTY_SPACE && player.a.posY != 15)
    {

        columnDrop(player.a.posX);
    }
    else
    {
        floodFillStarter(player.a.posX, player.a.posY);
    }

    if (game_board[player.b.posX][player.b.posY + 1] == EMPTY_SPACE && player.b.posY != 15)
    {
        columnDrop(player.b.posX);
    }
    else
    {
        floodFillStarter(player.b.posX, player.b.posY);
    }
}

void Game::columnDrop(int column)
{

    std::vector<char> aux = {};
    int l = 0;

    for (int i = 0; i < game_board[column].size(); i++)
    {
        if (game_board[column][i] != EMPTY_SPACE)
            aux.push_back(game_board[column][i]);
    }

    for (int j = 0; j < game_board[column].size(); j++)
    {
        if (j < game_board[column].size() - aux.size())
        {
            game_board[column][j] = EMPTY_SPACE;
        }
        else
        {
            game_board[column][j] = aux[l];
            l++;
        }
    }

    floodFillColumn(column);
}

void Game::floodFillColumn(int column)
{

    for (int i = 0; i < game_board[column].size(); i++)
    {
        if (game_board[column][i] != EMPTY_SPACE)
        {
            floodFillStarter(column, i);
        }
    }
}

void Game::floodFillStarter(int x, int y)
{

    currentFlood = {};
    floodCounter = 0;

    floodFill(x, y);

    if (floodCounter > 3)
    {

        deleteFloodfillBlocks();
    }

    currentFlood = {};
    floodCounter = 0;
}

void Game::floodFill(int x, int y)
{
    char c = game_board[x][y];
    Block b = {c, x, y};
    floodCounter++;

    checkedBlocks.push_back(b);
    currentFlood.push_back(b);

    if (x < 7)
    {
        if (game_board[x + 1][y] == c && !isBlockChecked(x + 1, y))
            floodFill(x + 1, y);
    }

    if (x > 0)
    {
        if (game_board[x - 1][y] == c && !isBlockChecked(x - 1, y))
            floodFill(x - 1, y);
    }

    if (y < 15)
    {
        if (game_board[x][y + 1] == c && !isBlockChecked(x, y + 1))
            floodFill(x, y + 1);
    }

    if (y > 0)
    {
        if (game_board[x][y - 1] == c && !isBlockChecked(x, y - 1))
            floodFill(x, y - 1);
    }
}

bool Game::isBlockChecked(int x, int y)
{

    for (size_t i = 0; i < currentFlood.size(); i++)
    {
        if (currentFlood[i].posX == x && currentFlood[i].posY == y)
            return true;
    }

    return false;
}

void Game::deleteFloodfillBlocks()
{
    ////////print order
    std::vector<int> columns = {};

    sdl->drawBoard(getBoard(), getScore(), 300);
    for (size_t i = 0; i < currentFlood.size(); i++)
    {

        game_board[currentFlood[i].posX][currentFlood[i].posY] = EMPTY_SPACE;

        columns.push_back(currentFlood[i].posX);
    }

    

    for (int j = 0; j < columns.size(); j++)
        columnDrop(columns[j]);

    high_score = high_score + 100;

    
    ////////print order
}

void Game::deleteBlocksEffect(){
    
}