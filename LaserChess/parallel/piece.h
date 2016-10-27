#include<iostream>
#include <stdio.h>

using namespace std;

class Piece {
    public:
        char type;
        char playerId;
        char orientation;

        Piece() {
            this->type = -1;
            this->playerId = -1;
            this->orientation = -1;
		}
								
		Piece(char type, char playerId, char orientation) {
            this->type = type;
            this->playerId = playerId;
            this->orientation = orientation;
		}

        Piece(Piece *p) {
            this->type = p->type;
            this->playerId = p->playerId;
            this->orientation = p->orientation;
		}
};
