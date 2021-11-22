#include <array>
#include <vector>
#include <bits/stdc++.h>
#include "SDLManager.h"

using namespace std;

class Game
{

    array<array<char, 16>, 8> game_board = {};

    enum PIECE_ROTATION
    {
        NEUTRAL,     //a b
        CLOCKWISE, //a
                     //b
        REVERSE,     //b a
        COUNTER_CLOCKWISE,   //b
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

    ///Flood fill done on contact blocks, and then each row that gets dropped
    std::vector<Block> checkedBlocks = {};
    std::vector<Block> currentFlood = {};
    int floodCounter = 0;

    




public:
    Game();
    void clearPieceOnBoard();
    void printPieceOnBoard();
    void movePiece(USER_INPUT input);
    void rotatePiece(bool right);
    void boardMovement(int shiftX, int shiftY);

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


    void generatePiece();
    array<array<char, 16>, 8> getBoard()
    {
        return game_board;
    };
};