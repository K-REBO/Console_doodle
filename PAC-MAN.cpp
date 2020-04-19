#include<ncurses.h>
#include<vector>
#include<time.h>
using namespace std;


#define Space (0)
#define Wall (1)




enum
{
        Up,
    Le, Nn, Ri,
        Dw,
};

struct Actor
{
    int Speed;
    int X;
    int Y;
    int Cursor;
    int State;
};


vector<vector<int>> Map = 
{
{1,1,1,1,1,1,1,1,1,1,1,1},//0
{1,0,0,0,0,0,0,0,0,0,0,1},//1
{1,0,1,1,0,1,1,1,1,1,0,1},//2
{1,0,1,1,0,0,0,0,0,0,0,1},//3
{1,0,1,1,0,0,0,0,0,0,0,1},//4
{1,0,0,0,0,0,1,1,1,0,1,1},//5
{1,1,0,1,1,0,1,1,0,0,1,1},//6
{1,0,0,1,1,0,1,1,0,0,0,1},//7
{1,1,0,0,0,0,0,0,0,1,1,1},//8
{1,1,0,1,1,0,1,1,0,1,1,1},//9
{1,1,0,1,1,0,1,1,0,0,0,1},//10
{1,1,1,1,1,1,1,1,1,1,1,1},//11
};



WINDOW *win;






#define X_field (12)
#define Y_field (12)

bool Power = true;




int Input(char c,int Cursor,int X_Pos,int Y_Pos)
{
    switch (c)
    {
    case 'w':
        if(Map[Y_Pos - 1][X_Pos] != Wall)
            return Up;
    break;

    case 's':
        if(Map[Y_Pos + 1][X_Pos] != Wall)
            return Dw;
    break;

    case 'a':
        if(Map[Y_Pos][X_Pos - 1] != Wall)
            return Le;
    break;
    
    case 'd':
        if(Map[Y_Pos][X_Pos + 1] != Wall)
            return Ri;
    break;
    
    default:return Cursor;break;
    }

}

void MoveActor(int Cursor,int &X_Pos,int &Y_Pos)
{
    switch (Cursor)
    {
        case Up:
            if(Map[Y_Pos - 1][X_Pos] != Wall)
                Y_Pos--;
        break;
    
        case Dw:
            if(Map[Y_Pos + 1][X_Pos] != Wall)
                Y_Pos++;
        break;

        case Le:
            if(Map[Y_Pos][X_Pos - 1] != Wall)
                X_Pos--;
        break;

        case Ri:
            if(Map[Y_Pos][X_Pos + 1] != Wall)
                X_Pos++;
        break;

        default:
        break;
    }
}

void Disp(int X_Pos,int Y_Pos)
{
    move(0,0);
    for(int y = 0;y < Y_field;++y)
    {
        for(int x = 0;x < X_field;++x)
        {
            if((x == X_Pos)&&(y == Y_Pos))
                addch('O');

            else if(Map[y][x] == Wall)
                addch('X');

            else if(Map[y][x] == Space)
                addch(' ');
        }

        addch('\n');
    }
}




int main()
{
    initscr();
    cbreak();
    noecho();
    char c;
    timeout(200);

    Actor PAC;
    PAC.X = 3;
    PAC.Y = 3;
    PAC.Cursor = Nn;

    
    while (Power)
    {
        mvaddstr(Y_field / 2,X_field / 2 - 3,"PAC-MAN");
        wrefresh(win);
        
        
        if(getch() == 0x1b)
            break;
        
        while((c = getch()) != 0x1b)
        {   

            Disp(PAC.X,PAC.Y);

            wrefresh(win);

            PAC.Cursor = Input(c,PAC.Cursor,PAC.X,PAC.Y);

            MoveActor(PAC.Cursor,PAC.X,PAC.Y);

            
        }
    }
    
    wclear(win);
    wrefresh(win);
    endwin();

}
