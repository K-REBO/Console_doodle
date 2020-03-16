/*Pong solo version

Attention!
In this code 
Variable is wrote by Snake_Case
Fugasious Variable in Function is wrote by UpperCamelCase
*/
#include<iostream>
#include<thread>
#include<conio.h>
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

int Y_Paddle = 8;

//I gonna code to set Pong Randomly
int X_Pong = 6;// First Place
int Y_Pong = 8;
int Pong_dir = 2; //First Dirction
// End Random 

using namespace std;

void Message(string str){
	system("cls");
	cout << str << endl;
	getch();
}



void Wall(int PongDir)
{
	switch(PongDir)
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



int main(){
	Message("Hello");


}
