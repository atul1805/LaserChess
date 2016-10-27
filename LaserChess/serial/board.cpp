#include "constants.h"
#include <string.h>
#include "board.h"
#include "piece.h"
#include <stdlib.h>
#include <math.h> 
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;

Board::Board() {
    this->gameBoard = new Piece**[9];
    for(int i = 0; i < 9; i++) {
        this->gameBoard[i] = new Piece*[9];
        for(int j = 0; j < 9; j++) {
			this->gameBoard[i][j] = new Piece();
	    }
    }
}

Board::Board(Board *b) {
	this->gameBoard = new Piece**[9];
    for(int i = 0; i < 9; i++) {
	    this->gameBoard[i] = new Piece*[9];
        for(int j = 0; j < 9; j++) {
            this->gameBoard[i][j] = new Piece(b->gameBoard[i][j]);
	    }
    }
}


void Board::initialize() {
	Piece* king1 = new Piece(P1KING, PLAYER1, -1);
    Piece* king2 = new Piece(P2KING, PLAYER2, -1);
	Piece* laser1 = new Piece(P1LASER, PLAYER1, A270);
    Piece* laser2 = new Piece(P2LASER, PLAYER2, A90);
	Piece* hypercube1 = new Piece(P1HYPERCUBE, PLAYER1, -1);
    Piece* hypercube2 = new Piece(P2HYPERCUBE, PLAYER2, -1);
	Piece* splitter1 = new Piece(P1BEAMSPLITTER, PLAYER1, A90);
    Piece* splitter2 = new Piece(P2BEAMSPLITTER, PLAYER2, A270);
	Piece* block11 = new Piece(P1BLOCK1, PLAYER1, A270);
    Piece* block12 = new Piece(P1BLOCK2, PLAYER1, A270);
    Piece* block13 = new Piece(P1BLOCK3, PLAYER1, A270);
	Piece* block14 = new Piece(P1BLOCK4, PLAYER1, A270);
    Piece* block21 = new Piece(P2BLOCK1, PLAYER2, A90);
	Piece* block22 = new Piece(P2BLOCK2, PLAYER2, A90);
    Piece* block23 = new Piece(P2BLOCK3, PLAYER2, A90);
    Piece* block24 = new Piece(P2BLOCK4, PLAYER2, A90);
	Piece* smirror11 = new Piece(P1STRMIRROR1, PLAYER1, A90);
    Piece* smirror12 = new Piece(P1STRMIRROR2, PLAYER1, A0);
	Piece* smirror21 = new Piece(P2STRMIRROR1, PLAYER2, A0);
    Piece* smirror22 = new Piece(P2STRMIRROR2, PLAYER2, A90);
	Piece* dmirror11 = new Piece(P1DIAMIRROR1, PLAYER1, A135);
	Piece* dmirror12 = new Piece(P1DIAMIRROR2, PLAYER1, A45);
    Piece* dmirror21 = new Piece(P2DIAMIRROR1, PLAYER2, A45);
	Piece* dmirror22 = new Piece(P2DIAMIRROR2, PLAYER2, A135);
	Piece* tmirror11 = new Piece(P1TRIMIRROR1, PLAYER1, A315);
	Piece* tmirror12 = new Piece(P1TRIMIRROR2, PLAYER1, A315);
	Piece* tmirror13 = new Piece(P1TRIMIRROR3, PLAYER1, A225);
	Piece* tmirror14 = new Piece(P1TRIMIRROR4, PLAYER1, A225);
	Piece* tmirror15 = new Piece(P1TRIMIRROR5, PLAYER1, A225);
	Piece* tmirror16 = new Piece(P1TRIMIRROR6, PLAYER1, A315);
	Piece* tmirror21 = new Piece(P2TRIMIRROR1, PLAYER2, A45);
	Piece* tmirror22 = new Piece(P2TRIMIRROR2, PLAYER2, A45);
	Piece* tmirror23 = new Piece(P2TRIMIRROR3, PLAYER2, A135);
	Piece* tmirror24 = new Piece(P2TRIMIRROR4, PLAYER2, A135);
	Piece* tmirror25 = new Piece(P2TRIMIRROR5, PLAYER2, A135);
	Piece* tmirror26 = new Piece(P2TRIMIRROR6, PLAYER2, A45);
    
	gameBoard[0][0] = tmirror11;
	gameBoard[0][1] = tmirror12;
	gameBoard[0][2] = dmirror11; 
	gameBoard[0][3] = hypercube1;
	gameBoard[0][4] = king1;
	gameBoard[0][5] = laser1;
	gameBoard[0][6] = dmirror12;
	gameBoard[0][7] = tmirror13;
	gameBoard[0][8] = tmirror14;
	gameBoard[1][0] = tmirror15;
	gameBoard[1][1] = block11;
	gameBoard[1][2] = block12;
	gameBoard[1][3] = smirror11;
	gameBoard[1][4] = smirror12;
	gameBoard[1][5] = splitter1;
	gameBoard[1][6] = block13;
	gameBoard[1][7] = block14;
	gameBoard[1][8] = tmirror16;

	gameBoard[7][0] = tmirror25;
	gameBoard[7][1] = block21;
	gameBoard[7][2] = block22;
	gameBoard[7][3] = splitter2;
	gameBoard[7][4] = smirror21;
	gameBoard[7][5] = smirror22;
	gameBoard[7][6] = block23;
	gameBoard[7][7] = block24;
	gameBoard[7][8] = tmirror26;
	gameBoard[8][0] = tmirror21;
	gameBoard[8][1] = tmirror22;
	gameBoard[8][2] = dmirror21;
	gameBoard[8][3] = laser2;
	gameBoard[8][4] = king2;
	gameBoard[8][5] = hypercube2;
	gameBoard[8][6] = dmirror22;
	gameBoard[8][7] = tmirror23;
	gameBoard[8][8] = tmirror24;
}

bool getUnicode(Piece p, char *t) {
	switch(p.type) {
            case P1KING :
                strcpy(t, u8"\u265B");
				return true;
            case P2KING :
                strcpy(t, u8"\u2655");
				return true;
			case P1LASER :
				if(p.orientation == A0)
					strcpy(t, u8"\u295F");
				else if(p.orientation == A90)
						strcpy(t, u8"\u295C");
				else if(p.orientation == A180)
						strcpy(t, u8"\u295E");
				else if(p.orientation == A270)
						strcpy(t, u8"\u295D");
				return true;
			case P2LASER :
				if(p.orientation == A0)
					strcpy(t, u8"\u2964");
				else if(p.orientation == A90)
						strcpy(t, u8"\u2963");
				else if(p.orientation == A180)
						strcpy(t, u8"\u2962");
				else if(p.orientation == A270)
						strcpy(t, u8"\u2965");
				return true;
			case P1HYPERCUBE :
				strcpy(t, u8"\u25CF");
				return true;
			case P2HYPERCUBE :
				strcpy(t, u8"\u25CB");
				return true;
			case P1TRIMIRROR1 :
			case P1TRIMIRROR2 :
			case P1TRIMIRROR3 :
			case P1TRIMIRROR4 :
			case P1TRIMIRROR5 :
			case P1TRIMIRROR6 :
				if(p.orientation == A315)
					strcpy(t, u8"\u25E4");
				else if(p.orientation == A225)
						strcpy(t, u8"\u25E5");
				else if(p.orientation == A135)
						strcpy(t, u8"\u25E2");
				else if(p.orientation == A45)
						strcpy(t, u8"\u25E3");
				return true;
			case P2TRIMIRROR1 :
			case P2TRIMIRROR2 :
			case P2TRIMIRROR3 :
			case P2TRIMIRROR4 :
			case P2TRIMIRROR5 :
			case P2TRIMIRROR6 :
				if(p.orientation == A315)
					strcpy(t, u8"\u25F8");
				else if(p.orientation == A225)
						strcpy(t, u8"\u25F9");
				else if(p.orientation == A135)
						strcpy(t, u8"\u25FF");
				else if(p.orientation == A45)
						strcpy(t, u8"\u25FA");
				return true;
			case P1STRMIRROR1 :
			case P1STRMIRROR2 :
				if(p.orientation == A0)
                	strcpy(t, u8"\u25AC");
				else if(p.orientation == A90)
                	strcpy(t, u8"\u25AE");
				return true;
            case P2STRMIRROR1 :
			case P2STRMIRROR2 :
				if(p.orientation == A0)
                	strcpy(t, u8"\u25AD");
				else if(p.orientation == A90)
                	strcpy(t, u8"\u25AF");
				return true;
			case P1DIAMIRROR1 :
			case P1DIAMIRROR2 :
			case P2DIAMIRROR1 :
			case P2DIAMIRROR2 :
				if(p.orientation == A45)
                	strcpy(t, u8"\u2215");
				else if(p.orientation == A135)
                	strcpy(t, u8"\u29F5");
				return true;
			case P1BLOCK1 :
			case P1BLOCK2 :
			case P1BLOCK3 :
			case P1BLOCK4 :
				strcpy(t, u8"\u25FC");
				return true;
			case P2BLOCK1 :
			case P2BLOCK2 :
			case P2BLOCK3 :
			case P2BLOCK4 :
				strcpy(t, u8"\u25FB");
				return true;
			case P1BEAMSPLITTER :
				if(p.orientation == A0)
					strcpy(t, u8"\u25B6");
				else if(p.orientation == A90)
						strcpy(t, u8"\u25B2");
				else if(p.orientation == A180)
						strcpy(t, u8"\u25C0");
				else if(p.orientation == A270)
						strcpy(t, u8"\u25BC");
				return true;
			case P2BEAMSPLITTER :
				if(p.orientation == A0)
					strcpy(t, u8"\u25B7");
				else if(p.orientation == A90)
						strcpy(t, u8"\u25B3");
				else if(p.orientation == A180)
						strcpy(t, u8"\u25C1");
				else if(p.orientation == A270)
						strcpy(t, u8"\u25BD");
				return true;
            default : 
				break;
        }
	return false;
}

void Board::print() {
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (gameBoard[i][j]->type != -1) {
				char *ss = (char *)malloc(10);
				if(getUnicode(*gameBoard[i][j], ss)) {
                    if(gameBoard[i][j]->playerId == PLAYER1)
                        printf("\033[1;31m%s\033[0m\t", ss);
                    else
                        printf("\033[1;32m%s\033[0m\t", ss);	
                }
				free(ss);
			} else
                cout <<"__\t"; 
        }
        cout << "\n\n";
    }
}

bool Board::isValidSource(int x, int y, char playerId) {
    if (x < 0 || y < 0 || x > 8 || y > 8)
        return false;
    return gameBoard[x][y]->playerId == playerId;
}

bool Board::isValidDes(int x1, int y1, int x2, int y2, char playerId) {
    if (x2 < 0 || y2 < 0 || x2 > 8 || y2 > 8)
        return false;
    if (gameBoard[x2][y2]->playerId == playerId) {
        if ((playerId == PLAYER1 && gameBoard[x1][y1]->type != P1HYPERCUBE) || (playerId == PLAYER2 && gameBoard[x1][y1]->type != P2HYPERCUBE))
			return false;
    }
	return abs(x1-x2) + abs(y1-y2) == 1;
}

void Board::tmove(int sx, int sy, int dx, int dy) {
    if (gameBoard[sx][sy]->type == P1HYPERCUBE || gameBoard[sx][sy]->type == P2HYPERCUBE) {
        int tx;
        int ty;
        do {
			srand(time(NULL));
            tx = rand() % 9;	
            ty = rand() % 9;
        } while(gameBoard[tx][ty]->type != -1);
        delete gameBoard[tx][ty];
        gameBoard[tx][ty] = new Piece(gameBoard[dx][dy]);
    }
    delete gameBoard[dx][dy];
    gameBoard[dx][dy] = new Piece(gameBoard[sx][sy]);
	delete gameBoard[sx][sy];
    gameBoard[sx][sy] = new Piece();
}

void Board::getPos(char type, int *pos) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
			if (gameBoard[i][j]->type == type) {
                pos[0] = i;
                pos[1] = j;
                break;
            }
        }
    }
}

int Board::isGameOver() {
    int *pos = (int *)malloc(2);
    pos[0] = -1;
    pos[1] = -1;
    getPos(P1KING, pos);
    if (pos[0] == -1 && pos[1] == -1) {
        free(pos);
        return PLAYER2;
    }
    pos[0] = -1;
    pos[1] = -1;
    getPos(P2KING, pos);
    if (pos[0] == -1 && pos[1] == -1) {
        free(pos);
        return PLAYER1;
    }
    free(pos);
    return -1;
}

bool Board::canRotate(int x, int y) {
    return gameBoard[x][y]->orientation != -1;
}

void Board::rotate(int i, int j, char angle) {
    if (gameBoard[i][j]->type == P1DIAMIRROR1 || gameBoard[i][j]->type == P1DIAMIRROR2
        || gameBoard[i][j]->type == P2DIAMIRROR1 || gameBoard[i][j]->type == P2DIAMIRROR2) {
        if (gameBoard[i][j]->orientation == A45)
            gameBoard[i][j]->orientation = A135;
        else if (gameBoard[i][j]->orientation == A135)
            gameBoard[i][j]->orientation = A45;
    } else if (gameBoard[i][j]->type == P1STRMIRROR1 || gameBoard[i][j]->type == P1STRMIRROR2
                || gameBoard[i][j]->type == P2STRMIRROR1 || gameBoard[i][j]->type == P2STRMIRROR2) {
        if (gameBoard[i][j]->orientation == A0)
            gameBoard[i][j]->orientation = A90;
        else if (gameBoard[i][j]->orientation == A90)
            gameBoard[i][j]->orientation = A0;
    } else
        gameBoard[i][j]->orientation = (gameBoard[i][j]->orientation + angle) % A360;
}

bool Board::canFire(int x, int y) {
    return gameBoard[x][y]->type == P1LASER || gameBoard[x][y]->type == P2LASER;
}

void Board::fire(int x, int y) {
    char currOrt = gameBoard[x][y]->orientation;
    if (currOrt == A0)
        fireHelper(x, y + 1, currOrt);
    else if (currOrt == A90)
        fireHelper(x - 1, y, currOrt);
    else if (currOrt == A180)
        fireHelper(x, y - 1, currOrt);
    else if (currOrt == A270)
        fireHelper(x + 1, y, currOrt);
}

bool Board::canPass(int x, int y, char currOrt) {
    if (gameBoard[x][y]->type == -1 || gameBoard[x][y]->type == P1HYPERCUBE || gameBoard[x][y]->type == P2HYPERCUBE)
        return true;
    else if (gameBoard[x][y]->type == P1STRMIRROR1 || gameBoard[x][y]->type == P1STRMIRROR2
            || gameBoard[x][y]->type == P2STRMIRROR1 || gameBoard[x][y]->type == P2STRMIRROR2)
        return gameBoard[x][y]->orientation == currOrt || ((gameBoard[x][y]->orientation + A180) % A360 == currOrt);
    else
        return false;
}

bool Board::canKill(int i, int j, char currOrt) {
    if (gameBoard[i][j]->type == P1LASER || gameBoard[i][j]->type == P2LASER
        || gameBoard[i][j]->type == P1KING || gameBoard[i][j]->type == P2KING)
        return true;
    else if (gameBoard[i][j]->type >= P1BLOCK1 && gameBoard[i][j]->type <= P2BLOCK4) {
        return !((gameBoard[i][j]->orientation + A180) % A360 == currOrt); 
    } else if (gameBoard[i][j]->type == P1STRMIRROR1 || gameBoard[i][j]->type == P1STRMIRROR2
                || gameBoard[i][j]->type == P2STRMIRROR1 || gameBoard[i][j]->type == P2STRMIRROR2) {
        return false;
    } else if (gameBoard[i][j]->type == P1DIAMIRROR1 || gameBoard[i][j]->type == P1DIAMIRROR2
                || gameBoard[i][j]->type == P2DIAMIRROR1 || gameBoard[i][j]->type == P2DIAMIRROR2) {
        return false;
    } else if (gameBoard[i][j]->type == P1HYPERCUBE || gameBoard[i][j]->type == P2HYPERCUBE) {
        return false;
    } else if (gameBoard[i][j]->type >= P1TRIMIRROR1 && gameBoard[i][j]->type <= P2TRIMIRROR6) {
        if (currOrt == A0 && (gameBoard[i][j]->orientation == A225 || gameBoard[i][j]->orientation == A135)) {
            return false;
        } else if (currOrt == A90 && (gameBoard[i][j]->orientation == A225 || gameBoard[i][j]->orientation == A315)) {
            return false;
        } else if (currOrt == A180 && (gameBoard[i][j]->orientation == A315 || gameBoard[i][j]->orientation == A45)) {
            return false;
        } else if (currOrt == A270 && (gameBoard[i][j]->orientation == A45 || gameBoard[i][j]->orientation == A135)) {
            return false;
        } else
            return true;
    } else if (gameBoard[i][j]->type == P1BEAMSPLITTER || gameBoard[i][j]->type == P2BEAMSPLITTER) {
        return gameBoard[i][j]->orientation == currOrt;
    }
}

void Board::reflect(int i, int j, char currOrt, char *ref) {
    if (gameBoard[i][j]->type >= P1BLOCK1 && gameBoard[i][j]->type <= P2BLOCK4)
        ref[0] = (currOrt + A180) % A360; 
    else if (gameBoard[i][j]->type == P1STRMIRROR1 || gameBoard[i][j]->type == P1STRMIRROR2
            || gameBoard[i][j]->type == P2STRMIRROR1 || gameBoard[i][j]->type == P2STRMIRROR2) {
        if (gameBoard[i][j]->orientation != currOrt)
            ref[0] = (currOrt + A180) % A360;
        else
            ref[0] = currOrt;
    } else if (gameBoard[i][j]->type == P1DIAMIRROR1 || gameBoard[i][j]->type == P1DIAMIRROR2
                || gameBoard[i][j]->type == P2DIAMIRROR1 || gameBoard[i][j]->type == P2DIAMIRROR2) {
        if (gameBoard[i][j]->orientation == A135) {
            if (currOrt == A0)
                ref[0] = A270;
            else if (currOrt == A90)
                ref[0] = A180;
            else if (currOrt == A180)
                ref[0] = A90;
            else if (currOrt == A270)
                ref[0] = A0;
        } else if (gameBoard[i][j]->orientation == A45) {
            if (currOrt == A0)
                ref[0] = A90;
            else if (currOrt == A90)
                ref[0] = A0;
            else if (currOrt == A180)
                ref[0] = A270;
            else if (currOrt == A270)
                ref[0] = A180;
        }
    } else if (gameBoard[i][j]->type >= P1TRIMIRROR1 && gameBoard[i][j]->type <= P2TRIMIRROR6) {
        if (gameBoard[i][j]->orientation == A45) {
            if (currOrt == A180)
                ref[0] = A90;
            else if (currOrt == A270)
                ref[0] = A0;
        } else if (gameBoard[i][j]->orientation == A135) {
            if (currOrt == A0)
                ref[0] = A90;
            else if (currOrt == A270)
                ref[0] = A180;
        } else if (gameBoard[i][j]->orientation == A225) {
            if (currOrt == A0)
                ref[0] = A270;
            else if (currOrt == A90)
                ref[0] = A180;
        } else if (gameBoard[i][j]->orientation == A315) {
            if (currOrt == A90)
                ref[0] = A0;
            else if (currOrt == A180)
                ref[0] = A270;
        }
    } else if (gameBoard[i][j]->type == P1BEAMSPLITTER || gameBoard[i][j]->type == P2BEAMSPLITTER) {
        if (gameBoard[i][j]->orientation == A0) {
            if (currOrt == A90)
                ref[0] = A0;
            else if (currOrt == A180) {
                ref[0] = A90;
                ref[1] = A270;
            } else if (currOrt == A270)
                ref[0] = A0;
        } else if (gameBoard[i][j]->orientation == A90) {
            if (currOrt == A0)
                ref[0] = A90;
            else if (currOrt == A180)
                ref[0] = A90;
            else if (currOrt == A270) {
                ref[0] = A0;
                ref[1] = A180;
            }
        } else if (gameBoard[i][j]->orientation == A180) {
            if (currOrt == A0) {
                ref[0] = A90;
                ref[1] = A270;
            } else if (currOrt == A90)
                ref[0] = A180;
            else if (currOrt == A270)
                ref[0] = A180;
        } else if (gameBoard[i][j]->orientation == A270) {
            if (currOrt == A0)
                ref[0] = A270;
            else if (currOrt == A90) {
                ref[0] = A0;
                ref[1] = A180;
            } else if (currOrt == A180)
                ref[0] = A270;
        }
    }
}

void Board::fireHelper(int x, int y, char currOrt) {
    if (x < 0 || y < 0 || x > 8 || y > 8)
        return;
    char *nextOrt = (char *)malloc(2);
    nextOrt[0] = -1;
    nextOrt[1] = -1;
    if (canPass(x, y, currOrt))
        nextOrt[0] = currOrt;
    else if (canKill(x, y, currOrt)) {
	    delete gameBoard[x][y];
		gameBoard[x][y] = new Piece();
        return;
    } else
        reflect(x, y, currOrt, nextOrt);
    
    for (int i = 0; i < 2; i++) {
        if (nextOrt[i] == A0)
            fireHelper(x, y + 1, nextOrt[i]);
        else if (nextOrt[i] == A90)
            fireHelper(x - 1, y, nextOrt[i]);
        else if (nextOrt[i] == A180)
            fireHelper(x, y - 1, nextOrt[i]);
        else if (nextOrt[i] == A270)
            fireHelper(x + 1, y, nextOrt[i]);
    }
    free(nextOrt);
}

int getScore(Piece *piece) {
	if(piece->type == P1LASER || piece->type == P2LASER)
		return LASER;
	if(piece->type == P1BEAMSPLITTER || piece->type == P2BEAMSPLITTER)
		return BEAMSPLITTER;
	if(piece->type >= P1BLOCK1 && piece->type <= P2BLOCK4)
		return BLOCK;
    if(piece->type == P1STRMIRROR1 || piece->type == P1STRMIRROR2 || piece->type == P2STRMIRROR1 || piece->type == P2STRMIRROR2)
        return STRMIRROR;
	if(piece->type == P1DIAMIRROR1 || piece->type == P1DIAMIRROR2 || piece->type == P2DIAMIRROR1 || piece->type == P2DIAMIRROR2)
		return DIAMIRROR;
	if(piece->type >= P1TRIMIRROR1 && piece->type <= P2TRIMIRROR6)
		return TRIMIRROR;
	if(piece->type == P1KING || piece->type == P2KING)
		return KING;
	if(piece->type == P1HYPERCUBE || piece->type == P2HYPERCUBE)
		return HYPERCUBE;
}

int Board::score(char playerId) {
    int score = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (gameBoard[i][j]->playerId == PLAYER1)
                score -= getScore(gameBoard[i][j]);
            else if (gameBoard[i][j]->playerId == PLAYER2)
                score += getScore(gameBoard[i][j]);
        }
    }
    if (DEPTH % 2 != 0)
	    return playerId == PLAYER1 ? score : -score;
    else
        return playerId == PLAYER1 ? -score : score;
}

void Board::makeGenericMove(Move* mv, char playerId) {
    if (mv->type=='M')
		tmove(mv->sx, mv->sy, mv->dx, mv->dy);
    else if (mv->type=='R')
        rotate(mv->sx, mv->sy, mv->angle);
    else if (mv->type=='F')
        fire(mv->sx, mv->sy);
}
