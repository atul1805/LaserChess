// To compile: g++ -std=c++11 -o lchess board.cpp LaserChess.cpp move.cpp
// To run    : ./lchess

#include "constants.h"
#include "board.h"
#include <iostream>
#include <vector>
#include "piece.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <limits>
using namespace std;

vector<Board*> all_boards;
vector<vector<Move*>* > all_moves;

void manualMove(Board *brd) {
    while (true) {
        int x;
        int y;
	
        cout << "Select a piece for turn (X,Y)\n";
        cin.clear();
		cin >> x >> y;
		while (!brd->isValidSource(x, y, PLAYER1)) {
            cout << "Invalid position. Select again\n";
			cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            cin >> x >> y;
        }
        char action;        
        while (true) {
            cout << "Enter action:\nM to Move\nR to Rotate\nF to Fire\n";
            cin >> action;
            if (action == 'M') {
                cout << "Enter destination (X,Y)\n";
                int dx;
                int dy;
                cin >> dx >> dy;
                while (!brd->isValidDes(x, y, dx, dy, PLAYER1)) {
                    cout << "Invalid position. Select again\n";
					cin.clear();
					std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            		cin >> dx >> dy;
                }
                brd->tmove(x, y, dx, dy);
                brd->print();
                break;
            } else if (action == 'R') {
                if (!brd->canRotate(x, y)) {
                    cout << "Invalid Action for this piece\n";
                    continue;
                }
                cout << "Enter Angle in anticlockwise in multiples of 90 \n";
                int angle;
                cin >> angle;
                brd->rotate(x, y, angle/5);
                brd->print();
                break;
            } else if (action == 'F') {
                if (!brd->canFire(x, y)) {
                    cout << "Invalid Action for this piece\n";
                    continue;
                }
                brd->fire(x, y);
                brd->print();
                break;
            } else
                cout << "Invalid action. Select again\n";
        }
        break;
    }
}

void getNextMoves(Board* b, char playerId, vector<Move*> *moves) {
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
			if (b->gameBoard[i][j]->playerId == playerId && ((playerId == PLAYER1 && b->gameBoard[i][j]->type != P1HYPERCUBE)
                                                            || (playerId == PLAYER2 && b->gameBoard[i][j]->type != P2HYPERCUBE))) {
				Move *m1 = new Move('M', i, j, i + 1, j, -1);
			    if(m1->isValid() && b->isValidDes(i, j, i + 1, j, playerId))
				    moves->push_back(m1);
				else
					delete m1;
			    Move *m2 = new Move('M', i, j, i - 1, j, -1);
			    if(m2->isValid() && b->isValidDes(i, j, i - 1, j, playerId))
				    moves->push_back(m2);
				else
					delete m2;
			    Move *m3 = new Move('M', i, j, i, j + 1, -1);
			    if(m3->isValid() && b->isValidDes(i, j, i, j + 1, playerId))
				    moves->push_back(m3);
				else
					delete m3;
			    Move *m4 = new Move('M', i, j, i, j - 1, -1);
			    if(m4->isValid() && b->isValidDes(i, j, i, j - 1, playerId))
				    moves->push_back(m4);
				else
					delete m4;
                if (b->canRotate(i, j)) {
                    Move *m5 = new Move('R', i, j, -1, -1, A90);
			        if(m5->isValid())
				        moves->push_back(m5);
					else
						delete m5;
                    Move *m6 = new Move('R', i, j, -1, -1, A180);
			        if(m6->isValid())
				        moves->push_back(m6);
					else
						delete m6;
                    Move *m7 = new Move('R', i, j, -1, -1, A270);
			        if(m7->isValid())
				        moves->push_back(m7);
					else
						delete m7;
                }
                if (b->canFire(i, j)) {
                    Move *m8 = new Move('F', i, j, -1, -1, -1);
			        if(m8->isValid())
				        moves->push_back(m8);
					else
						delete m8;
                }
            }
        }
    }
}

void deleteMoves(vector<Move*> *moves) {
	for(long unsigned int i = 0; i < moves->size(); i++) {
		//moves->at(i)->type.clear();	
		delete moves->at(i);
	}
}
void delete_all_moves() {
	long unsigned int count = 0;
	for(long unsigned int i = 0; i < all_moves.size(); i++) {
        count += all_moves[i]->size();
		deleteMoves(all_moves[i]);
		all_moves[i]->clear();
	}
    //printf("Deleted %lu Moves\n", count);
	all_moves.clear();
}

void deleteBoard(Board *board) {
	for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
			delete board->gameBoard[i][j];
		}
		delete board->gameBoard[i];
	}
	delete board->gameBoard;
    delete board;
}

void delete_all_boards() {
	printf("board delete : ready to delete %lu entries\n", all_boards.size());
	for(long unsigned int i = 0; i < all_boards.size(); i++) {
		deleteBoard(all_boards[i]);
	}
	all_boards.clear();
}

void getCompMoves(Board* b, char playerId, vector<vector<Move*> > *TwoMoves) {
    vector<Move*> *moves1 = new vector<Move*>;
    getNextMoves(b, playerId, moves1);
	all_moves.push_back(moves1);
	Board *bCopy;
	for(long unsigned int i = 0; i < moves1->size(); i++) {
    /*    bCopy = new Board(b);
		bCopy->makeGenericMove(moves1->at(i), playerId);
		vector<Move*> *moves2 = new vector<Move*>;
		getNextMoves(bCopy, playerId, moves2);
        deleteBoard(bCopy);
        all_moves.push_back(moves2);*/
		vector<Move*> *temp = new vector<Move*>;
		//for(long unsigned int j = 0; j < moves2->size(); j++) {
			temp->push_back(moves1->at(i));
			//temp->push_back(moves2->at(j));
            TwoMoves->push_back(*temp);
            temp->clear();
		//}
		delete temp;
	}
}

int scout(Board* b , vector<Move*> m , int alpha, int beta, char playerId, int depth) {
    b->makeGenericMove(m[0], playerId);
    //b->makeGenericMove(m[1], playerId);
    
    if (depth == 0)
        return b->score(playerId);

    vector<vector<Move*> > *children = new vector<vector<Move*> >();
    getCompMoves(b, playerId == PLAYER1 ? PLAYER2 : PLAYER1, children);
    Board *bCopy;
    if (playerId == PLAYER2) {
		for(long unsigned int i = 0; i < children->size(); i++) {
            bCopy = new Board(b);
            alpha = max(alpha , scout(bCopy, children->at(i), alpha, beta, PLAYER1, depth - 1));
            deleteBoard(bCopy);
            if(beta >= alpha)
                break;
        }
        delete children;
		return alpha;
    } else {
		for(long unsigned int i = 0; i < children->size() ; i++) {
            bCopy = new Board(b);
            beta = min(beta, scout(bCopy, children->at(i), alpha, beta, PLAYER2, depth - 1));
            deleteBoard(bCopy);
            if (beta <= alpha)
                break;
        }
        delete children;
		return beta;
    }
}

vector<Move*> getBestCompMove(Board *b, char playerId) {
	vector<vector<Move*> > *TwoMoves = new vector<vector<Move*> >;
    getCompMoves(b, playerId, TwoMoves);
	vector<int> *bestMoves = new vector<int>;

    Board *bCopy;
    int maxScore = -INFTY;
    for(long unsigned int i = 0; i < TwoMoves->size() ; i++) {
        if (i == 792 || i == 953 || i == 971) {
            continue;
        }
        bCopy = new Board(b);
        int score = scout(bCopy, TwoMoves->at(i), -INFTY, INFTY, playerId, DEPTH);
        deleteBoard(bCopy);
		if(score >= maxScore) {
			if(score > maxScore)
                bestMoves->clear();
            maxScore = score;
            bestMoves->push_back(i);
        }
    }
//	printf(" FINAL SCORE %d\n", maxScore);
	srand(time(NULL));
	int chosen_move = bestMoves->at(rand() % bestMoves->size());
	bestMoves->clear();
	delete bestMoves;	//this wud go after next line
	vector<Move*> final2 = TwoMoves->at(chosen_move);
	for(long unsigned int i = 0; i < TwoMoves->size(); i++) {
		(TwoMoves->at(i)).clear();
		//delete (&TwoMoves->at(i));	//DONT WORRY ABOUT THIS DELETEION, ALL MOVES ANYWAY GETS DELETED SONNER OR LATER
	}
	TwoMoves->clear();
	return final2;
}

int main() {
    Board *brd = new Board;
    brd->initialize();
    brd->print();
	printf("------------------------------------------------------------------\n");
    clock_t start;
    double duration;

    int i = 0;
    while (i < 10) {
        int won = brd->isGameOver();
        if (won != -1) {
            if (won == PLAYER1)
                cout << "You Won\n";
            else
                cout << "Computer Won\n";
            break;
        }
		
        manualMove(brd);
        //manualMove(brd);

        won = brd->isGameOver();
        if (won != -1) {
            if (won == PLAYER1)
                cout << "You Won\n";
            else
                cout << "Computer Won\n";
            break;
        }
        
        start = clock();
		vector<Move*> bestMove = getBestCompMove(brd, PLAYER2);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        cout << "Time: "<< duration <<'\n';

		printf("Comp's %d move.\n", i + 1);
        bestMove.at(0)->displayMove();
        //bestMove.at(1)->displayMove();
        brd->makeGenericMove(bestMove.at(0), PLAYER2);
		//brd->makeGenericMove(bestMove.at(1), PLAYER2);
		bestMove.clear();
        brd->print();
		printf("------------------------------------------------------------------\n");
        i++;
		//delete_all_boards();
		delete_all_moves();
    }   
    return 0;
}
