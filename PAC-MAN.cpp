#include<ncurses.h>
#include<vector>
using namespace std;

#define X_field (12)
#define Y_field (12)

struct Actor
{
    int Speed;
    int X;
    int Y;
    int Cursor;
    int State;
}
