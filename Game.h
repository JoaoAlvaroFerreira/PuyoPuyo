#include <array>
#include "SDLManager.h"

using namespace std;

class Game
{

    array<array<char, 16>, 8> game_board = {};

    enum PIECE_ROTATION
    {
        NEUTRAL,     //a b
        SECOND_DOWN, //a
                     //b
        REVERSE,     //b a
        SECOND_UP,   //b
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

public:
    Game();
    void movePiece(USER_INPUT input);
    void rotatePiece();
    void boardMovement(int shiftX, int shiftY);
    bool collisionCheck();
    void contactDrop();
    void contactDropAux(Block block);
    void generatePiece();
    array<array<char, 16>, 8> getBoard()
    {
        return game_board;
    };
};