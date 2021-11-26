#include "Game.h"

Game::Game()
{
    for (int i = 0; i < gameBoard.size(); i++)
    {
        for (int j = 0; j < gameBoard.at(i).size(); j++)
        {
            gameBoard[i][j] = EMPTY_SPACE;
        }
    }

    initPieces();
    assignPiece(false);
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

        if (input == QUIT)
        {
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

            if (collisionCheck())
            {

                contactDrop();

                if (checkLose())
                {
                    quit = true;
                    return 1;
                }
                else
                {
                    assignPiece(false);
                }
            }
            else
            {
                movePiece(input);
            }
        }
        sdl->drawBoard(getBoard(), getScore(), nextPiecesDrawable, holdingDrawable, 0);
    }

    return 0;
}

void Game::initPieces()
{

    for (int i = 0; i < nextPiecesDrawable.size(); i++)
    {
        nextPieces.push_back(generatePiece());
    }

    convertNextPieces();
};

void Game::hold()
{

    Piece aux = player;

    if (!holdingPiece)
    {
        assignPiece(true);

        holdingPiece = true;
    }
    else
    {
        player = holding;
    }

    clearPieceOnBoard();

    player.a.posX = aux.a.posX;
    player.a.posY = aux.a.posY;
    player.b.posX = aux.b.posX;
    player.b.posY = aux.b.posY;

    printPieceOnBoard();

    holding = aux;
    holding.a.posX = start_x;
    holding.a.posY = start_y;
    holding.b.posX = start_x + 1;
    holding.b.posY = start_y;

    holdingDrawable[0] = holding.a.num;
    holdingDrawable[1] = holding.b.num;
}

Game::Piece Game::generatePiece()
{

    Piece new_piece;

    int cOne = rand() % 4;
    int cTwo = rand() % 4;

    firstBlock = {possibleBlocks[cOne],
                  start_x,
                  start_y};

    secondBlock = {possibleBlocks[cTwo],
                   start_x + 1,
                   start_y};

    new_piece = {
        firstBlock,
        secondBlock,
        NEUTRAL};

    return new_piece;
}

void Game::assignPiece(bool hold)
{

    /////WORK
    player = nextPieces[0];

    std::rotate(nextPieces.begin(), nextPieces.begin() + 1, nextPieces.end());
    nextPieces.pop_back();
    nextPieces.push_back(generatePiece());

    convertNextPieces();

    if (!hold)
        boardMovement(0, 0);

    checkedBlocks = {};
}

void Game::convertNextPieces()
{
    for (int i = 0; i < nextPieces.size(); i++)
    {
        nextPiecesDrawable[i][0] = nextPieces[i].a.num;
        nextPiecesDrawable[i][1] = nextPieces[i].b.num;
    }
}

bool Game::checkLose()
{
    if (gameBoard[start_x][start_y] != EMPTY_SPACE || gameBoard[start_x + 1][start_y] != EMPTY_SPACE)
    {
        return true;
    }

    return false;
}

void Game::clearPieceOnBoard()
{
    gameBoard[player.a.posX][player.a.posY] = EMPTY_SPACE;
    gameBoard[player.b.posX][player.b.posY] = EMPTY_SPACE;
}

void Game::printPieceOnBoard()
{
    gameBoard[player.a.posX][player.a.posY] = player.a.num;
    gameBoard[player.b.posX][player.b.posY] = player.b.num;
}

void Game::rotatePiece(bool right)
{

    clearPieceOnBoard();

    if (right)
    {
        switch (player.orientation)
        {
        case NEUTRAL:

            if (player.a.posY < 15 && gameBoard[player.a.posX][player.a.posY + 1] == EMPTY_SPACE)
            {
                player.orientation = CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY + 1;
            }

            break;

        case CLOCKWISE:
            if (player.a.posX > 0 && gameBoard[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = REVERSE;

                player.b.posX = player.a.posX - 1;
                player.b.posY = player.a.posY;
            }
            break;
        case REVERSE:

            if (player.a.posY > 0 && gameBoard[player.a.posX][player.a.posY - 1] == EMPTY_SPACE)
            {
                player.orientation = COUNTER_CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY - 1;
            }
            break;
        case COUNTER_CLOCKWISE:

            if (player.a.posX < 7 && gameBoard[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
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

            if (player.a.posY > 0 && gameBoard[player.a.posX][player.a.posY - 1] == EMPTY_SPACE)
            {
                player.orientation = COUNTER_CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY - 1;
            }

            break;

        case CLOCKWISE:

            if (player.a.posX < 7 && gameBoard[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
            {
                player.orientation = NEUTRAL;

                player.b.posX = player.a.posX + 1;
                player.b.posY = player.a.posY;
            }
            break;
        case REVERSE:

            if (player.a.posY < 15 && gameBoard[player.a.posX][player.a.posY + 1] == EMPTY_SPACE)
            {
                player.orientation = CLOCKWISE;

                player.b.posX = player.a.posX;
                player.b.posY = player.a.posY + 1;
            }
            break;
        case COUNTER_CLOCKWISE:

            if (player.a.posX > 0 && gameBoard[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
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
        if (player.a.posY < 15 && player.b.posY < 15)
        {
            while (!collisionCheck())
                boardMovement(0, 1);
        }

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

        hold();

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
        if (gameBoard[player.a.posX - 1][player.a.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    case REVERSE:
        if (gameBoard[player.b.posX - 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    default:
        if (gameBoard[player.a.posX - 1][player.a.posY] == EMPTY_SPACE || gameBoard[player.b.posX - 1][player.b.posY] == EMPTY_SPACE)
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
        if (gameBoard[player.a.posX + 1][player.a.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    case NEUTRAL:
        if (gameBoard[player.b.posX + 1][player.b.posY] == EMPTY_SPACE)
            return true;
        else
            return false;
        break;
    default:
        if (gameBoard[player.a.posX + 1][player.a.posY] == EMPTY_SPACE || gameBoard[player.b.posX + 1][player.b.posY] == EMPTY_SPACE)
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

        if (gameBoard[player.b.posX][player.b.posY + 1] != EMPTY_SPACE)
        {
            return true;
        }

        return false;
        break;

    case COUNTER_CLOCKWISE:

        if (gameBoard[player.a.posX][player.a.posY + 1] != EMPTY_SPACE)
        {
            return true;
        }

        return false;
        break;

    default: //////////bug is here

        if (gameBoard[player.a.posX][player.a.posY + 1] != EMPTY_SPACE)
        {

            return true;
        }
        else if (gameBoard[player.b.posX][player.b.posY + 1] != EMPTY_SPACE)
        {

            return true;
        }

        return false;

        break;
    }
}

void Game::contactDrop()
{

    if (gameBoard[player.a.posX][player.a.posY + 1] == EMPTY_SPACE && player.a.posY != 15)
    {

        columnDrop(player.a.posX);
    }
    else
    {
        floodFillStarter(player.a.posX, player.a.posY);
    }

    if (gameBoard[player.b.posX][player.b.posY + 1] == EMPTY_SPACE && player.b.posY != 15)
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

    for (int i = 0; i < gameBoard[column].size(); i++)
    {
        if (gameBoard[column][i] != EMPTY_SPACE)
            aux.push_back(gameBoard[column][i]);
    }

    for (int j = 0; j < gameBoard[column].size(); j++)
    {
        if (j < gameBoard[column].size() - aux.size())
        {
            gameBoard[column][j] = EMPTY_SPACE;
        }
        else
        {
            gameBoard[column][j] = aux[l];
            l++;
        }
    }

    floodFillColumn(column);
}

void Game::floodFillColumn(int column)
{

    for (int i = 0; i < gameBoard[column].size(); i++)
    {
        if (gameBoard[column][i] != EMPTY_SPACE)
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
    char c = gameBoard[x][y];
    Block b = {c, x, y};
    floodCounter++;

    checkedBlocks.push_back(b);
    currentFlood.push_back(b);

    if (x < 7)
    {
        if (gameBoard[x + 1][y] == c && !isBlockChecked(x + 1, y))
            floodFill(x + 1, y);
    }

    if (x > 0)
    {
        if (gameBoard[x - 1][y] == c && !isBlockChecked(x - 1, y))
            floodFill(x - 1, y);
    }

    if (y < 15)
    {
        if (gameBoard[x][y + 1] == c && !isBlockChecked(x, y + 1))
            floodFill(x, y + 1);
    }

    if (y > 0)
    {
        if (gameBoard[x][y - 1] == c && !isBlockChecked(x, y - 1))
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
    
    std::vector<int> columns = {};

    array<array<char, 16>, 8> oldBoard = getBoard();

    for (size_t i = 0; i < currentFlood.size(); i++)
    {

        gameBoard[currentFlood[i].posX][currentFlood[i].posY] = EMPTY_SPACE;

        columns.push_back(currentFlood[i].posX);
    }

    deleteBlocksEffect(oldBoard);

    for (int j = 0; j < columns.size(); j++)
        columnDrop(columns[j]);

    highScore = highScore + 100;


}

void Game::deleteBlocksEffect(array<array<char, 16>, 8> oldBoard)
{

    for (int i = 0; i < 5; i++)
    {

        sdl->drawBoard(oldBoard, getScore(), nextPiecesDrawable, holdingDrawable, 50);
        sdl->drawBoard(getBoard(), getScore(), nextPiecesDrawable, holdingDrawable, 50);
    }
    sdl->playSoundEffect();
}