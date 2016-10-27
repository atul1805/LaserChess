#include <iostream>
#include "move.h"
#include "constants.h"
#include <math.h> 
#include <string>

using namespace std;

Move::Move(char type, int sx, int sy, int dx, int dy, char angle) {
    this->type = type;
    this->sx = sx;
    this->sy = sy;
    this->dx = dx;
    this->dy = dy;
    this->angle = angle;
}

bool Move::isValid() {
    bool res = false;
    if (this->type=='M') {
        if (this->sx >= 0 && this->sx < 9 && this->sy >= 0 && this->sy < 9
            && this->dx >= 0 && this->dx < 9 && this->dy >= 0 && this->dy < 9)
            res = true;
    } else if (this->type=='R') {
        if (this->sx >= 0 && this->sx < 9 && this->sy >= 0 && this->sy < 9 && this->angle % A90 == 0)
            res = true;
    } else if (this->type=='F') {
        if (this->sx >= 0 && this->sx < 9 && this->sy >= 0 && this->sy < 9)
            res = true;
    }
    return res;
}

void Move::displayMove() {
	int angle;
	if(this->type=='R')
		angle = (int)(this->angle * 5);
    cout << this->type << " " << this->sx << " " << this->sy << " " << this->dx << " " << this->dy << " " << angle << "\n";
}
