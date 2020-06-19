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

const X_FIELD: i32 = 40; //四で割り切れる数
const Y_FIELD: i32 = 16;
const WIN_POINT: u32 = 10; //First to get WIN_POINT is winner

fn main() {
    //Variables
    let mut turn: bool = false; //false (2P's turn)   true(1P's turn)

    let mut pong = Pong {
        x: X_FIELD / 2,
        y: Y_FIELD / 2,
        cursor: Cursor::Le,
    };
    let mut bar1 = Bar {
        x: 1,
        y: Y_FIELD / 2,
        score: 0,
    };
    let mut bar2 = Bar {
        x: X_FIELD - 1,
        y: Y_FIELD / 2,
        score: 0,
    };
    //END

    initscr();
    cbreak();
    noecho();

    //Display Field
    mvprintw(0, 0, "+");
    mvprintw(0, X_FIELD, "+");
    mvprintw(Y_FIELD, 0, "+");
    mvprintw(Y_FIELD, X_FIELD, "+");
    //END

    //First Message
    mvprintw(Y_FIELD / 2, X_FIELD / 2 - 7, "Wellcome 2 Pong");
    refresh();
    getch();
    mvprintw(Y_FIELD / 2, X_FIELD / 2 - 7, "1 Player use A & D");
    mvprintw(Y_FIELD / 2 + 1, X_FIELD / 2 - 7, "2 Player use J & L");
    refresh();
    getch();
    erase();
    //END

    timeout(100);

    //Display Field
    mvprintw(0, 0, "+");
    mvprintw(0, X_FIELD, "+");
    mvprintw(Y_FIELD, 0, "+");
    mvprintw(Y_FIELD, X_FIELD, "+");
    refresh();
    //END

    loop {
        let ch = getch();

        mvprintw(pong.y, pong.x, " "); //Clear Pong(Ovrewrite with whitespace)

        mvprintw(bar1.y - 1, bar1.x, " "); //Clear 1P's Bar
        mvprintw(bar1.y, bar1.x, " ");
        mvprintw(bar1.y + 1, bar1.x, " ");

        mvprintw(bar2.y - 1, bar2.x, " "); //Clear 2P's Bar
        mvprintw(bar2.y, bar2.x, " ");
        mvprintw(bar2.y + 1, bar2.x, " ");

        mvprintw(1, X_FIELD / 2, if turn { "1P" } else { "2P" }); //Display turn Player

        //Display Score
        mvprintw(2, X_FIELD / 4, &bar2.score.to_string());
        mvprintw(2, (X_FIELD / 4) * 3, &bar1.score.to_string());

        pong_cd(&mut pong, &mut bar1, &mut bar2, turn);
        //
        input(ch, &mut bar1, &mut bar2, turn);

        match &mut pong.cursor {
            Cursor::Up => {
                pong.y -= 1;
            }
            Cursor::UL => {
                pong.x -= 1;
                pong.y -= 1;
                turn = true;
            }
            Cursor::Le => {
                pong.x -= 1;
                turn = true;
            }
            Cursor::DL => {
                pong.x -= 1;
                pong.y += 1;
                turn = true;
            }
            Cursor::Dw => {
                pong.y += 1;
            }
            Cursor::DR => {
                pong.x += 1;
                pong.y += 1;
                turn = false;
            }
            Cursor::Ri => {
                pong.x += 1;
                turn = false;
            }
            Cursor::UR => {
                pong.x += 1;
                pong.y -= 1;
                turn = false;
            }
        }

        mvprintw(pong.y, pong.x, "o"); //Display PONG

        mvprintw(bar1.y - 1, bar1.x, "|"); //Display 1P Bar
        mvprintw(bar1.y, bar1.x, "|");
        mvprintw(bar1.y + 1, bar1.x, "|");

        mvprintw(bar2.y - 1, bar2.x, "|"); //Display 2P Bar
        mvprintw(bar2.y, bar2.x, "|");
        mvprintw(bar2.y + 1, bar2.x, "|");

        refresh();

        //27 mean escape
        if ch == 27 {
            break;
        }
        if bar2.score == WIN_POINT || bar1.score == WIN_POINT {
            erase();
            timeout(-1);

            mvprintw(Y_FIELD / 2 - 1, X_FIELD / 2 - 3, {
                if bar1.score == WIN_POINT {
                    "1P WIN"
                } else {
                    "2P WIN"
                }
            });
            mvprintw(Y_FIELD / 2 + 1, X_FIELD / 2 - 4, "Congrats");

            getch();
            break ();
        }
    }

    refresh();
    getch();
    endwin();
}
fn input(ch: i32, bar1: &mut Bar, bar2: &mut Bar, turn: bool) {
    let ch = convert(ch); // i32 --> char

    if turn {
        match ch {
            'a' => {
                if bar1.y + 1 < Y_FIELD - 1 {
                    bar1.y += 1;
                }
            }
            'd' => {
                if bar1.y - 1 > 1 {
                    bar1.y -= 1;
                }
            }
            _ => (),
        }
    } else {
        match ch {
            'j' => {
                if bar2.y + 1 < Y_FIELD - 1 {
                    bar2.y += 1;
                }
            }
            'l' => {
                if bar2.y - 1 > 1 {
                    bar2.y -= 1;
                }
            }
            _ => (),
        }
    }
}
fn pong_cd(pong: &mut Pong, bar1: &mut Bar, bar2: &mut Bar, turn: bool) {
    //Left Wall
    if pong.x <= 1 {
        bar1.score += 1;
        pong.x = X_FIELD / 2;
        pong.y = Y_FIELD / 2;
        pong.cursor = {
            if turn {
                Cursor::Le
            } else {
                Cursor::Ri
            }
        };
    }

    //Upper Wall
    if pong.y <= 1 {
        match pong.cursor {
            Cursor::UR => {
                pong.cursor = Cursor::DR;
            }
            Cursor::Up => {
                pong.cursor = Cursor::Dw;
            }
            Cursor::UL => {
                pong.cursor = Cursor::DL;
            }
            _ => (),
        }
    }

    //Right Wall
    if pong.x >= X_FIELD - 1 {
        bar2.score += 1;
        pong.x = X_FIELD / 2;
        pong.y = Y_FIELD / 2;
        pong.cursor = {
            if turn {
                Cursor::Le
            } else {
                Cursor::Ri
            }
        };
    }

    //Downer Wall
    if pong.y >= Y_FIELD - 1 {
        match pong.cursor {
            Cursor::DR => {
                pong.cursor = Cursor::UR;
            }
            Cursor::Dw => {
                pong.cursor = Cursor::Up;
            }
            Cursor::DL => {
                pong.cursor = Cursor::UL;
            }
            _ => (),
        }
    }

    // 1Bar Upper
    if (pong.y == bar1.y + 1) && (pong.x == bar1.x + 1) {
        match pong.cursor {
            Cursor::DL => {
                pong.cursor = Cursor::Ri;
            }
            Cursor::Le => {
                pong.cursor = Cursor::DR;
            }
            Cursor::UL => {
                pong.cursor = Cursor::DR;
            }
            _ => (),
        }
    }

    //1Bar Middle
    if (pong.y == bar1.y) && (pong.x == bar1.x + 1) {
        match pong.cursor {
            Cursor::DL => pong.cursor = Cursor::DR,
            Cursor::Le => pong.cursor = Cursor::Ri,
            Cursor::UL => pong.cursor = Cursor::UR,
            _ => (),
        }
    }

    //1Bar Downner
    if (pong.y == bar1.y - 1) && (pong.x == bar1.x + 1) {
        match pong.cursor {
            Cursor::DL => pong.cursor = Cursor::UR,
            Cursor::Le => pong.cursor = Cursor::UR,
            Cursor::UL => pong.cursor = Cursor::Ri,
            _ => (),
        }
    }

    //2Bar Upper
    if (pong.y == bar2.y + 1) && (pong.x == bar2.x - 1) {
        match pong.cursor {
            Cursor::DR => pong.cursor = Cursor::Le,
            Cursor::Ri => pong.cursor = Cursor::DL,
            Cursor::UR => pong.cursor = Cursor::DL,
            _ => (),
        }
    }

    //2Bar Middle
    if (pong.y == bar2.y) && (pong.x == bar2.x - 1) {
        match pong.cursor {
            Cursor::DR => pong.cursor = Cursor::DL,
            Cursor::Ri => pong.cursor = Cursor::Le,
            Cursor::UR => pong.cursor = Cursor::UL,
            _ => (),
        }
    }

    //2Bar Downner
    if (pong.y == bar2.y - 1) && (pong.x == bar2.x - 1) {
        match pong.cursor {
            Cursor::DR => {
                pong.cursor = Cursor::UL;
            }
            Cursor::Ri => {
                pong.cursor = Cursor::UL;
            }
            Cursor::UR => {
                pong.cursor = Cursor::Le;
            }
            _ => (),
        }
    }
}

fn convert(ch: i32) -> char {
    match ch {
        97 => 'a',
        100 => 'd',
        106 => 'j',
        108 => 'l',
        _ => ' ',
    }
}
