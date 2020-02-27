/*Reverci 
*2020/2/27
*/
#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;
#define Height (9)
#define Width (9)

#define Space (0)//Piece color
#define Black (1)
#define White (2)

int X_cursor = 0, Y_cursor = 0;

vector<vector<int>> Map(9, vector<int>(9));

bool Game;
bool Turn = false;//false Black || true White
void Fn_Vec(){
	for (int x = 0; x < Width; ++x) {
		for (int y = 0; y < Height; ++y) {
			Map.at(x).at(y) = Space;
		}
	} 
}

int main() {
	Fn_Vec();
	// massage
	printf("Wellcome to Recerci");
	_getch();
	system("cls");
	printf("Use WASD & SPACE to put Piece");
	_getch();
	system("cls");
	while (!Game){
		Turn = !Turn;
		system("cls");
		//Print Screan						   
		for (int y = 0; y < Height; ++y) {	   
			for (int x = 0; x < Width; ++x) { 
				if ((X_cursor == x) && (Y_cursor == y)) {
					cout << "ž";
				}
				else {
					switch (Map.at(y).at(x))	   
					{							   
					case Black:					   
						cout << "œ"; break;		
					case White:					   
						cout << "Z"; break;		
					default:					   
						cout << " "; break;		
					}							   
				}	
			}							   
			cout << endl;					   
		}									   
		cout << flush;						   
		//Print screan end

		switch (_getch())
		{
		case 'w':
			if (Y_cursor > 0) { Y_cursor--; } break;
		case 's':
			if (Y_cursor < Height) { Y_cursor++; }break;
		case 'a':
			if (X_cursor > 0) { X_cursor--; } break;
		case 'd':
			if (X_cursor < Width) { X_cursor++; } break;
		case ' ':
			Map.at(Y_cursor).at(X_cursor) = (Turn ? Black:White);
			
			
		default:
			break;
		}
		

	}
}
