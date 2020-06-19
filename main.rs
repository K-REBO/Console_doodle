extern crate ncurses;
use ncurses::*;
use std::char;

//
enum Cursor {
    Up, //UP
    UL, //UPper Left         0
    Le, //Left            1  |  7
    DL, //Downer Left      \ | /
    Dw, //Down          2----+----6
    DR, //Downer Right     / | \//
    Ri, //Right           3  |  5
    UR, //Upper Right        4
}

struct Bar {
    x: i32,
    y: i32,
    score: u32,
}
struct Pong {
    x: i32,
    y: i32,
    cursor: Cursor,
}

const X_field: i32 = 40; //四で割り切れる数
const Y_field: i32 = 16;
const WinPoint: u32 = 10; //First to get WinPoint is Winner

fn main() {
    //Variables
    let mut Winner: u8 = 0; //0 (In Game)   1 (1P Winner)   2(2P Winner)
    let mut Turn: bool = false; //false (2P's Turn)   true(1P's Turn)

    let mut pong = Pong {
        x: X_field / 2,
        y: Y_field / 2,
        cursor: Cursor::Le,
    };
    let mut Bar1 = Bar {
        x: 1,
        y: Y_field / 2,
        score: 0,
    };
    let mut Bar2 = Bar {
        x: X_field - 1,
        y: Y_field / 2,
        score: 0,
    };
    //END

    initscr();
    cbreak();
    noecho();

    //Display Field
    mvprintw(0, 0, "+");
    mvprintw(0, X_field, "+");
    mvprintw(Y_field, 0, "+");
    mvprintw(Y_field, X_field, "+");
    //END

    //First Message
    mvprintw(Y_field / 2, X_field / 2 - 7, "Wellcome 2 Pong");
    refresh();
    getch();
    mvprintw(Y_field / 2, X_field / 2 - 7, "1 Player use A & D");
    mvprintw(Y_field / 2 + 1, X_field / 2 - 7, "2 Player use J & L");
    refresh();
    getch();
    erase();
    //END

    timeout(100);

    //Display Field
    mvprintw(0, 0, "+");
    mvprintw(0, X_field, "+");
    mvprintw(Y_field, 0, "+");
    mvprintw(Y_field, X_field, "+");
    refresh();
    //END

    let mut stri: &str;

    loop {

        let mut ch = getch();

        mvprintw(pong.y, pong.x, " "); //Clear Pong(Ovrewrite with whitespace)

        mvprintw(Bar1.y - 1, Bar1.x, " "); //Clear 1P's Bar
        mvprintw(Bar1.y, Bar1.x, " ");
        mvprintw(Bar1.y + 1, Bar1.x, " ");

        mvprintw(Bar2.y - 1, Bar2.x, " "); //Clear 2P's Bar
        mvprintw(Bar2.y, Bar2.x, " ");
        mvprintw(Bar2.y + 1, Bar2.x, " ");

        mvprintw(1, X_field / 2, if Turn { "1P" } else { "2P" }); //Display Turn Player

        //Display Score
        mvprintw(2, X_field / 4, &Bar2.score.to_string());
        mvprintw(2, (X_field / 4) * 3, &Bar1.score.to_string());

        
        pongCD(&mut pong,&mut Bar1,&mut Bar2,Turn);
        // 
        input(ch,&mut Bar1,&mut Bar2,Turn);




        match &mut pong.cursor {
            Cursor::Up => {            pong.y -= 1;             },
            Cursor::UL => {pong.x -= 1;pong.y -= 1;Turn = true; },
            Cursor::Le => {pong.x -= 1;            Turn = true; },
            Cursor::DL => {pong.x -= 1;pong.y += 1;Turn = true; },
            Cursor::Dw => {            pong.y += 1;             },
            Cursor::DR => {pong.x += 1;pong.y += 1;Turn = false;},
            Cursor::Ri => {pong.x += 1;            Turn = false;},
            Cursor::UR => {pong.x += 1;pong.y -= 1;Turn = false;},
        }

        mvprintw(pong.y,pong.x,"o");//Display PONG

        mvprintw(Bar1.y - 1,Bar1.x,"|");//Display 1P Bar
        mvprintw(Bar1.y    ,Bar1.x,"|");
        mvprintw(Bar1.y + 1,Bar1.x,"|");

        mvprintw(Bar2.y - 1,Bar2.x,"|");//Display 2P Bar
        mvprintw(Bar2.y    ,Bar2.x,"|");
        mvprintw(Bar2.y + 1,Bar2.x,"|");

        refresh();


        //27 mean escape
        if ch == 27 {
            break;
        }
        if Bar2.score == WinPoint || Bar1.score == WinPoint {
            erase();
            timeout(-1);

            if Bar1.score == WinPoint {
                Winner = 1;
            }
            else {
                Winner = 2;
            }

            mvprintw(Y_field / 2,3,{
                if Winner == 1 {
                    "1P WIN \n Congrats"
                }
                else {
                    "2P WIN \n Congrats"
                }
            });

            getch();
            break();
        }



    }

    
    refresh();
    getch();
    endwin();
}
fn input(ch: i32,Bar1: &mut Bar ,Bar2: &mut Bar,Turn: bool) {
    let ch = convert(ch);// i32 --> char 

    if Turn {
        match ch {
            'a' => {
                if Bar1.y + 1 < Y_field - 1 {
                    Bar1.y += 1;
                }
            },
            'd' => {
                if Bar1.y -1 > 1 {
                    Bar1.y -= 1;
                }
            },
            _ => (),
        }
    }

    else {
        match ch {
            'j' => {
                if Bar2.y + 1 < Y_field -1 {
                    Bar2.y += 1;
                }
            },
            'l' => {
                if Bar2.y -1 > 1 {
                    Bar2.y -= 1;
                }
            },
            _ => (),
        }
    }


}
fn pongCD(pong:&mut Pong,Bar1:&mut Bar,Bar2:&mut Bar,Turn: bool) {
    
    //Left Wall
    if pong.x <= 1 {
        Bar1.score += 1;
        pong.x = X_field / 2;
        pong.y = Y_field / 2;
        pong.cursor = {
            if Turn {
                Cursor::Le
            }
            else {
                Cursor::Ri
            }
        };
    }

    //Upper Wall
     if pong.y <= 1 {
        match pong.cursor {
            Cursor::UR => {pong.cursor = Cursor::DR;},
            Cursor::Up => {pong.cursor = Cursor::Dw;},
            Cursor::UL => {pong.cursor = Cursor::DL;},
            _          => (),
        }
    }

    //Right Wall
     if pong.x >= X_field - 1 {
        Bar2.score += 1;
        pong.x = X_field / 2;
        pong.y = Y_field / 2;
        pong.cursor = {
            if Turn {
                Cursor::Le
            }
            else {
                Cursor::Ri
            }
        };
    }

    //Downer Wall
     if pong.y >= Y_field -1 {
        match pong.cursor {
            Cursor::DR => {pong.cursor = Cursor::UR;},
            Cursor::Dw => {pong.cursor = Cursor::Up;},
            Cursor::DL => {pong.cursor = Cursor::UL;},
            _          => (),
        }
    }

    // 1Bar Upper
     if (pong.y == Bar1.y + 1)&&(pong.x == Bar1.x + 1) {
        match pong.cursor {
            Cursor::DL => {pong.cursor = Cursor::Ri;},
            Cursor::Le => {pong.cursor = Cursor::DR;},
            Cursor::UL => {pong.cursor = Cursor::DR;},
            _          => (),
        }
    }

    //1Bar Middle
     if (pong.y == Bar1.y)&&(pong.x == Bar1.x + 1){
        match pong.cursor {
            Cursor::DL => pong.cursor = Cursor::DR,
            Cursor::Le => pong.cursor = Cursor::Ri,
            Cursor::UL => pong.cursor = Cursor::UR,
            _          => (),
        }
    }
    
    //1Bar Downner
     if (pong.y == Bar1.y - 1)&&(pong.x == Bar1.x + 1) {
        match pong.cursor {
            Cursor::DL => pong.cursor = Cursor::UR,
            Cursor::Le => pong.cursor = Cursor::UR,
            Cursor::UL => pong.cursor = Cursor::Ri,
            _          => (),
        }
    }

    //2Bar Upper 
     if (pong.y == Bar2.y + 1)&&(pong.x == Bar2.x -1){
        match pong.cursor {
            Cursor::DR => pong.cursor = Cursor::Le,
            Cursor::Ri => {pong.cursor = Cursor::DL},
            Cursor::UR => pong.cursor = Cursor::DL,
            _          => (),
        }
    }

    //2Bar Middle
     if (pong.y == Bar2.y)&&(pong.x == Bar2.x - 1) {
        match pong.cursor {
            Cursor::DR => pong.cursor = Cursor::DL,
            Cursor::Ri => pong.cursor = Cursor::Le,
            Cursor::UR => pong.cursor = Cursor::UL,
            _          => (),
        }
    }

    //2Bar Downner
     if (pong.y == Bar2.y - 1)&&(pong.x == Bar2.x - 1)
    {
        match pong.cursor {
            Cursor::DR => {pong.cursor = Cursor::UL;},
            Cursor::Ri => {pong.cursor = Cursor::UL;},
            Cursor::UR => {pong.cursor = Cursor::Le;},
            _          => (),
        }
    }




}

fn convert(ch:i32) -> char {
    match ch {
        97  => 'a',
        100 => 'd',
        106 => 'j',
        108 => 'l',
        _   => ' ',
    }
}
