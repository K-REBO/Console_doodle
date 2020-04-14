//+   1    +
//          
//          
//    o     
//          
//0        2
//          
//    345     
//    ===   
//+        +
#include<vector>
#include<ncurses.h>
#include<unistd.h>
using namespace std;


#define X_field (16)
#define Y_field (10)

bool Game = false;//true (Game Over)  false (Game)

int X_Pong = X_field / 2,Y_Pong = Y_field / 2;
int X_Bar = X_field / 2,Y_Bar = Y_field - 2;
int Pong_Cursor = 4;
int Pong_state = 0;

enum
{
    Up,//UP            
    UL,//UPper Left         0
    Le,//Left            1  |  7
    DL,//Downer Left      \ | /
    Dw,//Down          2----+----6
    DR,//Downer Right     / | \//
    Ri,//Right           3  |  5
    UR,//Upper Right        4
};


void Input(char c)
{
    switch (c)
    {
    case 'a':
        if(X_Bar > 2)
            X_Bar--;
        break;
    
    case 'd':
        if(X_Bar < X_field - 2)
            X_Bar++;
        break;

    default:
        break;
    }
}

void Test(char x)
{
    switch(x)
    {
        case 'W':Y_Pong--;break;
        case 'A':X_Pong--;break;
        case 'D':X_Pong++;break;
        case 'S':Y_Pong++;break;
        default:          break;
    }
}

void PongCD()//Collid Detection Pong and Wall and Bar
{
    //Left Wall
    if(X_Pong == 1)
        switch (Pong_Cursor)
        {
        case DL:Pong_Cursor = UR;break;
        case Le:Pong_Cursor = Ri;break;
        case UL:Pong_Cursor = DR;break;
        default:                 break;
        }

    //Upper Wall
    else if(Y_Pong == 1)
        switch(Pong_Cursor)
        {
            case UR:Pong_Cursor = DR;break;
            case Up:Pong_Cursor = Dw;break;
            case UL:Pong_Cursor = DL;break;
            default:                 break;
        }
    //Downer Wall
    else if(Y_Pong == Y_field - 1)
        Game = true;

    //Right Wall
    else if(X_Pong == X_field - 1)
        switch(Pong_Cursor)
        {
            case DR:Pong_Cursor = UL;break;
            case Ri:Pong_Cursor = Le;break;
            case UR:Pong_Cursor = DL;break;
            default:                 break;
        }


    //Left Bar
    else if((X_Pong == X_Bar - 1)&&(Y_Pong == Y_Bar - 1))
        switch (Pong_Cursor)
        {
        case DR:Pong_Cursor = UL;break;
        case Dw:Pong_Cursor = UL;break;
        case DL:Pong_Cursor = Up;break;
        default:                 break;
        }

    //Middle Bar
    else if((X_Pong == X_Bar)&&(Y_Pong == Y_Bar - 1))
        switch (Pong_Cursor)
        {
        case DR:Pong_Cursor = UR;break;
        case Dw:Pong_Cursor = Up;break;
        case DL:Pong_Cursor = UL;break;
        default:                 break;
        }

    //Right Bar
    else if((X_Pong == X_Bar + 1)&&(Y_Pong == Y_Bar - 1))
        switch(Pong_Cursor)
        {
            case DR:Pong_Cursor = Up;break;
            case Dw:Pong_Cursor = UR;break;
            case DL:Pong_Cursor = UR;break;
            default:                 break;
        }
    
    
}




int main()
{
    WINDOW *win;
    char c;
    initscr();
    noecho();
    cbreak();
    timeout(100);
    
    //Display FIELD
        mvaddch(0,0,'+');
        mvaddch(0,X_field,'+');
        mvaddch(Y_field,0,'+');
        mvaddch(Y_field,X_field,'+');
    //END

    wrefresh(win);
    while((c = getch()) != 0x1b)
    {   
        
        mvaddch(Y_Pong,X_Pong,' '); //Clear Pong
        mvaddch(Y_Bar,X_Bar - 1,' ');//Clear Bar
        mvaddch(Y_Bar,X_Bar    ,' ');
        mvaddch(Y_Bar,X_Bar + 1,' ');
        

        Test(c);
        PongCD();
        Input(c);
        
        
        switch (Pong_Cursor)
        {
            case Up:         Y_Pong--;break;
            case UL:X_Pong--;Y_Pong--;break;
            case Le:X_Pong--;         break;
            case DL:X_Pong--;Y_Pong++;break;
            case Dw:         Y_Pong++;break;
            case DR:X_Pong++;Y_Pong++;break;
            case Ri:X_Pong++;         break;
            case UR:X_Pong++;Y_Pong--;break;

            default:
                break;
        }




        mvaddch(Y_Pong,X_Pong  ,'o');//Display Pong
        mvaddch(Y_Bar,X_Bar - 1,'=');//Display Bar
        mvaddch(Y_Bar,X_Bar    ,'=');
        mvaddch(Y_Bar,X_Bar + 1,'=');

        
        wrefresh(win);
        if(Game)
        {
            erase();
            mvaddch(0,0,'+');
            mvaddch(0,X_field,'+');
            mvaddch(Y_field,0,'+');
            mvaddch(Y_field,X_field,'+');
            mvaddstr(Y_field / 2,X_field / 2,"Game Over");
            getch();
            break;
        }
    }
    wclear(win);
    wrefresh(win);
    endwin();

}
