#include <array>
#include "SDLManager.h"

using namespace std;

class Game{

    
    array<array<char,16>,8> game_board = {};

    struct Piece{
        char num;
        int posX;
        int posY;        
    };

    Piece main;
   
    public:
    Game();
    void movePiece(USER_INPUT input);
    void boardMovement(int oldX, int oldY, int newX, int newY, char c);

    array<array<char,16>,8> getBoard(){ return game_board;};

};