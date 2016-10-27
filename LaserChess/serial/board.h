#include "constants.h"
#include <stdlib.h>
#include "move.h"

class Piece;

class Board {
    public:
        Piece ***gameBoard;
        Board();
        Board(Board *);
        void initialize();
	    void print();
        bool isValidSource(int x, int y, char playerId);
        bool isValidDes(int x1, int y1, int x2, int y2, char playerId);
        void tmove(int sx, int sy, int dx, int dy);
        int isGameOver();
        void getPos(char type, int *pos);
        bool canRotate(int x, int y);
        void rotate(int x, int y, char angle);
        bool canFire(int x, int y);
        void fire(int x, int y);
        void fireHelper(int x, int y, char ort);
        bool canPass(int x, int y, char ort);
        bool canKill(int x, int y, char ort);
        void reflect(int x, int y, char ort, char *ref);

        int score(char playerId);
        void makeGenericMove(Move* mv, char playerId);
};
