#include <array>
#include <vector>
#include <bits/stdc++.h>
#include <unistd.h>
#include <random>
#include "SDLManager.h"

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

    int start_x = 3;
    int start_y = 0;

    int highScore = 0;
    int score_multiplier = 1;
    int difficulty_level = 1;
    Piece holding;
    bool holdingPiece = false;
    std::vector<Piece> nextPieces = {};
    std::array<std::array<char, 2>, 3> nextPiecesDrawable;
    char holdingDrawable[2];

    ///Flood fill done on contact blocks, and then each col that gets dropped
    std::vector<Block> checkedBlocks = {};
    std::vector<Block> currentFlood = {};
    int floodCounter = 0;

    char EMPTY_SPACE = '0';
    char possibleBlocks[4] = {'1', '2', '3', '4'};

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

    /////do Drop for
    void contactDrop();
    void columnDrop(int column);

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

    bool checkLose();

    array<array<char, 16>, 8> getBoard()
    {
        return gameBoard;
    };

    int getScore()
    {
        return highScore;
    }
};