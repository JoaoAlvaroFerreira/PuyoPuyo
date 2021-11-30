#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>
#include <bits/stdc++.h>
#include <unistd.h>
#include <random>
#include "SDLManager.h"
#include "Utils.h"

using namespace std;

class Game
{

    array<array<char, 16>, 8> gameBoard = {};

    enum PIECE_ROTATION
    {
        NEUTRAL,           //a b
        CLOCKWISE,         //a
                           //b
        REVERSE,           //b a
        COUNTER_CLOCKWISE, //b
                           //a
    };

    struct Block
    {
        char num;
        int posX;
        int posY;
    };

    struct Piece
    {
        Block a;
        Block b;
        int orientation;
    };

    Piece player;
    Block firstBlock;
    Block secondBlock;

    const int start_x = 3;
    const int start_y = 0;

    std::vector<int> scores;
    int highScore = 0;
    int comboCounter = 0;
    int difficultyLevel = 0;
    const int difficultyTresholds[10] = {100, 400, 1200, 2000, 3000, 4500, 6000, 8000, 10000, 12000};
    double game_speed;
    Piece holding;
    bool holdingPiece = false;
    std::vector<Piece> nextPieces = {};
    std::array<std::array<char, 2>, 3> nextPiecesDrawable;
    char holdingDrawable[2];

    ///Flood fill done on contact blocks, and then each col that gets dropped
    std::vector<Block> checkedBlocks = {};
    std::vector<Block> currentFlood = {};
    int floodCounter = 0;

    const char EMPTY_SPACE = '0';
    const int MAX_SCORES_SAVED = 8;
    const char possibleBlocks[4] = {'1', '2', '3', '4'};

    std::chrono::time_point<std::chrono::system_clock> messageClock;
    std::string currentMessage = " ";
    double messageTime = 2;

    bool pause;

    SDLManager *sdl;

public:
    Game();

    int gameLoop();

    void setGraphics(SDLManager *sdlManager) { sdl = sdlManager; };
    void clearPieceOnBoard();
    void printPieceOnBoard();
    void movePiece(USER_INPUT input);
    void rotatePiece(bool right);
    void boardMovement(int shiftX, int shiftY);

    bool rightCheck();
    bool leftCheck();
    bool collisionCheck();
    bool groundCheck();
    bool pieceCollisionCheck();

    void contactDrop();
    void columnDrop(int column, bool multiple);

    void floodFillStarter(int x, int y);
    void floodFill(int x, int y);
    void floodFillColumn(int column); //////do after every delete & drop
    bool isBlockChecked(int x, int y);

    void deleteFloodfillBlocks();
    void deleteBlocksEffect(array<array<char, 16>, 8> oldBoard);

    void initPieces();
    Piece generatePiece();
    void assignPiece(bool hold);
    void convertNextPieces();
    void hold();
    void setMessage(std::string message);

    bool emptyBoardCheck();
    void difficultyCheck();
    bool checkLose();
    void writeScore();

    array<array<char, 16>, 8> getBoard()
    {
        return gameBoard;
    };

    int getScore()
    {
        return highScore;
    }
};

#endif