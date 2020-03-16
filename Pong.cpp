/*Pong solo version
Attention!
In this code
Variable is wrote by Snake_Case
Fugasious Variable in Function is wrote by UpperCamelCase
*/
#include<iostream>
#include<thread>
#include<conio.h>
#include<vector>
#define X_field (16)
#define Y_field (10)


#define Up (0)
#define UL (1)
#define Le (2)
#define DL (3)
#define Dw (4)
#define DR (5)
#define Rg (6)
#define UR (7)

#define Space (0)
#define UpWall (1)
#define SideWall (2)


using namespace std;

int Y_Paddle = 8;

//I gonna code to set Pong Randomly
int X_Pong = 6;// First Place
int Y_Pong = 8;
int Pong_dir = 2; //First Dirction
// End Random 

vector<vector<int>> Map
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};

vector<vector<char>> Pause_Menu
{
	{'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ','R','e','s','t','e','r','t',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ','R','e','s','u','m','e',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ','Q','u','i','t',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\n'},
	{'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+','\n'}

};

void Message(string str)
{
	system("cls");
	cout << str << endl;
	_getch();
}



void Wall(int PongDir)
{
	switch (PongDir)
	{
	case Up:break;
	case UL:break;
	case Le:break;
	case DL:break;
	case Dw:break;
	case DR:break;
	case Rg:break;
	case UR:break;
	}
}

void Display() {
	for (int x = 0; x < X_field; ++x) 
	{
		for (int y = 0; y < Y_field; ++y)
		{
			cout << Map.at(x).at(y);
		}
		cout << "\n";
	}
	system("cls");
	cout << flush;
}

void Pause() {
	bool Game = false;
	int Pos = 0;

	while (!Game)
	{
		if (Pos == 0) 
		{
			for (int x = 0; x < 19; ++x) 
			{
				for (int y = 0; y < 11; ++y) 
				{
					if ((x == 13) && (y == 3))
					{
						cout << "<";
					}
					else {
					cout << Pause_Menu.at(x).at(y);
					}
				}
			}
		cout << flush;
		}

		else if (Pos == 1) {
			for (int x = 0; x < 19; ++x)
			{
				for (int y = 0; y < 11; ++y)
				{
					if ((x == 13) && (y == 5))
					{
						cout << "<";
					}
					else {
						cout << Pause_Menu.at(x).at(y);
					}
				}
			}
		
		}
		else if (Pos == 2) {
			for (int x = 0; x < 19; ++x)
			{
				for (int y = 0; y < 11; ++y)
				{
					if ((x == 13) && (y == 7))
					{
						cout << "<";
					}
					else {
						cout << Pause_Menu.at(x).at(y);
					}
				}
			}
		
		}

		switch (_getch())
		{
			case 'l':if(Pos != 2)Pos++; break;
			case 'r':if(Pos != 0)Pos--; break;
			case ' ':Game = true; break;
		}
	}
}
int main(){
	bool Game = false;
	Message("Wellcome to Pong");
	Message("Use L&R key to move Paddle \nSpace to show pause menu");
	Message("Tap to start");
	
	while (!Game)
	{
		Display();

		switch (_getch())
		{
		case 'l':
			if (Y_Paddle < Y_field)
				Y_Paddle++;
			break;
		case 'r':
			if (Y_Paddle > 0)
				Y_Paddle--;
			break;
		case ' ':
			Pause();
		}
	}



}
