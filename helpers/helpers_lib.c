#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

/* 

	In this file we developed a library to help the game, here we're gonna find some functions that are the basic 
	patterns to build it, create a project pattern and define some good practices for the game's code.
	
*/

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

/* To change the background color the pattern is:
   FIRST 16 NUMBERS <- Background is the first color (0 - Black)
   For example, if I
*/

// Functions to format the screen

void printf_empty(int num){
	int i;
	for(i=0;i<num;i++) printf("\n");
}


void printf_right(int num){
	int i;
	for(i=0;i<num;i++) printf("\t");
}


void clear_screen(){
	system("cls");
}


void printf_color(char * string, int color){
	HANDLE hConsole;	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	printf("%s", string);
	SetConsoleTextAttribute(hConsole, 7);
}



int main(){
	
	return 0;
}
