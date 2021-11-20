#include "Game.h"

Game::Game()
{
    for (std::array<char, 16> row : game_board)
        row.fill('0');

    main = {
        '1',
        5,
        5};
};

void Game::movePiece(USER_INPUT input)
{

    switch (input)
    {
    case UP:
        if (main.posY > 0)
        {
            boardMovement(main.posX, main.posY, main.posX, main.posY - 1, main.num);
            main.posY--;
        }
        break;
    case DOWN:
        if (main.posY < 15)
        {
            boardMovement(main.posX, main.posY, main.posX, main.posY + 1, main.num);
            main.posY++;
        }
        break;
    case LEFT:
        if (main.posX > 0)
        {
            boardMovement(main.posX, main.posY , main.posX - 1, main.posY , main.num);
             main.posX--;
        }
        break;
    case RIGHT:
        if (main.posX < 7)
        {
            boardMovement(main.posX, main.posY, main.posX + 1, main.posY , main.num);
            main.posX++;
        }
        break;

    default:
        break;
    }
}

void Game::boardMovement(int oldX, int oldY, int newX, int newY, char c)
{
    game_board[oldX][oldY] = '0';
    game_board[newX][newY] = c;
}