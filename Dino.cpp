#include<ncurses.h>
#include<vector>
using namespace std;




WINDOW *win;
vector<vector<int>> MAP_DINO = 
{
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},//0
    {0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},//1
    {0,0,0,0,0,0,0,1,0,1,1,1,1,0,0},//2
    {0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},//3
    {0,0,0,0,0,0,0,1,1,1,1,1,0,0,0},//4
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},//5
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0},//6
    {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},//7
    {1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},//8
    {1,1,0,1,1,1,1,1,1,1,0,0,0,0,0},//9
    {1,1,0,1,1,1,1,0,0,1,0,0,0,0,0},//10
    {0,1,0,1,1,1,1,0,0,0,0,0,0,0,0},//11
    {0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},//12
    {0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},//13
    {0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},//14
    {0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},//15
    {0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},//16
    {0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},//17
};

struct Actor
{
    int X;
    int Y;
    int State;

};




const int X_Field = 15 * 5;
const int Y_Field = 18 * 3;

int Frame = 0;




//Variables
    void Display(int DINO_Pos_X,int DINO_Pos_Y)
    {
       int VarX = DINO_Pos_X;
        //Display DINO
            move(DINO_Pos_Y,DINO_Pos_X);//First Place to addch()
            for(int y = 0;y < 18;++y)
            {   for(int x = 0;x < 15;++x)
                {
                    if(MAP_DINO[y][x] == 1)
                        mvaddch(DINO_Pos_Y,DINO_Pos_X,'=');
                    else
                        mvaddch(DINO_Pos_Y,DINO_Pos_X,' ');
    
                DINO_Pos_X++;
                }
    
                DINO_Pos_X = VarX;
    
                DINO_Pos_Y++;
            }    



        //Display Field
            mvaddch(0,0,'+');
            mvaddch(0,X_Field,'+');
            mvaddch(Y_Field,0,'+');
            mvaddch(Y_Field,X_Field,'+');
    }




    void Input(char c,int &Y_Pos)
    {
        if((c == ' ')&&(Frame == 0))
        {
            Y_Pos = Y_Pos - 1;Frame++;
        }

        switch (Frame)
        {
            
            case 1:Y_Pos = Y_Pos - 1;Frame++;  break;//Jump
            case 2:Y_Pos = Y_Pos - 2;Frame++;  break;//Jump
            case 3:Y_Pos = Y_Pos - 4;Frame++;  break;//Jump
            case 4:Y_Pos = Y_Pos - 8;Frame++;  break;//Jump

            case 5:Y_Pos = Y_Pos + 8;Frame++;  break;//Fall
            case 6:Y_Pos = Y_Pos + 4;Frame++;  break;//Fall
            case 7:Y_Pos = Y_Pos + 2;Frame++;  break;//Fall
            case 8:Y_Pos = Y_Pos + 1;Frame++;  break;//Fall
            case 9:Y_Pos = Y_Pos + 1;Frame = 0;break;//Fall
            default:                           break;
        }
        
        
    }
    





    void CD()
    {

    }
//END









int main()
{
    initscr();
    cbreak();
    noecho();
    char c;
    

    Actor DINO;
    DINO.X = X_Field / 4;
    DINO.Y = (Y_Field / 3) * 2;

    timeout(70);

    Display(DINO.X,DINO.Y);
    while((c = getch()) != 0x1b)
    {   
        erase();//Clear Display

        Input(c,DINO.Y);//input c && change DINO.X and DINO.Y

        Display(DINO.X,DINO.Y);

        

        wrefresh(win);
    }

    wclear(win);
    wrefresh(win);
    endwin();
}
