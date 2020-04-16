#include<ncurses.h>
#include<unistd.h>
using namespace std;

#define  X_field (40)//四で割れる
#define  Y_field (16)

int  Winner = 0;//0 (In Game)   1 (1P Winner)   2(2P Winner)
bool Turn = false;// false (2P's turn)    ture (1P's turn)

int a = 0;

int WinPoint = 10;//First to get WinPoint is Winner

int Score_1 = 0;
int Score_2 = 0;
char Score_1_char[100];
char Score_2_char[100]; 

int X_Pong = X_field / 2,Y_Pong = Y_field / 2;
int Pong_Cursor = 2;


int X1Bar = 1,Y1Bar = Y_field / 2;
int X2Bar = X_field - 1,Y2Bar = Y_field / 2;


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
    if(Turn)
        switch (c)
        {
            case 'a':
                if(Y1Bar + 1 < Y_field  - 1)
                    Y1Bar++;break;
            case 'd':
                if(Y1Bar - 1 > 1)
                    Y1Bar--;break;
            default:break;
        }
    
    else
        switch (c)
        {
            case 'j':
                if(Y2Bar + 1 < Y_field - 1)
                    Y2Bar++;break;
            case 'l':
                if(Y2Bar - 1 > 1)
                    Y2Bar--;break;
            default:break;
        }
    
}

void PongCD()//Collid Detection Pong and wall and Bar
{
    //Left Wall
    if(X_Pong <= 1)//1P win
    {
        Score_1++;
        X_Pong = X_field / 2;
        Y_Pong = Y_field / 2;
        Pong_Cursor = (Turn?2:6);
    }
    //Upper Wall
    else if(Y_Pong <= 1)
        switch(Pong_Cursor)
        {
            case UR:Pong_Cursor = DR;break;
            case Up:Pong_Cursor = Dw;break;
            case UL:Pong_Cursor = DL;break;
            default:                 break;
        }
    //Right Wall
    else if(X_Pong >= X_field - 1)
    {
        Score_2++;
        X_Pong = X_field / 2;
        Y_Pong = Y_field / 2;
        Pong_Cursor = (Turn?2:6);
    }
    //Downer Wall
    else if(Y_Pong >= Y_field - 1)
        switch(Pong_Cursor)
        {
            case DR:Pong_Cursor = UR;break;
            case Dw:Pong_Cursor = Up;break;
            case DL:Pong_Cursor = UL;break;
            default:                 break;
        }
    // 1Bar Upper
    else if((Y_Pong == Y1Bar + 1)&&(X_Pong == X1Bar + 1))
        switch(Pong_Cursor)
        {
            case DL:Pong_Cursor = UR;break;
            case Le:Pong_Cursor = UR;break;
            case UL:Pong_Cursor = Ri;break;
            default:                 break;
        }
    // 1Bar Middle
    else if((Y_Pong == Y1Bar)&&(X_Pong == X1Bar + 1))
        switch (Pong_Cursor)
        {
            case DL:Pong_Cursor = DR;break;
            case Le:Pong_Cursor = Ri;break;
            case UL:Pong_Cursor = UR;break;
            default:                 break;
        }
    // 1Bar Downer
    else if((Y_Pong == Y1Bar - 1)&&(X_Pong == X1Bar + 1))
        switch (Pong_Cursor)
        {
            case DL:Pong_Cursor = Ri;break;
            case Le:Pong_Cursor = DR;break;
            case UL:Pong_Cursor = DR;break;
            default:                 break;
        }
    // 2Bar Upper
    else if((Y_Pong == Y2Bar + 1)&&(X_Pong == X2Bar - 1))
        switch (Pong_Cursor)
        {
            case DR:Pong_Cursor = UL;break;
            case Ri:Pong_Cursor = UL;break;
            case UR:Pong_Cursor = Le;break;
            default:                 break;
        }
    // 2Bar Middle
    else if((Y_Pong == Y2Bar)&&(X_Pong == X2Bar - 1))
        switch (Pong_Cursor)
        {
            case DR:Pong_Cursor = DL;break;
            case Ri:Pong_Cursor = Le;break;
            case UR:Pong_Cursor = UL;break;
            default:                 break;
        }
    // 2Bar Downer
    else if((Y_Pong == Y2Bar - 1)&&(X_Pong == X2Bar - 1))
        switch (Pong_Cursor)
        {
            case DR:Pong_Cursor = Le;break;
            case Ri:Pong_Cursor = DL;break;
            case UR:Pong_Cursor = DL;break;
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
    
    
    //First Message
        mvaddstr(Y_field / 2,3,"Wellcome 2 Pong ");
        wrefresh(win);
        getch();
        erase();
        mvaddstr(Y_field / 2,3,"1 Player use A & D");
        mvaddstr(Y_field / 2 + 1,3,"2 Player use J & L");
        wrefresh(win);
        getch();
        erase();
    //END
    timeout(100);
    //Display Field
        mvaddch(0,0,'+');
        mvaddch(0,X_field,'+');
        mvaddch(Y_field,0,'+');
        mvaddch(Y_field,X_field,'+');
    //END

    wrefresh(win);

    while((c = getch()) != 0x1b)
    {

        sprintf(Score_1_char,"%d",Score_1);//Trancelate Score int to char
        sprintf(Score_2_char,"%d",Score_2);

        mvaddch(Y_Pong,X_Pong,' ');//Clear Pong

        mvaddch(Y1Bar - 1,X1Bar,' ');//Clear 1P Bar
        mvaddch(Y1Bar    ,X1Bar,' ');
        mvaddch(Y1Bar + 1,X1Bar,' ');

        mvaddch(Y2Bar - 1,X2Bar,' ');//Clear 2P Bar
        mvaddch(Y2Bar    ,X2Bar,' ');
        mvaddch(Y2Bar + 1,X2Bar,' ');

        mvaddstr(1,X_field / 2 - 1,(Turn?"1P":"2P"));//Display Now Player

        mvaddstr(2,X_field / 4,Score_2_char);//Display Score
        mvaddstr(2,(X_field / 4)*3,Score_1_char);




        PongCD();
        Input(c);

        switch (Pong_Cursor)
        {
            case Up:         Y_Pong--;             break;
            case UL:X_Pong--;Y_Pong--;Turn = true; break;
            case Le:X_Pong--;         Turn = true; break;
            case DL:X_Pong--;Y_Pong++;Turn = true; break;
            case Dw:         Y_Pong++;             break;
            case DR:X_Pong++;Y_Pong++;Turn = false;break;
            case Ri:X_Pong++;         Turn = false;break;
            case UR:X_Pong++;Y_Pong--;Turn = false;break;
            default:                               break;
        }

        mvaddch(Y_Pong,X_Pong,'o');//Display Pong

        mvaddch(Y1Bar - 1,X1Bar,'|');//Display 1P Bar
        mvaddch(Y1Bar    ,X1Bar,'|');
        mvaddch(Y1Bar + 1,X1Bar,'|');

        mvaddch(Y2Bar - 1,X2Bar,'|');//Display 2P Bar
        mvaddch(Y2Bar    ,X2Bar,'|');
        mvaddch(Y2Bar + 1,X2Bar,'|');

        
        wrefresh(win);

        if((Score_2 == WinPoint)||(Score_1 == WinPoint))
        {
            
            erase();
            timeout(-1);
            
            if(Score_1 = WinPoint)
                Winner = 1;
            else 
                Winner = 2;

            mvaddstr(Y_field / 2,3,(Winner == 1 ? "1P WIN \n Congrats" : "2P WIN \n Congrats"));
            getch();
            break;
        }   





    }

    wclear(win);
    wrefresh(win);
    endwin();
    
}
