#include <string>

using namespace std;

class Move {
    public:
        char type;
        int sx;
        int sy;
        int dx;
        int dy;
        char angle;

        Move(char type, int sx, int sy, int dx, int dy, char angle);
        void displayMove();
        bool isValid();
};
