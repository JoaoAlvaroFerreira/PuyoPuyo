#include "Game.h"

Game::Game()
{
    for (int i = 0; i < game_board.size(); i++)
    {
        for (int j = 0; j < game_board.at(i).size(); j++)
        {
            game_board[i][j] = '0';
        }
    }

    generatePiece();
};

void Game::generatePiece()
{
    firstBlock = {'1',
                  start_x,
                  start_y};

    secondBlock = {'2',
                   start_x + 1,
                   start_y};

    player = {
        firstBlock,
        secondBlock,
        NEUTRAL};

    game_board[firstBlock.posX][firstBlock.posY] = firstBlock.num;
    game_board[secondBlock.posX][secondBlock.posY] = secondBlock.num;
    boardMovement(0, 0);
}

void Game::rotatePiece()
{
}

void Game::movePiece(USER_INPUT input)
{

    switch (input)
    {
        /*
    case UP: ////////////CHECK THAT YOU CAN'T DELETE PIECES FROM BELOW OR BY SPINNING
        if (player.a.posY > 0 && player.b.posY > 0)
        {
            boardMovement(0,-1);
            
        }
        break;
        */
    case DOWN:
        if (player.a.posY < 15 && player.b.posY < 15)
        {
            boardMovement(0, 1);
        }
        break;
    case LEFT:
        if (player.a.posX > 0 && player.b.posX > 0)
        {
            boardMovement(-1, 0);
        }
        break;
    case RIGHT:
        if (player.a.posX < 7 && player.b.posX < 7)
        {
            boardMovement(1, 0);
        }
        break;

    default:
        break;
    }
}

void Game::boardMovement(int shiftX, int shiftY)
{
    game_board[player.a.posX][player.a.posY] = '0';
    game_board[player.b.posX][player.b.posY] = '0';

    player.a.posX = player.a.posX + shiftX;
    player.b.posX = player.b.posX + shiftX;

    player.a.posY = player.a.posY + shiftY;
    player.b.posY = player.b.posY + shiftY;

    game_board[player.a.posX][player.a.posY] = player.a.num;
    game_board[player.b.posX][player.b.posY] = player.b.num;
}

bool Game::collisionCheck()
{

    // || game_board[player.a.posX][player.a.posY+1] != '0' || game_board[player.b.posX][player.a.posY+1] != '0'
    if (player.a.posY == 15 || player.b.posY == 15 || game_board[player.a.posX][player.a.posY + 1] != '0' || game_board[player.b.posX][player.a.posY + 1] != '0')
    {
        return true;
    }

    return false;
}

void Game::contactDrop()
{

    if (game_board[player.a.posX][player.a.posY + 1] == '0' && player.a.posY != 15)
    {
        
        contactDropAux(player.a);
    }
    else if (game_board[player.b.posX][player.b.posY + 1] == '0' && player.b.posY != 15)
    {
        contactDropAux(player.b);
    }
}

void Game::contactDropAux(Block block) ///WILL HAVE TO BE REWORKED TO DROP ENTIRE COLUMN INSTEAD OF JUST ONE PUYO, do it by saving the above puyos on an array, finding the contact like now and then re-writing them on top
{

    bool contact = false;
    int i = block.posY;
    while(!contact)
    {

        if (game_board[block.posX][ i + 1] != '0' || i == 15)
        {
            game_board[block.posX][block.posY] = '0';
            game_board[block.posX][ i ] = block.num;

            contact = true;
           
        }
        i++;
    }
}
