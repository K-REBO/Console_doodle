/*
Name:Dino

Happy Birthday! Muramatsu!

I know you like Dinosaur & I can't hand a gift.
So I write it.

4/18/2020 0:13 - 
Authour:Bido

*/

#include<ncurses.h>

#define X_field (50)
#define Y_field (20)

/*
void DinoCD()//Collision Detection　of DINO
{

}
*/


int main()
{
    WINDOW *win;
    char c;


    initscr();
    noecho();
    cbreak();
    timeout(-1);

    //Field
        mvaddch(0,0,'+');
        mvaddch(0,X_field,'+');
        mvaddch(Y_field,0,'+');
        mvaddch(Y_field,X_field,'+');
        wrefresh(win);

    //"Wellcome to DINO"
        mvaddstr(Y_field / 2,X_field / 2 - 8,"Wellcome to DINO");
        wrefresh(win);
        getch();
    
    
    //"Use Space key ...."
        mvaddstr(Y_field / 2,X_field / 2 - 8,"Use SPACE 2 JAMP");
        wrefresh(win);
        getch();
    
    
    //"Chose charactor"
        mvaddstr(Y_field / 2,X_field / 2 - 8,"Chose charactor!");
        wrefresh(win);
        getch();
    
    
    //"Press Space to start"
        mvaddstr(Y_field / 2,X_field / 2 - 9,"Press KEY to START");
        wrefresh(win);
        getch();
        mvaddstr(Y_field / 2,X_field / 2 - 9,"                  ");//Clear 
    
    timeout(100);
    
    //Display Ground
        move(Y_field - 2,0);
        for(int x = 0;x < X_field;++x)
        {
            addch('=');
        }

    while ((c = getch()) != 0x1b)
    {
        


        wrefresh(win);

    }
    

    wclear(win);

    wrefresh(win);
    endwin();


}
