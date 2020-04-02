#include<iostream>
#include<iomanip>
#include<vector>
#include<conio.h>
#define Width (9)
#define Height (9)
#define H_Bomb (9)
#define P_Flag (10)
#define P_OpEd (11)
#define P_NoOp (-1)

int X_cursor = 0, Y_cursor = 0;
using namespace std;
const int b = H_Bomb;
int Op_Count = 0;
int H_Map_Type;
vector<vector<int>> H_Map = {
{1,H_Bomb,2,0,0,0,0,1,H_Bomb},
{1,1,2,H_Bomb,1,0,2,3,2},
{0,0,1,1,1,1,H_Bomb,H_Bomb,1},
{1,1,1,1,1,2,2,2,1},
{1,H_Bomb,1,1,H_Bomb,1,0,0,0},
{1,1,1,1,1,2,1,1,0},
{1,2,2,1,0,1,H_Bomb,1,0},
{1,H_Bomb,H_Bomb,1,0,1,1,1,0},
{1,2,2,1,0,0,0,0,0}
};
vector<vector<int>> H_Map_1 = {
{1,1,1,0,1,2,2,2,0},
{1,b,2,1,2,b,b,2,1},
{1,1,2,b,1,1,3,b,2},
{1,1,1,1,1,0,1,1,1},
{b,1,0,0,1,1,1,0,0},
{1,2,1,1,1,b,1,0,0},
{0,1,b,1,1,1,1,1,1},
{1,2,1,1,0,0,0,1,b},
{b,1,0,0,0,0,0,1,1}
};
vector<vector<int>> H_Map_2 = {
{1,1,1,1,2,2,2,1,0}, //0
{1,b,1,1,b,b,b,1,0}, //1
{1,2,2,1,2,2,2,1,0}, //2
{1,2,b,1,0,0,0,0,0}, //3
{1,b,2,1,1,1,1,0,0}, //4
{1,1,1,1,2,b,1,0,0}, //5
{1,1,1,1,b,2,1,0,0}, //6
{1,b,1,1,1,1,0,1,1}, //7
{1,1,1,0,0,0,0,1,b}, //8
};
vector<vector<int>> H_Map_3 = {
	{1,2,b,1,0,0,1,1,1},//0
	{1,b,2,1,0,0,1,b,1},//1
	{1,1,2,2,3,2,2,1,1},//2
	{0,0,1,b,b,b,1,1,1},//3
	{0,0,1,2,3,2,1,1,b},//4
	{0,0,0,1,1,1,0,1,1},//5
	{1,1,1,1,b,1,0,0,1},//6
	{1,b,1,1,1,1,0,1,1},//7
	{1,1,1,0,0,0,0,1,b},//8
};
vector<vector<int>> H_Map_4 = {
	{0,0,0,0,0,0,0,0,0},
	{0,1,2,3,2,1,0,0,0},
	{0,2,b,b,b,2,0,0,0},
	{0,3,b,8,b,3,0,0,0},
	{0,2,b,b,b,2,0,0,0},
	{0,1,2,3,2,1,0,0,0},
	{0,0,0,1,1,1,0,0,0},
	{0,0,0,1,1,1,0,0,0},
};
vector<vector<int>> H_Map_5 = {
	{b,1,0,0,0,0,1,1,1},
	{1,1,0,0,1,1,2,b,1},
	{0,0,1,1,2,b,2,1,1},
	{0,0,1,b,3,2,1,0,0},
	{0,0,1,2,1,2,b,1,0},
	{0,1,1,2,1,2,b,1,0},
	{1,2,b,1,0,1,1,1,0},
	{b,2,1,2,1,1,0,1,1},
	{1,1,0,1,b,1,0,1,b},
};


//Think Yourself
vector<vector<int>> P_Map = {
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,},
	{P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,P_NoOp,}
};
bool Game = false;



int main(void) {

	printf("Wellcome 2 MineSweeper");
	_getch();
	system("cls");
	printf("Player Use WASD\n& F 2 put Flag\n& Space 2 open");
	_getch();
	system("cls");
	printf("Massage 2 Developer\n\"NOT 4 PLAYER\"");
	_getch();
	system("cls");
	printf("Please ENTER Map_Coad");
	int a;
	cin >> a;
	switch (a) {
	case 0:break;
	case 1:H_Map = H_Map_1; H_Map_Type = 1; break;
	case 2:H_Map = H_Map_2; H_Map_Type = 2; break;
	case 3:H_Map = H_Map_3; H_Map_Type = 3; break;
	case 4:H_Map = H_Map_4; H_Map_Type = 4; break;
	case 5:H_Map = H_Map_5; H_Map_Type = 5; break;
	}


	while (!Game) {
		system("cls");
		for (int x = 0; x < Width; ++x) {
			for (int y = 0; y < Height; ++y) {
				if ((X_cursor == x) && (Y_cursor == y)) cout << "◇";
				else switch (P_Map.at(x).at(y)) {
				case P_Flag:cout << "\x1b[31m旗\x1b[37m"; break;
				case P_NoOp:cout << "□"; break;
				case P_OpEd:cout << setw(2) << H_Map.at(x).at(y); break;
				}
			}
			cout << "\n";
		}
		cout << X_cursor << Y_cursor << "  H_Map_Type:" << H_Map_Type;
		cout << flush;
		switch (_getch()) {
		case'w':if (X_cursor > 0) { X_cursor--; }break;
		case's':if (X_cursor < Width - 1) { X_cursor++; }break;
		case'a':if (Y_cursor > 0) { Y_cursor--; }break;
		case'd':if (Y_cursor < Height - 1) { Y_cursor++; }break;
		case'f':switch (P_Map.at(X_cursor).at(Y_cursor))
		{
		case P_Flag:P_Map.at(X_cursor).at(Y_cursor) = P_NoOp; break;
		case P_OpEd:break;
		case P_NoOp:P_Map.at(X_cursor).at(Y_cursor) = P_Flag; break;
		}break;
		case' ':
			switch (P_Map.at(X_cursor).at(Y_cursor))
			{
			case P_Flag:break;
			case P_OpEd:break;
			case P_NoOp:
				if (H_Map.at(X_cursor).at(Y_cursor) == H_Bomb) {
					system("cls");
					printf("Bomb!\nGame Over");
					_getch();
					system("cls");
					printf("Conitinu?\ny/n");

					return 0;
				}
				else
				{
					P_Map.at(X_cursor).at(Y_cursor) = P_OpEd;
					Op_Count++;
					if (Op_Count == Width * Height - 20) {
						cout << "WIN\n" << endl << "You're the\nBRAVE\nof\nVietnam" << endl;
						return 0;
					}
				}

			}break;
		}
	}
}