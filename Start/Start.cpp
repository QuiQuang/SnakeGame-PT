#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "console.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
//Khai báo các file txt để lấy ảnh
const char* f1 = "Intro1.txt";
const char* f2 = "Intro2.txt";
const char* f3 = "Intro3.txt";
const char* f4 = "Gotcha.txt";
const char* f5 = "Yummy.txt";
//---------------------------------------------------------------------------
//Tùy chọn lúc đầu
int ColorWall = 3;
int ColorSnake = 10;
int ColorSnake2 = 12;
int ColorFruit = 14;
int ColorTable = 15;
//---------------------------------------------------------------------------
//Cấu trúc game
int Width = 60;
int	Height = 40;
int defaultWidth = Width;
int defaultHeight = Height;
int tmpW = defaultWidth;
int tmpH = defaultHeight;
int maxW = 90, minW = 60, maxH = 45, minH = 40;
#define len			4
int Point = 0;
const char save1[] = "Save1.txt";
const char save2[] = "Save2.txt";
const char save3[] = "Save3.txt";
//---------------------------------------------------------------------------
//Kí hiệu đặc biệt tạo nên game
#define Head		02
#define Body		111
#define Fruit		232
#define Impediment	177
#define WallTop		220
#define WallBottom	223
#define WallEdge	219
#define BlankSpace u8"             "
//---------------------------------------------------------------------------
//Điều hướng di chuyển
enum Status { UP, DOWN, LEFT, RIGHT };
enum Level { HARD = 20, NORMAL = 25, EASY = 30, CUSTOM = 31 };
//---------------------------------------------------------------------------
//Tắt hiện trỏ chuột
void hidePointer() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
//---------------------------------------------------------------------------
#define MAXPLAYER 11
struct player {
	char name[13];
	int score;
}player[MAXPLAYER];
struct toado {
	int x, y;
};
struct snake {
	toado dot[1000];
	int n;
	Status sta;
	int score = 0;
}snake, snake2;
struct fruit {
	toado toado;
}fruit;
struct gate {
	toado thanh[10];
}gate;
struct impe {
	toado toado;
	Status sta = DOWN;
}impe, impe2, impe3;
struct sound {
	bool updown = true;
	bool Enter = true;
	bool eat = true;
	bool over = true;
}sound;
struct Coordinate {
	int x, y; //dòng - cột
};

//
//---------------------------------------------------------------------------
//Tùy chỉnh về tốc độ, chiều dài, số lượng rắn
int TIME = 155;
Level level = EASY;
int map = 0;
int numOfSnake = 1;
int numOfImpe = 1;
int MODE = 1;
FILE* info;
char MSSV[] = "211275072112710121127195";
char TEN[] = "DINHCONGHUYHOANGVOTANLOCLETUANHTUAN";
int over = 0;
int flag;
int countFruit;
//---------------------------------------------------------------------------
//Function
void OnOffColorLevel();
void OnOffEffectSound(bool a, int b);
void createGate();
void resetGate();
void createSnake();
void spawSnakeinGate();
void createFruit();
void createImpe();
void displayInfo(Level level);
void display();
void displayWall();
void howtoplay();
void Map1();
void Map2();
void Map3();
void Map4();
void Map5();
void createMap();
void saveGame(const char* path, int count, int flag);
void loadGame(const char* path, int& count, int& flag);
int Menu(int& choose, int option);
int MenuThem(int& choose, int option);
void MenuAdd();
void cleanMenu();
void dynamicText(const char text[]);
void displayOver(int over);
void controlMove();
bool touchMap1();
bool touchMap2();
bool touchMap3();
bool touchMap4();
bool touchMap5();
int handling(int& count, int mode);
void Loading();
void Logo();
void Top10();
void readInfo();
void printInfo();
void updateInfo();
void testScore();
void OnOffColor();
void KituMusic();
void SetColor(WORD color);											//Hàm thay đổi màu sắc của ảnh
void convertImage(const char* fname, int a, int b, int x, int y);	//Hàm chèn ảnh vào chương trình
void creatCompleteBar();											//Hàm làm thanh tiến trình
void completedPercent(int a);										//Hàm tiến độ 
void trafficLight();
void QuitGame();
void displayRound(int x);
void displayRoundCenter(int x);
void OnOffColorMode();
void cleanhow();
//---------------------------------------------------------------------------
int main() {
	//------------------------------------------- Intro
	/*Sleep(2000);
	hidePointer();
	convertImage(f1, 174, 50, 0, 0);
	Sleep(3000);

	system("cls");
	hidePointer();
	convertImage(f2, 202, 50, 0, 0);
	convertImage(f3, 239, 50, 20, 28);
	Sleep(3000);
	system("cls");

	displayWall();
	Loading();
	Logo();
	TextColor(ColorWall);
	for (int i = 0; i < 5; i++) {
		gotoXY(defaultWidth / 2 - 5, defaultHeight / 2 + 3);
		cout << "                                   ";
		Sleep(400);
		gotoXY(defaultWidth / 2 - 5, defaultHeight / 2 + 3);
		cout << "Just moment";
		Sleep(400);
	}
	Sleep(1000);
	system("cls");*/

	readInfo();
	//------------------------------------------- Local variables
	int temp1 = 0;
	int temp2 = 1;
	char save[20];
	flag = 0;
	countFruit = 0;
	int choose = 1;
	int color[6] = { 10, 11, 12, 13, 14, 15 };
	int numColor = 6;
	int timeTmp;
	int key = 0;
	char ran[] = "RANDOM";
	//------------------------------------------- Menu
	while (choose != 0) {
		snake.score = 0;
		choose = 1;
		system("cls");
		hidePointer();
		displayWall();

		UINT old_cp = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
		TextColor(6);  gotoXY(Width / 2 - 20, Height / 4 - 5);    cout << u8"███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗" << endl;
		TextColor(9);  gotoXY(Width / 2 - 20, Height / 4 - 4);    cout << u8"██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝" << endl;
		TextColor(11); gotoXY(Width / 2 - 20, Height / 4 - 3);    cout << u8"███████╗██╔██╗ ██║███████║█████╔╝ █████╗  " << endl;
		TextColor(12); gotoXY(Width / 2 - 20, Height / 4 - 2);    cout << u8"╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  " << endl;
		TextColor(14); gotoXY(Width / 2 - 20, Height / 4 - 1);    cout << u8"███████║██║ ╚████║██║  ██║██║  ██╗███████╗" << endl;
		TextColor(15); gotoXY(Width / 2 - 20, Height / 4);        cout << u8"╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝" << endl;
		SetConsoleOutputCP(old_cp);
		/*TextColor(15);
		gotoXY(Width / 2 - 26, Height / 4 - 5); cout << "  _________ _______      _____   ____  __.___________" << endl;
		gotoXY(Width / 2 - 26, Height / 4 - 4); cout << " /   _____/ \\      \\    /  _  \\ |    |/ _|\\_   _____/" << endl;
		gotoXY(Width / 2 - 26, Height / 4 - 3); cout << " \\_____  \\  /   |   \\  /  /_\\  \\|      <   |    __)_" << endl;
		gotoXY(Width / 2 - 26, Height / 4 - 2); cout << " /        \\/    |    \\/    |    \\    |  \\  |        \\" << endl;
		gotoXY(Width / 2 - 26, Height / 4 - 1); cout << "/_______  /\\____|__  /\\____|__  /____|__ \\/_______  /" << endl;
		gotoXY(Width / 2 - 26, Height / 4); cout << "        \\/         \\/         \\/        \\/        \\/ " << endl;*/

		hidePointer();
		gotoXY(Width / 2 - len, Height / 2 - 4);
		TextColor(3);
		puts("START GAME");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
		puts("LEVEL");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
		puts("MODE");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
		puts("SETTING");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 8);
		puts("HIGH SCORE");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 10);
		puts("ABOUT");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
		puts("EXIT");
		choose = Menu(choose, 7);

		switch (choose) {
		case 1: //New game
			choose = 1;
			clrscr();
			hidePointer();
			SetConsoleOutputCP(CP_UTF8);
			TextColor(6);  gotoXY(Width / 2 - 17, Height / 4 - 5);    cout << u8"███╗   ███╗ ██████╗ ██████╗ ███████╗" << endl;
			TextColor(9);  gotoXY(Width / 2 - 17, Height / 4 - 4);    cout << u8"████╗ ████║██╔═══██╗██╔══██╗██╔════╝" << endl;
			TextColor(11); gotoXY(Width / 2 - 17, Height / 4 - 3);    cout << u8"██╔████╔██║██║   ██║██║  ██║█████╗  " << endl;
			TextColor(12); gotoXY(Width / 2 - 17, Height / 4 - 2);    cout << u8"██║╚██╔╝██║██║   ██║██║  ██║██╔══╝  " << endl;
			TextColor(14); gotoXY(Width / 2 - 17, Height / 4 - 1);    cout << u8"██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗" << endl;
			TextColor(15); gotoXY(Width / 2 - 17, Height / 4);        cout << u8"╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝" << endl;
			SetConsoleOutputCP(old_cp);
			/*TextColor(15);	
			gotoXY(Width / 2 - 20, Height / 4 - 5); 	cout << u8"    ___       ___       ___       ___   " << endl;
			gotoXY(Width / 2 - 20, Height / 4 - 4);		cout << u8"   /\\__\\     /\\  \\     /\\  \\     /\\  \\  " << endl;
			gotoXY(Width / 2 - 20, Height / 4 - 3);		cout << u8"  /  L_L_   /  \\  \\   /  \\  \\   /  \\  \\" << endl;
			gotoXY(Width / 2 - 20, Height / 4 - 2);		cout << u8" / /L \\__\\ / /\\ \\__\\ / /\\ \\__\\ /  \\ \\__\\" << endl;
			gotoXY(Width / 2 - 20, Height / 4 - 1);		cout << u8" \\/_/ /  / \\ \\/ /  / \\ \\/ /  / \\ \\ \\/  /" << endl;
			gotoXY(Width / 2 - 20, Height / 4);			cout << u8"   / /  /   \\  /  /   \\  /  /   \\ \\/  /" << endl;
			gotoXY(Width / 2 - 20, Height / 4 + 1);		cout << u8"   \\/__/     \\/__/     \\/__/     \\/__/  " << endl;*/
			displayWall();
			gotoXY(Width / 2 - len, Height / 2 - 4);
			TextColor(10);
			puts("1 PLAYER");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
			TextColor(6);
			puts("2 PLAYER");
			if (MODE == 1) {
				gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
				TextColor(4);
				puts("LOAD GAME");
				TextColor(15);
				choose = Menu(choose, 3);
				hidePointer();
				switch (choose) {
				case 1: //1 người chơi
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 1;
					break;
				case 2: //2 người chơi
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 2;
					TIME -= TIME / 7;
					break;
				case 3:
					choose = 1;
					clrscr();
					hidePointer();
					SetConsoleOutputCP(CP_UTF8);
					TextColor(6);  gotoXY(Width / 2 - 15, Height / 4 - 5);    cout << u8"██╗      ██████╗  █████╗ ██████╗ " << endl;
					TextColor(9);  gotoXY(Width / 2 - 15, Height / 4 - 4);    cout << u8"██║     ██╔═══██╗██╔══██╗██╔══██╗" << endl;
					TextColor(11); gotoXY(Width / 2 - 15, Height / 4 - 3);    cout << u8"██║     ██║   ██║███████║██║  ██║" << endl;
					TextColor(12); gotoXY(Width / 2 - 15, Height / 4 - 2);    cout << u8"██║     ██║   ██║██╔══██║██║  ██║" << endl;
					TextColor(14); gotoXY(Width / 2 - 15, Height / 4 - 1);    cout << u8"███████╗╚██████╔╝██║  ██║██████╔╝" << endl;
					TextColor(15); gotoXY(Width / 2 - 15, Height / 4);        cout << u8"╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ " << endl;
					SetConsoleOutputCP(old_cp);
					/*TextColor(15);
					gotoXY(Width / 2 - 20, Height / 4 - 5);     cout << "    ___       ___       ___       ___   ";
					gotoXY(Width / 2 - 20, Height / 4 - 4);     cout << "   /\\__\\     /\\  \\     /\\  \\     /\\  \\  ";
					gotoXY(Width / 2 - 20, Height / 4 - 3);     cout << "  /:/  /    /::\\  \\   /::\\  \\   /::\\  \\ ";
					gotoXY(Width / 2 - 20, Height / 4 - 2);     cout << " /:/__/    /:/\\:\\__\\ /::\\:\\__\\ /:/\\:\\__\\";
					gotoXY(Width / 2 - 20, Height / 4 - 1);     cout << " \\:\\  \\    \\:\\/:/  / \\/\\::/  / \\:\\/:/  /";
					gotoXY(Width / 2 - 20, Height / 4);			cout << "  \\:\\__\\    \\::/  /    /:/  /   \\::/  / ";
					gotoXY(Width / 2 - 20, Height / 4 + 1);		cout << "   \\/__/     \\/__/     \\/__/     \\/__/  ";*/
					displayWall();
					gotoXY(Width / 2 - len, Height / 2 - 4);
					TextColor(10);
					puts("SAVE - ONE");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
					TextColor(6);
					puts("SAVE - TWO");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
					TextColor(4);
					puts("SAVE - THREE");
					TextColor(15);
					choose = Menu(choose, 3);
					switch (choose) {
					case 1:
						strcpy(save, save1);
						break;
					case 2:
						strcpy(save, save2);
						break;
					case 3:
						strcpy(save, save3);
						break;
					}
					numOfSnake = 1;
					MODE = 3;
					break;
				}
			}
			else {
				TextColor(15);
				choose = Menu(choose, 2);

				switch (choose) {
				case 1: //1 người chơi
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 1;
					break;
				case 2: //2 người chơi
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 2;
					TIME -= TIME / 7;
					break;
				}
			}
			break;
		case 2: //Độ khó của game
			choose = 1;
			clrscr();
			SetConsoleOutputCP(CP_UTF8);
			TextColor(6);  gotoXY(Width / 2 - 18, Height / 4 - 5);    cout << u8"██╗     ███████╗██╗   ██╗███████╗██╗     " << endl;
			TextColor(9);  gotoXY(Width / 2 - 18, Height / 4 - 4);    cout << u8"██║     ██╔════╝██║   ██║██╔════╝██║    " << endl;
			TextColor(11); gotoXY(Width / 2 - 18, Height / 4 - 3);    cout << u8"██║     █████╗  ██║   ██║█████╗  ██║     " << endl;
			TextColor(12); gotoXY(Width / 2 - 18, Height / 4 - 2);    cout << u8"██║     ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║    " << endl;
			TextColor(14); gotoXY(Width / 2 - 18, Height / 4 - 1);    cout << u8"███████╗███████╗ ╚████╔╝ ███████╗███████╗" << endl;
			TextColor(15); gotoXY(Width / 2 - 18, Height / 4);        cout << u8"╚══════╝╚══════╝  ╚═══╝  ╚══════╝╚══════╝" << endl;
			SetConsoleOutputCP(old_cp);
			/*TextColor(15);
			gotoXY(Width / 2 - 26, Height / 4 - 5);     cout << "    ___       ___       ___       ___       ___   ";
			gotoXY(Width / 2 - 26, Height / 4 - 4);     cout << "   /\\__\\     /\\  \\     /\\__\\     /\\  \\     /\\__\\  ";
			gotoXY(Width / 2 - 26, Height / 4 - 3);     cout << "  / /  /    /  \\  \\   / / _/_   /  \\  \\   / /  /  ";
			gotoXY(Width / 2 - 26, Height / 4 - 2);     cout << " / /__/    /  \\ \\__\\ |  L/\\__\\ /  \\ \\__\\ / /__/  ";
			gotoXY(Width / 2 - 26, Height / 4 - 1);     cout << " \\ \\  \\    \\ \\ \\/  / |    /  / \\  \\ \\/  /\\ \\  \\   ";
			gotoXY(Width / 2 - 26, Height / 4);			cout << "  \\ \\__\\    \\ \\/  /   L;;/__/   \\ \\/  /   \\ \\__\\  ";
			gotoXY(Width / 2 - 26, Height / 4 + 1);     cout << "   \\/__/     \\/__/               \\/__/     \/__/ ";*/
			TextColor(3);
			hidePointer();
			displayWall();
			OnOffColorLevel();
			gotoXY(Width / 2 - len, Height / 2 - 4);
			TextColor(10);
			puts("EASY");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
			TextColor(14);
			puts("NORMAL");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
			TextColor(12);
			puts("HARD");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
			TextColor(6);
			puts("CUSTOM");
			TextColor(15);
			choose = Menu(choose, 4);

			switch (choose) {

			case 1: //Easy
				level = EASY;
				TIME = 155;
				numOfImpe = 1;
				clrscr();
				hidePointer();
				break;
			case 2: //Normal
				level = NORMAL;
				TIME = 95;
				numOfImpe = 2;
				clrscr();
				hidePointer();
				break;
			case 3: //Hard
				level = HARD;
				TIME = 50;
				numOfImpe = 3;
				clrscr();
				hidePointer();
				break;
			case 4: //Custom
				level = CUSTOM;
				timeTmp = TIME;
				key = 0;
				clrscr();

				SetConsoleOutputCP(CP_UTF8);
				TextColor(6);  gotoXY(Width / 2 - 6, Height / 4 - 5);    cout << u8"██╗   ██╗██████╗ " << endl;
				TextColor(9);  gotoXY(Width / 2 - 6, Height / 4 - 4);    cout << u8"██║   ██║██╔══██╗" << endl;
				TextColor(11); gotoXY(Width / 2 - 6, Height / 4 - 3);    cout << u8"██║   ██║██████╔╝" << endl;
				TextColor(12); gotoXY(Width / 2 - 6, Height / 4 - 2);    cout << u8"██║   ██║██╔═══╝ " << endl;
				TextColor(14); gotoXY(Width / 2 - 6, Height / 4 - 1);    cout << u8"╚██████╔╝██║    " << endl;
				TextColor(15); gotoXY(Width / 2 - 6, Height / 4);        cout << u8" ╚═════╝ ╚═╝    " << endl;
				SetConsoleOutputCP(old_cp);
				/*TextColor(15);
				gotoXY(Width / 2 - 10, Height / 4 - 5);     cout << "    ___       ___   ";
				gotoXY(Width / 2 - 10, Height / 4 - 4);     cout << "   /\\__\\     /\\  \\  ";
				gotoXY(Width / 2 - 10, Height / 4 - 3);     cout << "  / / _/_   /  \\  \\ ";
				gotoXY(Width / 2 - 10, Height / 4 - 2);     cout << " / /_/\\__\\ /  \\ \\__\\";
				gotoXY(Width / 2 - 10, Height / 4 - 1);     cout << " \\ \\/ /  / \\/\\  /  /";
				gotoXY(Width / 2 - 10, Height / 4);			cout << "  \\  /  /     \\/__/";
				gotoXY(Width / 2 - 10, Height / 4 + 1);     cout << "   \\/__/           ";*/
				/*gotoXY(Width / 2 - 20, Height / 4 + 16);     cout << "    ___       ___       ___       ___   ";
				gotoXY(Width / 2 - 20, Height / 4 + 17);     cout << "   /\\  \\     /\\  \\     /\\__\\     /\\__\\  ";
				gotoXY(Width / 2 - 20, Height / 4 + 18);     cout << "  /  \\  \\   /  \\  \\   / /\\__\\   / | _|_ ";
				gotoXY(Width / 2 - 20, Height / 4 + 19);     cout << " / /\\ \\__\\ / /\\ \\__\\ / / /\\__\\ /  |/\\__\\";
				gotoXY(Width / 2 - 20, Height / 4 + 20);     cout << " \\ \\/ /  / \\ \\/ /  / \\  / /  / \\/|  /  /";
				gotoXY(Width / 2 - 20, Height / 4 + 21);	cout << "  \\  /  /   \\  /  /   \\  /  /    | /  / ";
				gotoXY(Width / 2 - 20, Height / 4 + 22);    cout << "   \\/__/     \\/__/     \\/__/     \\/__/  ";*/
				SetConsoleOutputCP(CP_UTF8);
				TextColor(6);  gotoXY(Width / 2 - 17, Height / 4 + 16);    cout << u8"██████╗  ██████╗ ██╗    ██╗███╗   ██╗" << endl;
				TextColor(9);  gotoXY(Width / 2 - 17, Height / 4 + 17);    cout << u8"██╔══██╗██╔═══██╗██║    ██║████╗  ██║" << endl;
				TextColor(11); gotoXY(Width / 2 - 17, Height / 4 + 18);    cout << u8"██║  ██║██║   ██║██║ █╗ ██║██╔██╗ ██║" << endl;
				TextColor(12); gotoXY(Width / 2 - 17, Height / 4 + 19);    cout << u8"██║  ██║██║   ██║██║███╗██║██║╚██╗██║" << endl;
				TextColor(14); gotoXY(Width / 2 - 17, Height / 4 + 20);    cout << u8"██████╔╝╚██████╔╝╚███╔███╔╝██║ ╚████║" << endl;
				TextColor(15); gotoXY(Width / 2 - 17, Height / 4 + 21);    cout << u8"╚═════╝  ╚═════╝  ╚══╝╚══╝ ╚═╝  ╚═══╝" << endl;
				SetConsoleOutputCP(old_cp);


				hidePointer();
				displayWall();
				gotoXY(Width / 2 - 2 * len, Height / 2 - 2);
				puts("ENTER SLEEP TIME: ");
				while (key != 13) {
					gotoXY(Width / 2 - 1, Height / 2);
					cout << timeTmp << " ";
					key = _getch();
					if ((key == 'w' || key == 'W' || key == 72) && timeTmp < 200)
						timeTmp++;
					else if ((key == 's' || key == 'S' || key == 80) && timeTmp > 10)
						timeTmp--;
				}
				TIME = timeTmp;
				break;
			}
			continue;
		case 3: //Mode game -> Sinh tồn hoặc cơ bản
			choose = 1;

			clrscr();
			hidePointer();
			TextColor(15);
			SetConsoleOutputCP(CP_UTF8);
			TextColor(6);  gotoXY(Width / 2 - 15, Height / 4 - 5);    cout << u8"███╗   ███╗ ██████╗ ██████╗ ███████╗" << endl;
			TextColor(9);  gotoXY(Width / 2 - 15, Height / 4 - 4);    cout << u8"████╗ ████║██╔═══██╗██╔══██╗██╔════╝" << endl;
			TextColor(11); gotoXY(Width / 2 - 15, Height / 4 - 3);    cout << u8"██╔████╔██║██║   ██║██║  ██║█████╗  " << endl;
			TextColor(12); gotoXY(Width / 2 - 15, Height / 4 - 2);    cout << u8"██║╚██╔╝██║██║   ██║██║  ██║██╔══╝  " << endl;
			TextColor(14); gotoXY(Width / 2 - 15, Height / 4 - 1);    cout << u8"██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗" << endl;
			TextColor(15); gotoXY(Width / 2 - 15, Height / 4);        cout << u8"╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝" << endl;
			SetConsoleOutputCP(old_cp);
			TextColor(3);
			displayWall();
			OnOffColorMode();
			gotoXY(Width / 2 - len, Height / 2 - 4);
			TextColor(10);
			puts("CLASSIC");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
			TextColor(4);
			puts("SURVIVAL");
			TextColor(15);
			choose = Menu(choose, 2);

			switch (choose) {
			case 1:
				MODE = 1;
				break;
			case 2:
				MODE = 2;
				break;
			}
			continue;
		case 4: //Custom màu và size của wall
			choose = 1;
			clrscr();
			hidePointer();
			SetConsoleOutputCP(CP_UTF8);
			TextColor(6);  gotoXY(Width / 2 - 27, Height / 4 - 5);    cout << u8"███████╗███████╗████████╗████████╗██╗███╗   ██╗ ██████╗ " << endl;
			TextColor(9);  gotoXY(Width / 2 - 27, Height / 4 - 4);    cout << u8"██╔════╝██╔════╝╚══██╔══╝╚══██╔══╝██║████╗  ██║██╔════╝ " << endl;
			TextColor(11); gotoXY(Width / 2 - 27, Height / 4 - 3);    cout << u8"███████╗█████╗     ██║      ██║   ██║██╔██╗ ██║██║  ███╗" << endl;
			TextColor(12); gotoXY(Width / 2 - 27, Height / 4 - 2);    cout << u8"╚════██║██╔══╝     ██║      ██║   ██║██║╚██╗██║██║   ██║" << endl;
			TextColor(14); gotoXY(Width / 2 - 27, Height / 4 - 1);    cout << u8"███████║███████╗   ██║      ██║   ██║██║ ╚████║╚██████╔╝" << endl;
			TextColor(15); gotoXY(Width / 2 - 27, Height / 4);        cout << u8"╚══════╝╚══════╝   ╚═╝      ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ " << endl;
			SetConsoleOutputCP(old_cp);
			TextColor(3);
			displayWall();
			gotoXY(Width / 2 - len, Height / 2 - 4);
			TextColor(12);
			puts("COLOR CUSTOM");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
			TextColor(ColorWall);
			puts("WALL CUSTOM");
			gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
			TextColor(6);
			puts("MUSIC CUSTOM");
			TextColor(15);
			choose = Menu(choose, 3);

			switch (choose) {

			case 1: //Show custom
				choose = 1;
				clrscr();
				hidePointer();
				displayWall();
				SetConsoleOutputCP(CP_UTF8);
				TextColor(6);  gotoXY(Width / 2 - 21, Height / 4 - 5);    cout << u8" ██████╗ ██████╗ ██╗      ██████╗ ██████╗ " << endl;
				TextColor(9);  gotoXY(Width / 2 - 21, Height / 4 - 4);    cout << u8"██╔════╝██╔═══██╗██║     ██╔═══██╗██╔══██╗" << endl;
				TextColor(11); gotoXY(Width / 2 - 21, Height / 4 - 3);    cout << u8"██║     ██║   ██║██║     ██║   ██║██████╔╝" << endl;
				TextColor(12); gotoXY(Width / 2 - 21, Height / 4 - 2);    cout << u8"██║     ██║   ██║██║     ██║   ██║██╔══██╗" << endl;
				TextColor(14); gotoXY(Width / 2 - 21, Height / 4 - 1);    cout << u8"╚██████╗╚██████╔╝███████╗╚██████╔╝██║  ██║" << endl;
				TextColor(15); gotoXY(Width / 2 - 21, Height / 4);        cout << u8" ╚═════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝" << endl;
				SetConsoleOutputCP(old_cp);
				TextColor(ColorSnake);
				gotoXY(Width / 2 - len, Height / 2 - 4 );
				puts("PLAYER 1");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				TextColor(ColorSnake2);
				puts("PLAYER 2");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
				TextColor(ColorFruit);
				puts("FRUIT COLOR");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
				TextColor(ColorWall);
				puts("WALL COLOR");
				TextColor(15);
				choose = Menu(choose, 4);
				switch (choose) {
				case 1:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();

					for (int i = 0, j = 0; i < numColor; i++, j += 2) {
						TextColor(color[i]);
						gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
						putchar(Head);
						for (int i = 0; i < 5; i++) {
							gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
							putchar(Body);
						}
					}
					gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
					for (int i = 0; i < 6; i++) {
						TextColor(color[i]);
						cout << ran[i];
					}
					choose = Menu(choose, 7);
					switch (choose) {
					case 1:
						ColorSnake = 10;
						break;
					case 2:
						ColorSnake = 11;
						break;
					case 3:
						ColorSnake = 12;
						break;
					case 4:
						ColorSnake = 13;
						break;
					case 5:
						ColorSnake = 14;
						break;
					case 6:
						ColorSnake = 15;
						break;
					case 7:
						srand((int)time(NULL));
						ColorSnake = 1 + rand() % 15;
						break;
					}
					break;
				case 2:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();
					for (int i = 0, j = 0; i < numColor; i++, j += 2) {
						TextColor(color[i]);
						gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
						putchar(Head);
						for (int i = 0; i < 5; i++) {
							gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
							putchar(Body);
						}
					}
					gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
					for (int i = 0; i < 6; i++) {
						TextColor(color[i]);
						cout << ran[i];
					}
					choose = Menu(choose, 7);
					switch (choose) {
					case 1:
						ColorSnake2 = 10;
						break;
					case 2:
						ColorSnake2 = 11;
						break;
					case 3:
						ColorSnake2 = 12;
						break;
					case 4:
						ColorSnake2 = 13;
						break;
					case 5:
						ColorSnake2 = 14;
						break;
					case 6:
						ColorSnake2 = 15;
						break;
					case 7:
						srand((int)time(NULL));
						ColorSnake2 = 1 + rand() % 15;
						break;
					}
					break;
				case 3:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();

					for (int i = 0, j = 0; i < numColor; i++, j += 2) {
						TextColor(color[i]);
						gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
						putchar(Fruit);
					}
					gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
					for (int i = 0; i < 6; i++) {
						TextColor(color[i]);
						cout << ran[i];
					}
					choose = Menu(choose, 7);
					switch (choose) {
					case 1:
						ColorFruit = 10;
						break;
					case 2:
						ColorFruit = 11;
						break;
					case 3:
						ColorFruit = 12;
						break;
					case 4:
						ColorFruit = 13;
						break;
					case 5:
						ColorFruit = 14;
						break;
					case 6:
						ColorFruit = 15;
						break;
					case 7:
						srand((int)time(NULL));
						ColorFruit = 1 + rand() % 15;
						break;
					}
					break;
				case 4:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();
					for (int i = 0, j = 0; i < numColor; i++, j += 2) {
						TextColor(color[i]);
						for (int i = 0; i < 8; i++) {
							gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
							putchar(WallTop);
						}
					}
					gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
					for (int i = 0; i < 6; i++) {
						TextColor(color[i]);
						cout << ran[i];
					}
					choose = Menu(choose, 7);
					switch (choose) {
					case 1:
						ColorWall = 10;
						break;
					case 2:
						ColorWall = 11;
						break;
					case 3:
						ColorWall = 12;
						break;
					case 4:
						ColorWall = 13;
						break;
					case 5:
						ColorWall = 14;
						break;
					case 6:
						ColorWall = 15;
						break;
					case 7:
						srand((int)time(NULL));
						ColorWall = 1 + rand() % 15;
						break;
					}
					break;
				}
				break;
			case 2:
				choose = 1;
				clrscr();
				hidePointer();
				displayWall();
				SetConsoleOutputCP(CP_UTF8);
				TextColor(6);  gotoXY(Width / 2 - 13, Height / 4 - 5);    cout << u8"███████╗██╗███████╗███████╗" << endl;
				TextColor(9);  gotoXY(Width / 2 - 13, Height / 4 - 4);    cout << u8"██╔════╝██║╚══███╔╝██╔════╝" << endl;
				TextColor(11); gotoXY(Width / 2 - 13, Height / 4 - 3);    cout << u8"███████╗██║  ███╔╝ █████╗  " << endl;
				TextColor(12); gotoXY(Width / 2 - 13, Height / 4 - 2);    cout << u8"╚════██║██║ ███╔╝  ██╔══╝  " << endl;
				TextColor(14); gotoXY(Width / 2 - 13, Height / 4 - 1);    cout << u8"███████║██║███████╗███████╗" << endl;
				TextColor(15); gotoXY(Width / 2 - 13, Height / 4);        cout << u8"╚══════╝╚═╝╚══════╝╚══════╝" << endl;
				SetConsoleOutputCP(old_cp);
				TextColor(3);
				gotoXY(Width / 2 - len, Height / 2 - 4);
				puts("DEFAULT");
				gotoXY(Width / 2 - 3 * len, Height / 2 - 4 + 1);
				cout << "(Width: " << defaultWidth << ", Height : " << defaultHeight << ")";
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				puts("CUSTOM");

				TextColor(15);
				choose = Menu(choose, 2);
				switch (choose) {

				case 1:
					clrscr();
					Width = defaultWidth;
					Height = defaultHeight;
					break;
				case 2:
					clrscr();
					hidePointer();
					displayWall();
					SetConsoleOutputCP(CP_UTF8);
					TextColor(6);  gotoXY(Width / 2 - 13, Height / 4 - 5);    cout << u8"███████╗██╗███████╗███████╗" << endl;
					TextColor(9);  gotoXY(Width / 2 - 13, Height / 4 - 4);    cout << u8"██╔════╝██║╚══███╔╝██╔════╝" << endl;
					TextColor(11); gotoXY(Width / 2 - 13, Height / 4 - 3);    cout << u8"███████╗██║  ███╔╝ █████╗  " << endl;
					TextColor(12); gotoXY(Width / 2 - 13, Height / 4 - 2);    cout << u8"╚════██║██║ ███╔╝  ██╔══╝  " << endl;
					TextColor(14); gotoXY(Width / 2 - 13, Height / 4 - 1);    cout << u8"███████║██║███████╗███████╗" << endl;
					TextColor(15); gotoXY(Width / 2 - 13, Height / 4);        cout << u8"╚══════╝╚═╝╚══════╝╚══════╝" << endl;
					SetConsoleOutputCP(old_cp);
					TextColor(3);
					gotoXY(Width / 2 - 13, Height / 2 - 4);
					cout << "Num Of WIDTH (MAX: " << maxW << ",MIN: " << minW << ")";
					while (1) {
						gotoXY(Width / 2 - 1, Height / 2 - 4 + 2);
						cin >> tmpW;
						if (tmpW > maxW || tmpW < minW) {
							for (int i = 0; i < 4; i++) {
								TextColor(3);
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 1);
								cout << "Please ENTER again:";
								Sleep(100);
								TextColor(15);
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 1);
								cout << "Please ENTER again:";
								Sleep(100);
							}
							TextColor(3);
							gotoXY(Width / 2 - 1, Height / 2 - 4 + 2);
							cout << "      ";
							continue;
						}
						if (tmpW <= maxW && tmpW >= minW)
							break;
					}
					fflush(stdin);
					gotoXY(Width / 2 - 13, Height / 2 - 4 + 4);
					cout << "Num Of Height(MAX: " << maxH << ",MIN: " << minH << ")";
					while (1) {
						gotoXY(Width / 2 - 1, Height / 2 - 4 + 6);
						cin >> tmpH;
						if (tmpH > maxH || tmpH < minH) {
							for (int i = 0; i < 4; i++) {
								TextColor(3);
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 5);
								cout << "Please ENTER again:";
								Sleep(100);
								TextColor(15);
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 5);
								cout << "Please ENTER again:";
								Sleep(100);
							}
							TextColor(3);
							gotoXY(Width / 2 - 1, Height / 2 - 4 + 6);
							cout << "      ";
							continue;
						}
						else if (tmpH <= maxH && tmpH >= minH)
							break;
					}
					Height = tmpH;
					Width = tmpW;
					break;
				}
				break;

			case 3:   //Tắt mở nhạc 
				choose = 1;
				clrscr();
				TextColor(15);
				UINT old_cp = GetConsoleOutputCP();
				SetConsoleOutputCP(CP_UTF8);
				TextColor(6); gotoXY(Width / 2 - 18, Height / 4 - 5);     cout << u8"███╗   ███╗██╗   ██╗███████╗██╗ ██████╗" << endl;
				TextColor(9); gotoXY(Width / 2 - 18, Height / 4 - 4);     cout << u8"████╗ ████║██║   ██║██╔════╝██║██╔════╝" << endl; 
				TextColor(11); gotoXY(Width / 2 - 18, Height / 4 - 3);    cout << u8"██╔████╔██║██║   ██║███████╗██║██║     " << endl; 
				TextColor(12); gotoXY(Width / 2 - 18, Height / 4 - 2);    cout << u8"██║╚██╔╝██║██║   ██║╚════██║██║██║     " << endl; 
				TextColor(14); gotoXY(Width / 2 - 18, Height / 4 - 1);    cout << u8"██║ ╚═╝ ██║╚██████╔╝███████║██║╚██████╗" << endl; 
				TextColor(15); gotoXY(Width / 2 - 18, Height / 4);        cout << u8"╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝ ╚═════╝" << endl;
				SetConsoleOutputCP(old_cp);
				displayWall();
				gotoXY(Width / 2 - len, Height / 2 - 4);
				TextColor(13);
				puts("SOUND EFFECT");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				TextColor(12);
				puts("ALL SOUND");
				TextColor(15);
				choose = Menu(choose, 2);
				switch (choose) {
				case 1:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();
					TextColor(14);
					gotoXY(Width / 2 - len, Height / 2 - 4);
					puts("EAT SOUND");
					gotoXY(Width / 2 - len + 15, Height / 2 - 4);
					KituMusic();
					gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
					TextColor(13);
					puts("GAMEOVER SOUND");
					gotoXY(Width / 2 - len + 15, Height / 2 - 4 + 2);
					KituMusic();
					gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
					TextColor(12);
					puts("UPDOWN SOUND");
					gotoXY(Width / 2 - len + 15, Height / 2 - 4 + 4);
					KituMusic();
					gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
					TextColor(11);
					puts("ENTER SOUND");
					gotoXY(Width / 2 - len + 15, Height / 2 - 4 + 6);
					KituMusic();
					TextColor(15);
					choose = Menu(choose, 4);
					switch (choose) {
					case 1:
						choose = 1;
						clrscr();
						hidePointer();
						displayWall();
						gotoXY(Width / 2 - len, Height / 2 - 4);
						TextColor(10);
						puts("TURN ON");
						gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
						TextColor(12);
						puts("TURN OFF");
						OnOffColor();
						TextColor(15);
						choose = Menu(choose, 2);
						switch (choose) {
						case 1:
							sound.eat = true;
							break;
						case 2:
							sound.eat = false;
							break;
						}
						break;
					case 2:
						choose = 1;
						clrscr();
						hidePointer();
						displayWall();
						gotoXY(Width / 2 - len, Height / 2 - 4);
						TextColor(10);
						puts("TURN ON");
						gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
						TextColor(12);
						puts("TURN OFF");
						OnOffColor();
						TextColor(15);
						choose = Menu(choose, 2);
						switch (choose) {
						case 1:
							sound.over = true;
							break;
						case 2:
							sound.over = false;
							break;
						}
						break;
					case 3:
						choose = 1;
						clrscr();
						hidePointer();
						displayWall();
						gotoXY(Width / 2 - len, Height / 2 - 4);
						TextColor(10);
						puts("TURN ON");
						gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
						TextColor(12);
						puts("TURN OFF");
						OnOffColor();
						TextColor(15);
						choose = Menu(choose, 2);
						switch (choose) {
						case 1:
							sound.updown = true;
							break;
						case 2:
							sound.updown = false;
							break;
						}
						break;
					case 4:
						choose = 1;
						clrscr();
						hidePointer();
						displayWall();
						gotoXY(Width / 2 - len, Height / 2 - 4);
						TextColor(10);
						puts("TURN ON");
						gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
						TextColor(12);
						puts("TURN OFF");
						OnOffColor();
						TextColor(3);
						choose = Menu(choose, 2);
						switch (choose) {
						case 1:
							sound.Enter = true;
							break;
						case 2:
							sound.Enter = false;
							break;
						}
						break;
					}
					break;
				case 2:
					choose = 1;
					clrscr();
					hidePointer();
					displayWall();
					TextColor(10);
					gotoXY(Width / 2 - len, Height / 2 - 4);
					puts("TURN ON");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
					TextColor(12);
					puts("TURN OFF");
					UINT old_cp = GetConsoleOutputCP();
					SetConsoleOutputCP(CP_UTF8);
					TextColor(10);
					gotoXY(Width / 2 - len + 9, Height / 2 - 4);
					cout << u8"●";
					TextColor(12);
					gotoXY(Width / 2 - len + 9, Height / 2 - 4 + 2);
					cout << u8"●";
					SetConsoleOutputCP(old_cp);
					TextColor(15);
					choose = Menu(choose, 2);

					switch (choose) {
					case 1:
						sound.eat = true;
						sound.over = true;
						sound.updown = true;
						sound.Enter = true;
						break;
					case 2:
						sound.eat = false;
						sound.over = false;
						sound.updown = false;
						sound.Enter = false;
						break;
					}

					break;
				}

			}
			continue;
		case 5: //Highscore
			clrscr();
			hidePointer();
			Top10();
			TextColor(3);
			displayWall();
			printInfo();
			_getch();
			continue;
		case 6: //About
			clrscr();
			hidePointer();
			displayWall();
			QuitGame();
			_getch();
			continue;
		case 7: //Exit
			while (1) {
				gotoXY(Width / 2 - len - 2, Height / 2 - 4 + 12);
				puts("EXIT GAME....");
				Sleep(250);
				gotoXY(Width / 2 - len - 2, Height / 2 - 4 + 12);
				for (int i = 0; i < strlen("EXIT GAME...."); i++) {
					cout << " ";
				}
				Sleep(250);
				if (_kbhit()) {
					if (_getch() == 13)
						break;
				}
			}
			system("cls");
			break;
		}
		if (choose == 7) {
			updateInfo();
			break;
		}
		//------------------------------------------------------------------------------------------------------------------------
		//													Start Game
		//------------------------------------------------------------------------------------------------------------------------
		if (MODE != 2) {
			if (MODE == 1) {
				countFruit = 0;
				flag = 0;
				snake.n = 5;
				resetGate();
				createFruit();
				createSnake();
				clrscr();
				displayWall();
				map = 0;
				dynamicText("PRESS ENTER");
				trafficLight();				
				displayRound(map);
				hidePointer();

				TextColor(ColorFruit);
				gotoXY(fruit.toado.x, fruit.toado.y);
				putchar(Fruit);

			}
			else {
				clrscr();
				resetGate();
				displayWall();
				hidePointer();
				loadGame(save, countFruit, flag);
				displayRoundCenter(map);
				trafficLight();
			}
			while (1) {
				displayWall();
				howtoplay();
				if (numOfSnake != 2) {
					creatCompleteBar();
					displayRound(map);
				}
				createMap();
				display();
				if (countFruit % 3 == 0) {
					TextColor(ColorFruit);
					gotoXY(fruit.toado.x, fruit.toado.y);
					putchar(Fruit);
				}
				over = handling(countFruit, MODE);
				temp1 = countFruit;
				if (numOfSnake == 1) {
					if (temp1 == 1 && temp1 == temp2)
					{
						completedPercent(countFruit);
						cleanhow();
						convertImage(f4, 65, 0, Width + 20, Height / 2 - 12);
						Sleep(500);
						convertImage(f4, 128, 0, Width + 20, Height / 2 - 12);
						temp2++;
					}
					if (temp1 == 2 && temp1 == temp2)
					{
						completedPercent(countFruit);
						cleanhow();
						convertImage(f5, 13, 0, Width + 18, Height / 2 - 10);
						Sleep(500);
						convertImage(f5, 128, 0, Width + 18, Height / 2 - 10);
						temp2++;
					}
				}
				hidePointer();
				controlMove();
				if (numOfSnake == 1) {
					if (over == -1 || over == 1 || over == -3) {
						displayOver(over);
						testScore();
						temp1 = 0;
						temp2 = 1;
						break;
					}
					if (countFruit >= 2) {
						gotoXY(Width / 2, 10);
						createGate();
						if (snake.dot[0].x == gate.thanh[0].x && snake.dot[0].y == gate.thanh[0].y) {
							flag = 1;
							for (int i = snake.n; i >= 0; i--) {
								gotoXY(snake.dot[i].x, snake.dot[i].y);
								putchar(' ');
								Sleep(50);
							}
							system("cls");
							gotoXY(Width / 2, Height / 2);
							TextColor(14);
							displayWall();
							countFruit = 0;
							temp1 = 0;
							temp2 = 1;
							map++;
							displayRoundCenter(map);
							trafficLight();
							displayRound(map);
							createMap();
							spawSnakeinGate();  
							gotoXY(gate.thanh[0].x, gate.thanh[0].y);
							putchar(' ');
							displayWall();
							howtoplay();
							for (int i = snake.n - 1; i--; i >= 0) {
								gotoXY(snake.dot[i].x, snake.dot[i].y);
								if (i == 0) {
									putchar(Head);
								}
								else if (i == 1) {
									putchar('*');
								}
								else cout << MSSV[i - 2];
								Sleep(100);
							}
							resetGate();
						}
					}

					if (snake.sta == UP || snake.sta == DOWN)
						Sleep(TIME);
					else Sleep(TIME);
				}
				else if (numOfSnake == 2) {
					if (over == -2 || over == 2 || over == 3 || over == -3) {
						displayOver(over);
						clrscr();
						hidePointer();
						break;
					}
					if (snake.sta == UP || snake.sta == DOWN || snake2.sta == UP || snake2.sta == DOWN)
						Sleep(50);
					else Sleep(TIME);
					Sleep(TIME);
				}
			}
		}
		else if(MODE == 2) {
			map = 0;
			hidePointer();
			createSnake();
			createFruit();
			createImpe();
			clrscr();
			displayWall();
			trafficLight();
			TextColor(ColorFruit);
			gotoXY(fruit.toado.x, fruit.toado.y);
			putchar(Fruit);
			display();
			howtoplay();

			while (1) {
				howtoplay();
				resetGate();
				hidePointer();
				over = handling(countFruit, MODE);
				controlMove();
				display();
				TextColor(ColorFruit);
				gotoXY(fruit.toado.x, fruit.toado.y);
				putchar(Fruit);
				if (numOfSnake == 1) {
					if (over == -1 || over == 1 || over == -3) {
						displayOver(over);
						testScore();
						break;
					}
					if (snake.sta == UP || snake.sta == DOWN)
						Sleep(TIME);
					else Sleep(TIME);
				}
				else if (numOfSnake == 2) {
					if (over == -2 || over == 2 || over == 3 || over == -3) {
						displayOver(over);
						clrscr();
						hidePointer();
						break;
					}
					if (snake.sta == UP || snake.sta == DOWN || snake2.sta == UP || snake2.sta == DOWN)
						Sleep(TIME);
					else Sleep(TIME);
					Sleep(TIME);
				}
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------








//Sound
void OnOffEffectSound(bool a, int b) {
	switch (b) {
	case 1:
		if (a == true) {
			PlaySound(TEXT("eating.wav"), NULL, SND_ASYNC);
		}
		break;
	case 2:
		if (a == true) {
			PlaySound(TEXT("lose.wav"), NULL, SND_ASYNC);
		}
		break;
	case 3:
		if (a == true) {
			PlaySound(TEXT("cartoonAccent.wav"), NULL, SND_ASYNC);
		}
		break;
	case 4:
		if (a == true) {
			PlaySound(TEXT("enter.wav"), NULL, SND_ASYNC);
		}
		break;
	}
}
void OnOffColor() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(10);
	gotoXY(Width / 2 - len + 9, Height / 2 - 4);
	cout << u8"●";
	TextColor(12);
	gotoXY(Width / 2 - len + 9, Height / 2 - 4 + 2);
	cout << u8"●";
	SetConsoleOutputCP(old_cp);
	TextColor(11);
}
void KituMusic()
{
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(6);
	cout << u8"♪";
	SetConsoleOutputCP(old_cp);
}

//Tạo hàng rào
void createGate() {
	gate.thanh[0].x = Width / 2;
	gate.thanh[0].y = 10;
	gate.thanh[1].x = Width / 2 + 1;
	gate.thanh[1].y = 10;
	gate.thanh[2].x = Width / 2 - 1;
	gate.thanh[2].y = 10;
	gate.thanh[3].x = Width / 2 + 1;
	gate.thanh[3].y = 11;
	gate.thanh[4].x = Width / 2 - 1;
	gate.thanh[4].y = 11;
	gate.thanh[5].x = Width / 2 - 1;
	gate.thanh[5].y = 9;
	gate.thanh[6].x = Width / 2;
	gate.thanh[6].y = 9;
	gate.thanh[7].x = Width / 2 + 1;
	gate.thanh[7].y = 9;
	TextColor(15);
	for (int i = 1; i <= 7; i++) {
		if (i < 5) {
			gotoXY(gate.thanh[i].x, gate.thanh[i].y);
			putchar(204);
		}
		else {
			gotoXY(gate.thanh[i].x, gate.thanh[i].y);
			putchar(177);
		}
	}
	TextColor(13);
	gotoXY(gate.thanh[0].x, gate.thanh[0].y);
	putchar(254);
}
void resetGate() {
	for (int i = 0; i <= 7; i++) {
		gate.thanh[i].x = 0;
		gate.thanh[i].y = 0;
	}
}

//Tạo rắn
void createSnake() {
	//snake 1
	snake.n = 5;
	for (int i = snake.n - 1, j = 2; i >= 0; i--, j++) {
		snake.dot[i].x = j;
		snake.dot[i].y = 2;
	}
	snake.sta = RIGHT;
	// snake 2
	if (numOfSnake == 2) {
		snake2.n = 5;
		for (int i = snake2.n - 1, j = 2; i >= 0; i--, j++) {
			snake2.dot[i].x = j;
			snake2.dot[i].y = Height - 5;
		}
		snake2.sta = RIGHT;
	}
}
void spawSnakeinGate() {
	TextColor(13);
	gotoXY(gate.thanh[0].x, gate.thanh[0].y);
	putchar(254);
	for (int i = snake.n - 1, j = 11; i >= 0; i--, j++) {
		snake.dot[i].x = Width / 2;
		snake.dot[i].y = j;
		Sleep(150);
	}
	snake.sta = DOWN;
}
//Tạo đồ ăn
void createFruit() {
	srand((unsigned int)time(0));
	int flag = 0;
	while (1) {
		flag = 0;
		fruit.toado.x = 1 + rand() % (Width - 1);
		fruit.toado.y = 1 + rand() % (Height - 1);
		for (int i = 0; i < snake.n; i++) {
			if (snake.dot[i].x == fruit.toado.x && snake.dot[i].y == fruit.toado.y)
				flag = 1;
			else if (snake2.dot[i].x == fruit.toado.x && snake2.dot[i].y == fruit.toado.y)
				flag = 1;
		}
		//Map 1
		if (map == 1) {
			if (fruit.toado.y == Height / 4 || fruit.toado.y == Height / 4 * 3)
			{
				if ((fruit.toado.x >= Width / 3 && fruit.toado.x <= Width / 3 + 5) || (fruit.toado.x >= Width / 2 + 5 && fruit.toado.x <= Width / 3 * 2))
					flag = 1;
			}
			if (fruit.toado.x == Width / 3 || fruit.toado.x == Width / 3 * 2)
			{
				if ((fruit.toado.y >= Height / 4 && fruit.toado.y <= Height / 4 + 5) || (fruit.toado.y >= Height / 2 + 5 && fruit.toado.y <= Height - 10))
					flag = 1;
			}
		}
		//Map 2
		if (map == 2) {
			if (fruit.toado.y == Height / 4 + 5 || fruit.toado.y == Height / 2 + 5)
			{
				if ((fruit.toado.x >= Width / 3 && fruit.toado.x <= Width / 3 + 5) || (fruit.toado.x >= Width / 2 + 5 && fruit.toado.x <= Width / 3 * 2))
					flag = 1;
			}
			if (fruit.toado.x == Width / 3 + 5 || fruit.toado.x == Width / 2 + 5)
			{
				if ((fruit.toado.y >= Height / 4 && fruit.toado.y <= Height / 4 + 5) || (fruit.toado.y >= Height / 2 + 5 && fruit.toado.y <= Height - 10))
					flag = 1;
			}
		}
		//Map 3
		if (map == 3) {
			if (fruit.toado.x == Width / 2 - 10 || fruit.toado.x == Width / 2 + 10) {
				if (fruit.toado.y >= Height / 2 - 10 && fruit.toado.y <= Height / 2 + 10)
					flag = 1;
			}
		}
		//Map 4
		if (map == 4) {
			if (fruit.toado.y == Height / 4)
			{
				if (fruit.toado.x >= Width / 3 && fruit.toado.x <= Width / 3 + 5)
					flag = 1;
			}
			if (fruit.toado.y == Height / 4 * 3)
			{
				if (fruit.toado.x >= Width / 2 + 5 && fruit.toado.x <= Width / 3 * 2)
					flag = 1;
			}
			if (fruit.toado.x == Width / 3)
			{
				if (fruit.toado.y >= Height / 4 && fruit.toado.y <= Height / 4 + 5)
					flag = 1;
			}
			if (fruit.toado.x == Width / 3 * 2)
			{
				if (fruit.toado.y >= Height / 2 + 5 && fruit.toado.y <= Height - 10)
					flag = 1;
			}

		}
		//Map 5
		if (map == 5) {
			if (fruit.toado.y == Height / 4 + 5){
				if (fruit.toado.x >= Width / 3 && fruit.toado.x <= Width / 3 + 5)
					flag = 1;
			}
			if (fruit.toado.y == Height / 2 + 5) {
				if (fruit.toado.x >= Width / 2 + 5 && fruit.toado.x <= Width / 3 * 2)
					flag = 1;
			}
			if (fruit.toado.x == Width / 2 + 5) {
				if (fruit.toado.y >= Height / 2 + 5 && fruit.toado.y <= Height - 10)
					flag = 1;
			}
			if (fruit.toado.x == Width / 3 + 5) {
				if (fruit.toado.y >= Height / 4 && fruit.toado.y <= Height / 4 + 5)
					flag = 1;
			}

		}
		if (fruit.toado.x == 0 && fruit.toado.y == 0)
			flag = 1;
		//Gate
		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				if (fruit.toado.x == Width / 2 + i || fruit.toado.y == 10 + j)
					flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
//Tạo chướng ngại vật
void createImpe() {
	if (numOfImpe == 1) {
		impe.toado.x = Width / 2;
		impe.toado.y = 2;
		impe.sta = UP;
	}
	else if (numOfImpe == 2) {
		impe.toado.x = Width / 2 - Width / 4;
		impe.toado.y = 2;
		impe.sta = DOWN;

		impe2.toado.x = Width / 2 + Width / 4;
		impe2.toado.y = Height - 1;
		impe2.sta = UP;
	}
	else if (numOfImpe == 3) {
		impe.toado.x = Width / 2 - Width / 3 + 1;
		impe.toado.y = 2;
		impe.sta = DOWN;

		impe2.toado.x = Width / 2;
		impe2.toado.y = Height / 2;
		impe2.sta = UP;

		impe3.toado.x = Width / 2 + Width / 3;
		impe3.toado.y = Height - 1;
		impe3.sta = UP;
	}
}

//Thông tin người chơi trong game
void displayInfo(Level level) {

	TextColor(ColorTable);
	gotoXY(Width + 10, 1);
	printf("LEVEL: ");

	if (level == EASY) {
		TextColor(ColorCode_Green);
		puts("EASY");
	}
	else if (level == NORMAL) {
		TextColor(ColorCode_Yellow);
		puts("NORMAL");
	}
	else if (level == HARD) {
		TextColor(ColorCode_Red);
		puts("HARD");
	}
	else if (level == CUSTOM) {
		TextColor(ColorCode_Grey);
		puts("CUSTOM");
	}

	TextColor(ColorTable);
	gotoXY(Width + 5, 3);
	printf("PLAYER 1'S SCORE: ");

	TextColor(ColorSnake);
	printf("%d", snake.score);

	if (numOfSnake == 2) {
		TextColor(ColorTable);
		gotoXY(Width + 5, 5);
		printf("PLAYER 2'S SCORE: ");

		TextColor(ColorSnake2);
		printf("%d", snake2.n - 5);

	}
}

//Function hiện thông tin chính
void display() {
	displayInfo(level);
	//snake 1
	TextColor(ColorSnake);
	for (int i = 2; i < snake.n; i++) {
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		cout << MSSV[i - 2];
	}
	gotoXY(snake.dot[snake.n - 1].x, snake.dot[snake.n - 1].y);
	putchar(' ');
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar(Head);
	gotoXY(snake.dot[1].x, snake.dot[1].y);
	cout << "*";

	// snake 2
	if (numOfSnake == 2) {
		TextColor(ColorSnake2);
		for (int i = 2; i < snake2.n; i++) {
			gotoXY(snake2.dot[i].x, snake2.dot[i].y);
			cout << TEN[i - 2];
		}
		gotoXY(snake2.dot[snake2.n - 1].x, snake2.dot[snake2.n - 1].y);
		putchar(' ');
		gotoXY(snake2.dot[0].x, snake2.dot[0].y);
		putchar(Head);
		gotoXY(snake2.dot[1].x, snake2.dot[1].y);
		cout << "*";
	}
	if (MODE == 2) {
		TextColor(ColorCode_Red);
		gotoXY(impe.toado.x, impe.toado.y);
		putchar(Impediment);
		if (numOfImpe >= 2) {
			gotoXY(impe2.toado.x, impe2.toado.y);
			putchar(Impediment);
		}
		if (numOfImpe == 3) {
			gotoXY(impe3.toado.x, impe3.toado.y);
			putchar(Impediment);
		}
	}
}

//Vẽ tường
void displayWall() {
	TextColor(ColorWall);
	for (int i = 0; i <= Height; i++) {
		gotoXY(Width, i);
		putchar(WallEdge);
		gotoXY(0, i);
		putchar(WallEdge);
	}
	for (int i = 0; i <= Width; i++) {
		gotoXY(i, 0);
		putchar(WallTop);
		gotoXY(i, Height);
		putchar(WallBottom);
	}
}
void howtoplay() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(15);
	//Vẽ 2 bên tường
	gotoXY(Width + 13, Height / 4 + 1);	 cout << u8"██████████████████████████████████████████████████████████████";
	gotoXY(Width + 13, Height / 4 + 2);  cout << u8"█╔═══════════════════════════════════════════════════════════█╗";
	gotoXY(Width + 13, Height / 4 + 3);  cout << u8"█║       ┏     ┓                               ┏     ┓       █║";
	gotoXY(Width + 13, Height / 4 + 4);  cout << u8"█║          W                                     ▲          █║";
	gotoXY(Width + 13, Height / 4 + 5);  cout << u8"█║        A ♥ D                                 ◄ ♥ ►        █║";
	gotoXY(Width + 13, Height / 4 + 6);  cout << u8"█║          S                                     ▼          █║";
	gotoXY(Width + 13, Height / 4 + 7);  cout << u8"█║       ┗     ┛                               ┗     ┛       █║";
	gotoXY(Width + 13, Height / 4 + 8);  cout << u8"█║                                                           █║";
	gotoXY(Width + 13, Height / 4 + 9);  cout << u8"█║                   __  ___   _    __  ___                  █║";
	gotoXY(Width + 13, Height / 4 + 10); cout << u8"█║                  / _|| o \\ / \\  / _|| __|                 █║";
	gotoXY(Width + 13, Height / 4 + 11); cout << u8"█║                  \\_ \\|  _/| o |( (_ | _|                  █║";
	gotoXY(Width + 13, Height / 4 + 12); cout << u8"█║                  |__/|_|  |_n_| \\__||___|                 █║";
	gotoXY(Width + 13, Height / 4 + 13); cout << u8"█║                                                           █║";
	gotoXY(Width + 13, Height / 4 + 14); cout << u8"█║                  ████████████████████████                 █║";
	gotoXY(Width + 13, Height / 4 + 15); cout << u8"█║                  █                      █                 █║";
	gotoXY(Width + 13, Height / 4 + 16); cout << u8"█║                                                           █║";
	gotoXY(Width + 13, Height / 4 + 17); cout << u8"██████████████████████████████████████████████████████████████║";
	gotoXY(Width + 13, Height / 4 + 18); cout << u8" ╚════════════════════════════════════════════════════════════╝";

	TextColor(15);
	gotoXY(Width + 6, Height / 2 + 10); cout << u8" _____    _______  __  __  _______     _______  _______  _______  ______  _______";
	gotoXY(Width + 6, Height / 2 + 11); cout << u8"|     |_ |_     _||  |/  ||    ___|   |     __||   |   ||   _   ||   __ \\|    ___|";
	gotoXY(Width + 6, Height / 2 + 12); cout << u8"|       | _|   |_ |     < |    ___|   |__     ||       ||       ||      <|    ___|";
	gotoXY(Width + 6, Height / 2 + 13); cout << u8"|_______||_______||__|\\__||_______|   |_______||___|___||___|___||___|__||_______|";
	SetConsoleOutputCP(old_cp);
}
void cleanhow() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 35; j++) {
			gotoXY(Width + 6 + i, Height / 4 + j);
			cout << " ";
		}
	}
}

//Tạo map
void Map1() //Map thu nhat
{
	TextColor(ColorWall);
	for (int i = Width / 3; i <= Width / 3 + 5; i++) {
		gotoXY(i, Height / 4);
		putchar(WallTop);
		gotoXY(i, Height / 4 * 3);
		putchar(WallTop);
	}
	for (int i = Width / 2 + 5; i <= Width / 3 * 2; i++) {
		gotoXY(i, Height / 4);
		putchar(WallTop);
		gotoXY(i, Height / 4 * 3);
		putchar(WallTop);
	}
	for (int i = Height / 4; i <= Height / 4 + 5; i++) {
		gotoXY(Width / 3, i);
		putchar(WallEdge);
		gotoXY(Width / 3 * 2, i);
		putchar(WallEdge);
	}
	for (int i = Height / 2 + 5; i <= Height - 10; i++) {
		gotoXY(Width / 3, i);
		putchar(WallEdge);
		gotoXY(Width / 3 * 2, i);
		putchar(WallEdge);
	}
}
void Map2() //Map thu 2
{
	TextColor(ColorWall);
	for (int i = Height / 4; i <= Height / 4 + 5; i++)
	{
		gotoXY(Width / 3 + 5, i);
		putchar(WallEdge);
		gotoXY(Width / 2 + 5, i);
		putchar(WallEdge);
	}
	for (int i = Height / 2 + 5; i <= Height - 10; i++)
	{
		gotoXY(Width / 3 + 5, i);
		putchar(WallEdge);
		gotoXY(Width / 2 + 5, i);
		putchar(WallEdge);
	}
	for (int i = Width / 3; i <= Width / 3 + 5; i++)
	{
		gotoXY(i, Height / 4 + 5);
		putchar(WallEdge);
		gotoXY(i, Height / 2 + 5);
		putchar(WallEdge);
	}
	for (int i = Width / 2 + 5; i <= Width / 3 * 2; i++)
	{
		gotoXY(i, Height / 4 + 5);
		putchar(WallEdge);
		gotoXY(i, Height / 2 + 5);
		putchar(WallEdge);
	}
}
void Map3() {
	TextColor(ColorWall);
	for (int i = Height / 2 - 10; i <= Height / 2 + 10; i++) {
		gotoXY(Width / 2 - 10, i);
		putchar(WallEdge);
	}
	for (int i = Height / 2 - 10; i <= Height / 2 + 10; i++) {
		gotoXY(Width / 2 + 10, i);
		putchar(WallEdge);
	}
}
void Map4() {
	TextColor(ColorWall);
	for (int i = Width / 3; i <= Width / 3 + 5; i++) {
		gotoXY(i, Height / 4);
		putchar(WallBottom);
	}
	for (int i = Width / 2 + 5; i <= Width / 3 * 2; i++) {
		gotoXY(i, Height / 4 * 3);
		putchar(WallTop);
	}
	for (int i = Height / 4; i <= Height / 4 + 5; i++) {
		gotoXY(Width / 3, i);
		putchar(WallEdge);
	}
	for (int i = Height / 2 + 5; i <= Height - 10; i++) {
		gotoXY(Width / 3 * 2, i);
		putchar(WallEdge);
	}
}
void Map5()
{
	TextColor(ColorWall);
	for (int i = Height / 4; i <= Height / 4 + 5; i++)
	{
		gotoXY(Width / 3 + 5, i);
		putchar(WallEdge);
	}
	for (int i = Height / 2 + 5; i <= Height - 10; i++)
	{
		gotoXY(Width / 2 + 5, i);
		putchar(WallEdge);
	}
	for (int i = Width / 3; i <= Width / 3 + 5; i++)
	{
		gotoXY(i, Height / 4 + 5);
		putchar(WallEdge);
	}
	for (int i = Width / 2 + 5; i <= Width / 3 * 2; i++)
	{
		gotoXY(i, Height / 2 + 5);
		putchar(WallEdge);
	}
}
void createMap() {
	switch (map) {
	case 1:
		Map1();
		break;

	case 2:
		Map2();
		break;
	case 3:
		Map3();
		break;
	case 4:
		Map4();
		break;
	case 5:
		Map5();
		break;
	}
}

//Save game
void saveGame(const char* path, int count, int flag) {
	ofstream out;
	out.open(path, ios::out);
	out << count << " " << flag << " " << level << "\n";
	out << fruit.toado.x << " " << fruit.toado.y << "\n";
	out << snake.n << " " << snake.score << " " << snake.sta << "\n";
	out << map << " " << TIME << "\n\n";
	for (int i = 0; i < snake.n; i++) {
		out << snake.dot[i].x << " " << snake.dot[i].y << "\n";
	}
	out.close();
}
//Load game
void loadGame(const char* path, int& count, int& flag) {
	ifstream in;
	int sta, lv;
	in.open(path, ios::in);
	in >> count >> flag >> lv >> fruit.toado.x >> fruit.toado.y;
	in >> snake.n >> snake.score >> sta;
	switch (sta) {
	case 0:
		snake.sta = UP;
		break;
	case 1:
		snake.sta = DOWN;
		break;
	case 2:
		snake.sta = LEFT;
		break;
	case 3:
		snake.sta = RIGHT;
		break;
	}
	switch (lv) {
	case 20:
		level = HARD;
		break;
	case 25:
		level = NORMAL;
		break;
	case 30:
		level = EASY;
		break;
	}
	in >> map >> TIME;
	for (int i = 0; i < snake.n; i++) {
		in >> snake.dot[i].x >> snake.dot[i].y;
	}
	in.close();
	if (flag == 0) {
		TextColor(ColorFruit);
		gotoXY(fruit.toado.x, fruit.toado.y);
		putchar(Fruit);
	}
}

//Menu game
int Menu(int& choose, int option) {
	int key = 0;
	int leng = len + 5;
	while (key != 13) {
		for (int i = 0; i < option * 2; i += 2) {
			gotoXY(Width / 2 - leng, Height / 2 - 4 + i);
			cout << ' ';
		}
		if ((key == 'w' || key == 'W' || key == 72) && choose > 1) {
			OnOffEffectSound(sound.updown, 3);
			choose--;
		}
		else if ((key == 's' || key == 'S' || key == 80) && choose < option) {
			OnOffEffectSound(sound.updown, 3);
			choose++;
		}

		for (int i = 0; i <= option * 2; i += 2) {
			if (choose == i / 2 + 1) {
				gotoXY(Width / 2 - leng, Height / 2 - 4 + i);
				putchar(175);
			}
		}
		key = _getch();
		OnOffEffectSound(sound.Enter, 4);
	}
	return choose;
}
int MenuThem(int& choose, int option) {
	int key = 0;
	int leng = len + 5;
	while (key != 13) {
		for (int i = 0; i < option * 2; i += 2) {
			gotoXY(Width / 2 - leng, Height / 2 + i);
			cout << ' ';
		}
		if ((key == 'w' || key == 'W' || key == 72) && choose > 1) {
			OnOffEffectSound(sound.updown, 3);
			choose--;
		}
		else if ((key == 's' || key == 'S' || key == 80) && choose < option) {
			OnOffEffectSound(sound.updown, 3);
			choose++;
		}

		for (int i = 0; i <= option * 2; i += 2) {
			if (choose == i / 2 + 1) {
				gotoXY(Width / 2 - leng, Height / 2 + i);
				putchar(175);
			}
		}
		key = _getch();
		OnOffEffectSound(sound.Enter, 4);
	}
	return choose;
}
void MenuAdd() {
	TextColor(14);
	for (int i = 0; i <= 18; i++) {
		gotoXY(Width, Height / 2 - 10 + i);
		putchar(WallEdge);
		gotoXY(0, Height / 2 - 10 + i);
		putchar(WallEdge);
	}
	for (int i = 0; i <= Width; i++) {
		gotoXY(i, Height / 2 - 10);
		putchar(WallTop);
		gotoXY(i, Height / 2 + 8);
		putchar(WallBottom);
	}
	TextColor(4);
	for (int i = 1; i < 18; i++) {
		for (int j = 1; j < Width; j++) {
			gotoXY(j, Height / 2 - 10 + i);
			cout << " ";
		}
	}
}
void cleanMenu() {
	TextColor(7);
	for (int i = 0; i <= 18; i++) {
		for (int j = 0; j <= Width; j++) {
			gotoXY(j, Height / 2 - 10 + i);
			cout << " ";
		}
	}
}

//Kết thúc lượt game
void displayOver(int over) {
	if (over == -1) {
		TextColor(14);
		OnOffEffectSound(sound.over, 2);
		dynamicText("GAME OVER !!!");
		if (MODE == 3)
			MODE = 1;
	}
	else if (over == 1) {
		TextColor(14);
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		dynamicText("YOU WON !!!");
	}
	else if (over == 2) {
		TextColor(ColorSnake2);
		dynamicText("PLAYER 2 WON !!!");
		OnOffEffectSound(sound.over, 2);
	}
	else if (over == -2) {
		TextColor(ColorSnake);
		dynamicText("PLAYER 1 WON !!!");
		OnOffEffectSound(sound.over, 2);
	}
	else if (over == 3) {
		TextColor(ColorCode_Cyan);
		dynamicText("MATCH DRAW !!!");
		OnOffEffectSound(sound.over, 2);
	}
	else if (over == -3) {
		TextColor(ColorCode_Cyan);
		dynamicText("END GAME !!!");
		OnOffEffectSound(sound.over, 2);
	}
}
//Di chuyển
void controlMove() {
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];

	for (int i = snake2.n - 1; i > 0; i--)
		snake2.dot[i] = snake2.dot[i - 1];

	if (_kbhit()) {
		int key = _getch();

		//snake 1
		if ((key == 'w' || key == 'W') && snake.sta != DOWN)
			snake.sta = UP;
		else if ((key == 's' || key == 'S') && snake.sta != UP)
			snake.sta = DOWN;
		else if ((key == 'd' || key == 'D') && snake.sta != LEFT)
			snake.sta = RIGHT;
		else if ((key == 'a' || key == 'A') && snake.sta != RIGHT)
			snake.sta = LEFT;
		else if (key == ' ') {
			int choose = 1;
			MenuAdd();
			TextColor(14);
			gotoXY(Width / 2 - 25, Height / 2 - 8);    cout << "__________  _____   ____ ___  ____________________" << endl;
			gotoXY(Width / 2 - 25, Height / 2 - 7);	cout << "\\______   \\/  _  \\ |    |   \\/   _____/\\_   _____/" << endl;
			gotoXY(Width / 2 - 25, Height / 2 - 6);	cout << " |     ___/  /_\\  \\|    |   /\\_____  \\  |    __)_ " << endl;
			gotoXY(Width / 2 - 25, Height / 2 - 5);	cout << " |    |  /    |    \\    |  / /        \\ |        \\" << endl;
			gotoXY(Width / 2 - 25, Height / 2 - 4);	cout << " |____|  \\____|__  /______/ /_______  //_______  /" << endl;
			gotoXY(Width / 2 - 25, Height / 2 - 3);	cout << "                 \\/                 \\/         \\/ " << endl;
			if (numOfSnake == 2 || MODE == 2) {
				gotoXY(Width / 2 - len, Height / 2);
				puts("RESUME");
				gotoXY(Width / 2 - len, Height / 2 + 2);
				puts("EXIT");
				choose = MenuThem(choose, 2);
				switch (choose) {
				case 1:
					cleanMenu();
					system("cls");
					displayWall();
					trafficLight();
					TextColor(ColorFruit);
					gotoXY(fruit.toado.x, fruit.toado.y);
					putchar(Fruit);
					break;
				case 2:
					over = -3;
					cleanMenu();
					displayWall();
					break;
				}
			}
			else {
				gotoXY(Width / 2 - len, Height / 2 + 2);
				puts("SAVE GAME");
				gotoXY(Width / 2 - len, Height / 2);
				puts("RESUME");
				gotoXY(Width / 2 - len, Height / 2 + 4);
				puts("EXIT");
				choose = MenuThem(choose, 3);
				switch (choose) {
				case 1:
					cleanMenu();
					system("cls");
					displayWall();
					trafficLight();
					TextColor(ColorFruit);
					gotoXY(fruit.toado.x, fruit.toado.y);
					putchar(Fruit);
					break;
				case 2:
					cleanMenu();
					MenuAdd();
					choose = 1;
					TextColor(14);
					gotoXY(Width / 2 - 21, Height / 2 - 8);		cout << "  _________   _________   _______________" << endl;
					gotoXY(Width / 2 - 21, Height / 2 - 7);	    cout << " /   _____/  /  _  \\   \\ /   /\\_   _____/" << endl;
					gotoXY(Width / 2 - 21, Height / 2 - 6);	    cout << " \\_____  \\  /  /_\\  \\   Y   /  |    __)_" << endl;
					gotoXY(Width / 2 - 21, Height / 2 - 5);		cout << " /        \\/    |    \\     /   |        \\ " << endl;
					gotoXY(Width / 2 - 21, Height / 2 - 4);		cout << "/_______  /\\____|__  /\\___/   /_______  /" << endl;
					gotoXY(Width / 2 - 21, Height / 2 - 3);	    cout << "        \\/         \\/                 \\/ " << endl;
					gotoXY(Width / 2 - len, Height / 2);
					puts("SAVE GAME 1");
					gotoXY(Width / 2 - len, Height / 2 + 2);
					puts("SAVE GAME 2");
					gotoXY(Width / 2 - len, Height / 2 + 4);
					puts("SAVE GAME 3");
					choose = MenuThem(choose, 3);
					switch (choose) {
					case 1:
						saveGame(save1, countFruit, flag);
						cleanMenu();
						TextColor(ColorFruit);
						gotoXY(fruit.toado.x, fruit.toado.y);
						putchar(Fruit);
						break;
					case 2:
						saveGame(save2, countFruit, flag);
						cleanMenu();
						TextColor(ColorFruit);
						gotoXY(fruit.toado.x, fruit.toado.y);
						putchar(Fruit);
						break;
					case 3:
						saveGame(save3, countFruit, flag);
						cleanMenu();
						TextColor(ColorFruit);
						gotoXY(fruit.toado.x, fruit.toado.y);
						putchar(Fruit);
						break;
					}
					break;
				case 3:
					over = -3;
					cleanMenu();
					displayWall();
					break;
				}
			}
		}

		//snake 2
		if (numOfSnake == 2) {
			if ((key == 72) && snake2.sta != DOWN)
				snake2.sta = UP;
			else if ((key == 80) && snake2.sta != UP)
				snake2.sta = DOWN;
			else if ((key == 77) && snake2.sta != LEFT)
				snake2.sta = RIGHT;
			else if ((key == 75) && snake2.sta != RIGHT)
				snake2.sta = LEFT;
		}
	}
	//snake 1

	if (snake.dot[0].x != gate.thanh[0].x || snake.dot[0].y != gate.thanh[0].y) {
		if (snake.sta == UP)
			snake.dot[0].y--;
		else if (snake.sta == DOWN)
			snake.dot[0].y++;
		else if (snake.sta == LEFT)
			snake.dot[0].x--;
		else if (snake.sta == RIGHT)
			snake.dot[0].x++;
	}

	//snake 2
	if (numOfSnake == 2) {
		if (snake2.sta == UP)
			snake2.dot[0].y--;
		else if (snake2.sta == DOWN)
			snake2.dot[0].y++;
		else if (snake2.sta == LEFT)
			snake2.dot[0].x--;
		else if (snake2.sta == RIGHT)
			snake2.dot[0].x++;
	}
	// impe
	if (MODE == 2) {
		gotoXY(impe.toado.x, impe.toado.y);
		cout << " ";
		if (impe.sta == UP)
			impe.toado.y--;
		else if (impe.sta == DOWN)
			impe.toado.y++;
		else if (impe.sta == LEFT)
			impe.toado.x--;
		else if (impe.sta == RIGHT)
			impe.toado.x++;

		if (numOfImpe >= 2) {

			gotoXY(impe2.toado.x, impe2.toado.y);
			cout << " ";
			if (impe2.sta == UP)
				impe2.toado.y--;
			else if (impe2.sta == DOWN)
				impe2.toado.y++;
			else if (impe2.sta == LEFT)
				impe2.toado.x--;
			else if (impe2.sta == RIGHT)
				impe2.toado.x++;
		}
		if (numOfImpe == 3) {
			gotoXY(impe3.toado.x, impe3.toado.y);
			cout << " ";
			if (impe3.sta == UP)
				impe3.toado.y--;
			else if (impe3.sta == DOWN)
				impe3.toado.y++;
			else if (impe3.sta == LEFT)
				impe3.toado.x--;
			else if (impe3.sta == RIGHT)
				impe3.toado.x++;
		}
	}
}
//Chạm map
bool touchMap1()
{
	if (snake.dot[0].y == Height / 4 || snake.dot[0].y == Height / 4 * 3)
	{
		if ((snake.dot[0].x >= Width / 3 && snake.dot[0].x <= Width / 3 + 5) || (snake.dot[0].x >= Width / 2 + 5 && snake.dot[0].x <= Width / 3 * 2))
			return true;
	}
	if (snake.dot[0].x == Width / 3 || snake.dot[0].x == Width / 3 * 2)
	{
		if ((snake.dot[0].y >= Height / 4 && snake.dot[0].y <= Height / 4 + 5) || snake.dot[0].y >= Height / 2 + 5 && snake.dot[0].y <= Height - 10)
			return true;
	}
	return false;
}
bool touchMap2()
{
	if (snake.dot[0].y == Height / 4 + 5 || snake.dot[0].y == Height / 2 + 5)
	{
		if ((snake.dot[0].x >= Width / 3 && snake.dot[0].x <= Width / 3 + 5) || (snake.dot[0].x >= Width / 2 + 5 && snake.dot[0].x <= Width / 3 * 2))
			return true;
	}
	if (snake.dot[0].x == Width / 3 + 5 || snake.dot[0].x == Width / 2 + 5)
	{
		if ((snake.dot[0].y >= Height / 4 && snake.dot[0].y <= Height / 4 + 5) || snake.dot[0].y >= Height / 2 + 5 && snake.dot[0].y <= Height - 10)
			return true;
	}
	return false;
}
bool touchMap3() {

	if (snake.dot[0].x == Width / 2 - 10 || snake.dot[0].x == Width / 2 + 10) {
		if ((snake.dot[0].y >= Height / 2 - 10 && snake.dot[0].y <= Height / 2 + 10))
			return true;
	}
	return false;
}
bool touchMap4() {
	if (snake.dot[0].y == Height / 4) {
		if ((snake.dot[0].x >= Width / 3 && snake.dot[0].x <= Width / 3 + 5))
			return true;
	}
	if (snake.dot[0].y == Height / 4 * 3) {
		if ((snake.dot[0].x >= Width / 2 + 5 && snake.dot[0].x <= Width / 3 * 2))
			return true;
	}
	if (snake.dot[0].x == Width / 3) {
		if ((snake.dot[0].y >= Height / 4 && snake.dot[0].y <= Height / 4 + 5))
			return true;
	}
	if (snake.dot[0].x == Width / 3 * 2) {
		if ((snake.dot[0].y >= Height / 2 + 5 && snake.dot[0].y <= Height - 10))
			return true;
	}
	return false;
}
bool touchMap5() {
	if (snake.dot[0].y == Height / 4 + 5) {
		if ((snake.dot[0].x >= Width / 3 && snake.dot[0].x <= Width / 3 + 5))
			return true;
	}
	if (snake.dot[0].y == Height / 2 + 5) {
		if ((snake.dot[0].x >= Width / 2 + 5 && snake.dot[0].x <= Width / 3 * 2))
			return true;
	}
	if (snake.dot[0].x == Width / 2 + 5) {
		if (snake.dot[0].y >= Height / 2 + 5 && snake.dot[0].y <= Height - 10)
			return true;
	}
	if (snake.dot[0].x == Width / 3 + 5) {
		if (snake.dot[0].y >= Height / 4 && snake.dot[0].y <= Height / 4 + 5)
			return true;
	}
	return false;
}

//Thao tác rắn khi đang chơi
int handling(int& count, int mode) {
	//Ăn đồ ăn
	if (snake.dot[0].x == fruit.toado.x && snake.dot[0].y == fruit.toado.y) {
		snake.dot[snake.n] = snake.dot[snake.n - 1];
		snake.n++;
		snake.score++;

		TextColor(ColorFruit);
		gotoXY(fruit.toado.x, fruit.toado.y);
		putchar(Fruit);
		createFruit();

		if (count <= 1 && numOfSnake == 1) {
			count++;
			createFruit();
			TextColor(ColorFruit);
			gotoXY(fruit.toado.x, fruit.toado.y);
			putchar(Fruit);
		}
		OnOffEffectSound(sound.eat, 1);
		if (MODE == 2) {
			TIME -= 3;
		}
	}

	if (numOfSnake == 2) {
		if (snake2.dot[0].x == fruit.toado.x && snake2.dot[0].y == fruit.toado.y) {
			snake2.dot[snake2.n] = snake2.dot[snake2.n - 1];
			snake2.n++;
			OnOffEffectSound(sound.eat, 1);
			createFruit();
			TextColor(ColorFruit);
			gotoXY(fruit.toado.x, fruit.toado.y);
			putchar(Fruit);
		}
	}
	if (MODE == 2) {
		//Chướng ngại vật khi chạm biên
		if (impe.toado.y >= Height - 1) {
			impe.sta = UP;
		}
		else if (impe.toado.y <= 1) {
			impe.sta = DOWN;
		}
		if (numOfImpe >= 2) {
			if (impe2.toado.y >= Height - 1) {
				impe2.sta = UP;
			}
			else if (impe2.toado.y <= 1) {
				impe2.sta = DOWN;
			}
		}
		if (numOfImpe == 3) {
			if (impe3.toado.y >= Height - 1) {
				impe3.sta = UP;
			}
			else if (impe3.toado.y <= 1) {
				impe3.sta = DOWN;
			}
		}
	}
	switch (numOfSnake) {
	case 1:
		//Chạm tường khi trả về -1
		if (snake.dot[0].x <= 0 || snake.dot[0].x >= Width || snake.dot[0].y >= Height || snake.dot[0].y <= 0 || (map == 1 && touchMap1() == true) || (map == 2 && touchMap2() == true) || (map == 3 && touchMap3() == true) || (map == 4 && touchMap4() == true) || (map == 5 && touchMap5() == true))
			return -1;
		for (int i = 1; i < 7; i++) {
			if (snake.dot[0].x == gate.thanh[i].x && snake.dot[0].y == gate.thanh[i].y)
				return -1;
		}
		//Chạm thân khi trả về -1
		for (int i = 4; i < snake.n; i++) {
			if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				return -1;
		}
		if (MODE == 2) {
			//Win game khi trả về 1
			if (snake.n == level)
				return 1;
			//Chạm chướng ngại vật khi trả về -1
			for (int i = 0; i < snake.n - 1; i++) {
				if (snake.dot[i].x == impe.toado.x && snake.dot[i].y == impe.toado.y)
					return -1;
			}
			if (numOfImpe >= 2) {
				//Chạm chướng ngại vật khi trả về -1
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe2.toado.x && snake.dot[i].y == impe2.toado.y)
						return -1;
				}
			}
			if (numOfImpe == 3) {
				//Chạm chướng ngại vật khi trả về -1
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe3.toado.x && snake.dot[i].y == impe3.toado.y)
						return -1;
				}
			}
		}
		return 0;
	case 2:
		//Xử lí chạm thân và chạm tường
		//Chạm tường, thân trả về -2
		if (snake.dot[0].x <= 0 || snake.dot[0].x >= Width || snake.dot[0].y >= Height || snake.dot[0].y <= 0)
			return 2;
		if (snake2.dot[0].x <= 0 || snake2.dot[0].x >= Width || snake2.dot[0].y >= Height || snake2.dot[0].y <= 0)
			return -2;

		for (int i = 4; i < snake.n; i++) {
			if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				return 2;
		}
		for (int i = 4; i < snake2.n; i++) {
			if (snake2.dot[0].x == snake2.dot[i].x && snake2.dot[0].y == snake2.dot[i].y)
				return -2;
		}

		//Chạm nhau
		//Trả về -2 khi rắn 1 thắng, 2 khi rắn 2 thắng. chạm đầu nhau trả về 3
		for (int i = 1; i < snake.n - 1; i++) {
			if (snake2.dot[0].x == snake.dot[i].x && snake2.dot[0].y == snake.dot[i].y)
				return -2;
		}
		for (int i = 1; i < snake2.n - 1; i++) {
			if (snake.dot[0].x == snake2.dot[i].x && snake.dot[0].y == snake2.dot[i].y)
				return 2;
		}
		if ((snake.dot[0].x == snake2.dot[0].x && snake.dot[0].y == snake2.dot[0].y))
			return 3;

		if (MODE == 2) {
			//Thắng
			if (snake.n == level)
				return -2;
			else if (snake2.n == level)
				return 2;
			//Chạm chướng ngại vật
			for (int i = 0; i < snake.n - 1; i++) {
				if (snake.dot[i].x == impe.toado.x && snake.dot[i].y == impe.toado.y)
					return 2;
			}
			for (int i = 0; i < snake2.n - 1; i++) {
				if (snake2.dot[i].x == impe.toado.x && snake2.dot[i].y == impe.toado.y)
					return -2;
			}
			if (numOfImpe >= 2) {
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe2.toado.x && snake.dot[i].y == impe2.toado.y)
						return 2;
				}
				for (int i = 0; i < snake2.n - 1; i++) {
					if (snake2.dot[i].x == impe2.toado.x && snake2.dot[i].y == impe2.toado.y)
						return -2;
				}
			}
			if (numOfImpe == 3) {
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe3.toado.x && snake.dot[i].y == impe3.toado.y)
						return 2;
				}
				for (int i = 0; i < snake2.n - 1; i++) {
					if (snake2.dot[i].x == impe3.toado.x && snake2.dot[i].y == impe3.toado.y)
						return -2;
				}
			}
		}
	}
	return 0;
}

//Đọc file highscore
void readInfo() {
	info = fopen("Player Info.txt", "r");
	if (info != NULL) {
		for (int i = 0; i < MAXPLAYER - 1; i++) {
			fgets(player[i].name, 14, info);
			fscanf(info, "%d", &player[i].score);
			fseek(info, 2, SEEK_CUR);
		}
		fclose(info);
	}
	else puts("FILE ERROR !");

	// sort
	for (int i = 0; i < MAXPLAYER - 1; i++) {
		for (int j = i; j < MAXPLAYER - 1; j++) {
			if (player[j].score > player[i].score) {
				player[10] = player[j];
				player[j] = player[i];
				player[i] = player[10];
			}
		}
	}

}
//Để tên và điểm người chơi
void printInfo() {
	for (int i = 0, j = 0; i < MAXPLAYER - 1; i++, j += 2) {
		gotoXY(Width / 2 - 2 * len - 2, Height / 2 - 9 + j);
		printf("%2d. %-13s\t%d", i + 1, player[i].name, player[i].score);
	}
}
//Update tên người điểm cao trong file
void updateInfo() {
	info = fopen("Player Info.txt", "w+");
	if (info != NULL) {
		for (int i = 0; i < MAXPLAYER - 1; i++) {
			fprintf(info, "%13s%d\n", player[i].name, player[i].score);
		}
		fclose(info);
	}
	else puts("FILE ERROR !");
}
//Đặt tên sau khi thua
void testScore() {
	int i;
	char tmp[100];
	clrscr();
	hidePointer();
	displayWall();
	for (i = 0; i < 10; i++) {
		if (snake.score >= player[i].score) {
			fflush(stdin);
			gotoXY(Width / 2 - 3 * len, Height / 2 - 3);
			cout << "PLEASE ENTER YOUR NAME: ";
			gotoXY(Width / 2 - 2 - len, Height / 2 - 1);
			gets_s(tmp);

			strncpy(player[9].name, tmp, 13);
			player[9].score = snake.score;
			for (int i = 0; i < MAXPLAYER - 1; i++) {
				for (int j = i; j < MAXPLAYER - 1; j++) {
					if (player[j].score > player[i].score) {
						player[10] = player[j];
						player[j] = player[i];
						player[i] = player[10];
					}
				}
			}
			break;
		}
	}
}

//Đồ họa
void OnOffColorLevel() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(10);
	gotoXY(Width / 2 - len + 11, Height / 2 - 4);
	cout << u8"●";
	TextColor(14);
	gotoXY(Width / 2 - len + 11, Height / 2 - 4 + 2);
	cout << u8"●";
	TextColor(12);
	gotoXY(Width / 2 - len + 11, Height / 2 - 4 + 4);
	cout << u8"●";
	TextColor(6);
	gotoXY(Width / 2 - len + 9, Height / 2 - 4 + 6);
	cout << u8"(♥_♥)";
	SetConsoleOutputCP(old_cp);
	TextColor(11);
}
void OnOffColorMode() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(10);
	gotoXY(Width / 2 - len + 11, Height / 2 - 4);
	cout << u8"(▀_▀)";
	TextColor(4);
	gotoXY(Width / 2 - len + 11, Height / 2 - 4 + 2);
	cout << u8"┌∩┐(▀v▀)┌∩┐";
	SetConsoleOutputCP(old_cp);
	TextColor(15);
}
void dynamicText(const char text[]) {
	//	display();

	while (1) {
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		puts(text);
		Sleep(250);
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		for (int i = 0; i < strlen(text); i++) {
			cout << " ";
		}
		Sleep(250);
		if (_kbhit()) {
			if (_getch() == 13)
				break;
		}
	}
}
void Loading() {
	int Count;
	for (int i = 0; i < defaultWidth / 2 + 2; i++) {
		gotoXY(defaultWidth / 4 - 1 + i, defaultHeight / 2 + 6);
		putchar(196);
		gotoXY(defaultWidth / 4 - 1 + i, defaultHeight / 2 + 8);
		putchar(196);
	}
	TextColor(10);
	gotoXY(defaultWidth / 4, defaultHeight / 2 + 7);
	for (Count = 0; Count < defaultWidth / 2; Count++) {
		cout << char(219);
		hidePointer();
		if (Count < 5) {
			Sleep(300);
		}
		else if (Count < 10) {
			Sleep(200);
		}
		else if (Count < defaultWidth / 2) {
			Sleep(150);
		}
	}
}
void Logo() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	for (int i = 2; i < 10; i++) {
		TextColor(i);
		gotoXY(defaultWidth / 2 - 25, defaultHeight / 2 - 7);  cout << u8"▄▄▄▄▄▄▄▄";
		gotoXY(defaultWidth / 2 - 25, defaultHeight / 2 - 6);  cout << u8"█       ";
		gotoXY(defaultWidth / 2 - 25, defaultHeight / 2 - 5);  cout << u8"█▄▄▄▄▄▄▄";
		gotoXY(defaultWidth / 2 - 25, defaultHeight / 2 - 4);  cout << u8"       █";
		gotoXY(defaultWidth / 2 - 25, defaultHeight / 2 - 3);  cout << u8"▄▄▄▄▄▄▄█";

		TextColor(i + 1);
		gotoXY(defaultWidth / 2 - 15, defaultHeight / 2 - 10); cout << u8"▄▄       ▄";
		gotoXY(defaultWidth / 2 - 15, defaultHeight / 2 - 9);  cout << u8"█ ▀▄     █";
		gotoXY(defaultWidth / 2 - 15, defaultHeight / 2 - 8);  cout << u8"█   ▀▄   █";
		gotoXY(defaultWidth / 2 - 15, defaultHeight / 2 - 7);  cout << u8"█     ▀▄ █";
		gotoXY(defaultWidth / 2 - 15, defaultHeight / 2 - 6);  cout << u8"█       ▀█";

		TextColor(i + 2);
		gotoXY(defaultWidth / 2 - 4, defaultHeight / 2 - 7);  cout << u8"    ▄▀▀▄    ";
		gotoXY(defaultWidth / 2 - 4, defaultHeight / 2 - 6);  cout << u8"   ▄▀  ▀▄   ";
		gotoXY(defaultWidth / 2 - 4, defaultHeight / 2 - 5);  cout << u8"  ▄▀▄▄▄▄▀▄  ";
		gotoXY(defaultWidth / 2 - 4, defaultHeight / 2 - 4);  cout << u8" ▄▀      ▀▄ ";
		gotoXY(defaultWidth / 2 - 4, defaultHeight / 2 - 3);  cout << u8"▄▀        ▀▄";

		TextColor(i + 3);
		gotoXY(defaultWidth / 2 + 8, defaultHeight / 2 - 10);  cout << u8"▄    ▄";
		gotoXY(defaultWidth / 2 + 8, defaultHeight / 2 - 9);   cout << u8"█ ▄▄▀   ";
		gotoXY(defaultWidth / 2 + 8, defaultHeight / 2 - 8);   cout << u8"█▀▄▄    ";
		gotoXY(defaultWidth / 2 + 8, defaultHeight / 2 - 7);   cout << u8"█   ▀▄  ";
		gotoXY(defaultWidth / 2 + 8, defaultHeight / 2 - 6);   cout << u8"█     ▀";

		TextColor(i + 4);
		gotoXY(defaultWidth / 2 + 18, defaultHeight / 2 - 7);  cout << u8"█▀▀▀▀▀▀▀  ";
		gotoXY(defaultWidth / 2 + 18, defaultHeight / 2 - 6);  cout << u8"█         ";
		gotoXY(defaultWidth / 2 + 18, defaultHeight / 2 - 5);  cout << u8"█■■■■■■■  ";
		gotoXY(defaultWidth / 2 + 18, defaultHeight / 2 - 4);  cout << u8"█         ";
		gotoXY(defaultWidth / 2 + 18, defaultHeight / 2 - 3);  cout << u8"█▄▄▄▄▄▄▄  ";
		Sleep(300);
	}

	SetConsoleOutputCP(old_cp);
}
void Top10() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	TextColor(6);  gotoXY(Width / 2 - 23, Height / 4 - 8);    cout << u8"████████╗ ██████╗ ██████╗ " << endl;
	TextColor(9);  gotoXY(Width / 2 - 23, Height / 4 - 7);    cout << u8"╚══██╔══╝██╔═══██╗██╔══██╗" << endl;
	TextColor(11); gotoXY(Width / 2 - 23, Height / 4 - 6);    cout << u8"   ██║   ██║   ██║██████╔╝" << endl;
	TextColor(12); gotoXY(Width / 2 - 23, Height / 4 - 5);    cout << u8"   ██║   ██║   ██║██╔═══╝ " << endl;
	TextColor(14); gotoXY(Width / 2 - 23, Height / 4 - 4);    cout << u8"   ██║   ╚██████╔╝██║     " << endl;
	TextColor(15); gotoXY(Width / 2 - 23, Height / 4 - 3);    cout << u8"   ╚═╝    ╚═════╝ ╚═╝     " << endl;
	TextColor(14);
	gotoXY(Width / 2 + 6, Height / 4 - 5);	cout << u8"  ▄▄  ▄▄▄▄▄";
	gotoXY(Width / 2 + 6, Height / 4 - 4);	cout << u8" ▄██  ██ ██";
	gotoXY(Width / 2 + 6, Height / 4 - 3);  cout << u8"  ██  ██ ██";
	gotoXY(Width / 2 + 6, Height / 4 - 2);  cout << u8"  ██  ██ ██";
	gotoXY(Width / 2 + 6, Height / 4 - 1);	cout << u8"  ▀▀  ▀▀▀▀▀";
	SetConsoleOutputCP(old_cp);
}
void SetColor(WORD color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void convertImage(const char* fname, int a, int b, int x, int y) {
	//const char * fname là tên file truyền vào
	//a là màu sắc của hình ảnh (0 < a < 255)
	//b là tốc độ xuất ảnh
	//x và y là tọa độ ảnh sẽ được xuất ra

	vector <int> A;
	A.push_back(a);				//Lựa chọn các số từ 1 - 255 sẽ tương ứng với mỗi màu sắc cho TOÀN BỘ bức ảnh
	int i = 0;
	SetColor(A.at(i++ % A.size()));

	ifstream file;
	file.open(fname, ios_base::in);
	string line;

	while (getline(file, line))
	{
		gotoXY(x, y);
		cout << line << endl;
		y++;
		Sleep(b);
	}
	SetColor(65);
	file.close();
}
void creatCompleteBar() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	SetColor(71);
	for (int i = 0; i < Width - 15; i++)	//Thanh ngang dưới
	{
		gotoXY((Width / 8) + i, Height + 7);
		cout << u8"█";
	}

	for (int i = 0; i < 4; i++)	//Thanh dọc trái
	{
		gotoXY(Width / 8, Height + i + 4);
		cout << u8"█";
	}

	for (int i = 0; i <= Width - 15; i++) //Thanh ngang trên
	{
		gotoXY((Width / 8) + i, Height + 3);
		cout << u8"█";
	}

	for (int i = 0; i < 4; i++)	//Thanh dọc phải
	{
		gotoXY(Width / 8 + Width - 15, Height + i + 4);
		cout << u8"█";
	}


	SetConsoleOutputCP(old_cp);
}
void trafficLight() {
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	//Ready
	PlaySound(TEXT("ready.wav"), NULL, SND_ASYNC);
	SetColor(13);
	gotoXY(Width / 4 - 1, Height / 2 - 6); cout << " _____                   _        ";
	gotoXY(Width / 4 - 1, Height / 2 - 5); cout << "|  __ \\                 | |       ";
	gotoXY(Width / 4 - 1, Height / 2 - 4); cout << "| |__) | ___   __ _   __| | _   _ ";
	gotoXY(Width / 4 - 1, Height / 2 - 3); cout << "|  _  / / _ \\ / _` | / _` || | | |";
	gotoXY(Width / 4 - 1, Height / 2 - 2); cout << "| | \\ \\|  __/| (_| || (_| || |_| |";
	gotoXY(Width / 4 - 1, Height / 2 - 1); cout << "|_|  \\_\\\\___| \\__,_| \\__,_| \\__, |";
	gotoXY(Width / 4 - 1, Height / 2 - 0); cout << "                             __/ |";
	gotoXY(Width / 4 - 1, Height / 2 + 1); cout << "                            |___/ ";

	Sleep(1000);

	SetColor(128);
	gotoXY(Width / 4 - 1, Height / 2 - 6); cout << " _____                   _        ";
	gotoXY(Width / 4 - 1, Height / 2 - 5); cout << "|  __ \\                 | |       ";
	gotoXY(Width / 4 - 1, Height / 2 - 4); cout << "| |__) | ___   __ _   __| | _   _ ";
	gotoXY(Width / 4 - 1, Height / 2 - 3); cout << "|  _  / / _ \\ / _` | / _` || | | |";
	gotoXY(Width / 4 - 1, Height / 2 - 2); cout << "| | \\ \\|  __/| (_| || (_| || |_| |";
	gotoXY(Width / 4 - 1, Height / 2 - 1); cout << "|_|  \\_\\\\___| \\__,_| \\__,_| \\__, |";
	gotoXY(Width / 4 - 1, Height / 2 - 0); cout << "                             __/ |";
	gotoXY(Width / 4 - 1, Height / 2 + 1); cout << "                            |___/ ";

	//Số 3
	PlaySound(TEXT("count.wav"), NULL, SND_ASYNC);
	SetColor(228);
	gotoXY(Width / 2 - 4, Height / 2 - 3); cout << " ____  ";
	gotoXY(Width / 2 - 4, Height / 2 - 2); cout << "|___ \\ ";
	gotoXY(Width / 2 - 4, Height / 2 - 1); cout << "  __) |";
	gotoXY(Width / 2 - 4, Height / 2 - 0); cout << " |__ < ";
	gotoXY(Width / 2 - 4, Height / 2 + 1); cout << " ___) |";
	gotoXY(Width / 2 - 4, Height / 2 + 2); cout << "|____/ ";


	//Đèn màu đỏ
	SetColor(228);

	gotoXY(Width + 3, Height / 8 - 1 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 11); cout << u8"         ●●●●●●●●●●●";

	Sleep(1000);

	SetColor(128);
	gotoXY(Width + 3, Height / 8 - 1 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 - 1 + 11); cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width / 2 - 4, Height / 2 - 3); cout << " ____  ";
	gotoXY(Width / 2 - 4, Height / 2 - 2); cout << "|___ \\ ";
	gotoXY(Width / 2 - 4, Height / 2 - 1); cout << "  __) |";
	gotoXY(Width / 2 - 4, Height / 2 - 0); cout << " |__ < ";
	gotoXY(Width / 2 - 4, Height / 2 + 1); cout << " ___) |";
	gotoXY(Width / 2 - 4, Height / 2 + 2); cout << "|____/ ";


	//Số 2
	SetColor(70);
	gotoXY(Width / 2 - 4, Height / 2 - 3); cout << " ___  ";
	gotoXY(Width / 2 - 4, Height / 2 - 2); cout << "|__ \\ ";
	gotoXY(Width / 2 - 4, Height / 2 - 1); cout << "   ) |";
	gotoXY(Width / 2 - 4, Height / 2 - 0); cout << "  / / ";
	gotoXY(Width / 2 - 4, Height / 2 + 1); cout << " / /_";
	gotoXY(Width / 2 - 4, Height / 2 + 2); cout << "|____|";

	//Đèn màu vàng
	SetColor(70);

	gotoXY(Width + 3, Height / 8 + 11 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 11); cout << u8"         ●●●●●●●●●●●";

	Sleep(1000);

	SetColor(128);
	gotoXY(Width + 3, Height / 8 + 11 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 11 + 11); cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width / 2 - 4, Height / 2 - 3); cout << " ___  ";
	gotoXY(Width / 2 - 4, Height / 2 - 2); cout << "|__ \\ ";
	gotoXY(Width / 2 - 4, Height / 2 - 1); cout << "   ) |";
	gotoXY(Width / 2 - 4, Height / 2 - 0); cout << "  / / ";
	gotoXY(Width / 2 - 4, Height / 2 + 1); cout << " / /_";
	gotoXY(Width / 2 - 4, Height / 2 + 2); cout << "|____|";

	//Số 1
	SetColor(42);
	gotoXY(Width / 2 - 3, Height / 2 - 3); cout << " __ ";
	gotoXY(Width / 2 - 3, Height / 2 - 2); cout << "/_ |";
	gotoXY(Width / 2 - 3, Height / 2 - 1); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 - 0); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 + 1); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 + 2); cout << " |_|";

	//Đèn màu xanh
	SetColor(42);

	gotoXY(Width + 3, Height / 8 + 23 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 11); cout << u8"         ●●●●●●●●●●●";

	Sleep(1000);

	SetColor(128);
	gotoXY(Width + 3, Height / 8 + 23 + 0);  cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 1);  cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 2);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 3);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 4);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 5);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 6);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 7);  cout << u8"●●●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 8);  cout << u8" ●●●●●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 9);  cout << u8"   ●●●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 10); cout << u8"    ●●●●●●●●●●●●●●●●●●●●●";
	gotoXY(Width + 3, Height / 8 + 23 + 11); cout << u8"         ●●●●●●●●●●●";
	gotoXY(Width / 2 - 3, Height / 2 - 3); cout << " __ ";
	gotoXY(Width / 2 - 3, Height / 2 - 2); cout << "/_ |";
	gotoXY(Width / 2 - 3, Height / 2 - 1); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 - 0); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 + 1); cout << " | |";
	gotoXY(Width / 2 - 3, Height / 2 + 2); cout << " |_|";

	//Go
	PlaySound(TEXT("go.wav"), NULL, SND_ASYNC);
	SetColor(13);
	gotoXY(Width / 2 - 12, Height / 2 - 3); cout << "  _____          _   _   _ ";
	gotoXY(Width / 2 - 12, Height / 2 - 2); cout << " / ____|        | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 - 1); cout << "| |  __   ___   | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 - 0); cout << "| | |_ | / _ \\  | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 + 1); cout << "| |__| || (_) | |_| |_| |_|";
	gotoXY(Width / 2 - 12, Height / 2 + 2); cout << " \\_____| \\___/  (_) (_) (_)";

	Sleep(1000);

	SetColor(128);
	gotoXY(Width / 2 - 12, Height / 2 - 3); cout << "  _____          _   _   _ ";
	gotoXY(Width / 2 - 12, Height / 2 - 2); cout << " / ____|        | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 - 1); cout << "| |  __   ___   | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 - 0); cout << "| | |_ | / _ \\  | | | | | |";
	gotoXY(Width / 2 - 12, Height / 2 + 1); cout << "| |__| || (_) | |_| |_| |_|";
	gotoXY(Width / 2 - 12, Height / 2 + 2); cout << " \\_____| \\___/  (_) (_) (_)";

	SetConsoleOutputCP(old_cp);
}
void completedPercent(int a) //Hàm tiến độ
{
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	if (a == 1)	//Trường hợp rắn ăn quả Fruit đầu tiên
	{
		SetColor(198);
		for (int i = 0; i < (Width - 15) / 2; i++)
		{
			gotoXY(Width / 8 + 1 + i, Height + 4);
			cout << u8"█";
			gotoXY(Width / 8 + 1 + i, Height + 5);
			cout << u8"█";
			gotoXY(Width / 8 + 1 + i, Height + 6);
			cout << u8"█";
			Sleep(1);
		}
	}

	if (a == 2)	//Trường hợp rắn ăn quả Fruit thứ 2
	{
		SetColor(186);
		for (int i = 0; i < Width - 15 - 1; i++)
		{
			gotoXY(Width / 8 + 1 + i, Height + 4);
			cout << u8"█";
			gotoXY(Width / 8 + 1 + i, Height + 5);
			cout << u8"█";
			gotoXY(Width / 8 + 1 + i, Height + 6);
			cout << u8"█";
			Sleep(1);
		}
	}

	SetConsoleOutputCP(old_cp);
}
void QuitGame()
{

	PlaySound(TEXT("credit.wav"), NULL, SND_ASYNC);
	UINT old_cp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
	//ShowConsoleCursor(false);
	const int BoardX = 5;
	//20
	const int BoardY = 9;
	const int BoardW = 50;
	const int BoardH = 13;
	const int X = BoardX + 2 + 2 + 1 + 1;
	const int Y = BoardH + BoardY;
	//TextColor(240);
	//drawBoard(BoardH, BoardW, BoardX, BoardY);
	for (int i = Y; i > -Y; i--)
	{
		int j = 0;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			cout << u8"       ĐỒ ÁN KỸ THUẬT LẬP TRÌNH    ";

		} j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"  Game rắn săn mồi _ The Snake Game ";

		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"   Trường Đại học Khoa học Tự Nhiên     ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Lớp:                                    ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             21CLC01                     ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Giáo viên hướng dẫn:              ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Trương Toàn Thịnh    ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Nhóm thực hiện:                   ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Nhóm 7               ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y) cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"Các thành viên:                   ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Đinh Công Huy Hoàng    ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Võ Tấn Lộc           ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Lê Tự Anh Tuấn          ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"             Bùi Minh Đức        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			TextColor(12);
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥       ";
			;
			TextColor(ColorWall);
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥   Thanks for playing   ♥       ";
			;
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			TextColor(12);
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"       ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥       ";
			;
			TextColor(11);
		}j++;
		if (i + j > BoardY && i + j < Y)
		{
			gotoXY(X, i + (j));
			if (i + j <= Y)
				cout << u8"                                        ";
			;
			//Sleep(450);
			break;
			continue;
		}j++;
		Sleep(450);
	}
	SetConsoleOutputCP(old_cp);
}
void displayRound(int x)
{
	if (x == 0)
	{
		SetColor(70);
		gotoXY(Width + 30, 0); cout << " _____                           _   __ " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | | /_ |" << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| |  | |" << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` |  | |" << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| |  | |" << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_|  |_|" << endl;
	}
	else if (x == 1)
	{
		SetColor(133);
		gotoXY(Width + 30, 0); cout << " _____                           _   ___  " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | | |__ \\ " << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| |    ) |" << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` |   / / " << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| |  / /_ " << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_| |____|" << endl;
	}
	else if (x == 2)
	{
		SetColor(133);
		gotoXY(Width + 30, 0); cout << " _____                           _   ____  " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | | |___ \\ " << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| |   __) |" << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` |  |__ < " << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| |  ___) |" << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_| |____/ " << endl;
	}
	else if (x == 3)
	{
		SetColor(142);
		gotoXY(Width + 30, 0); cout << " _____                           _   _  _   " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | | | || |  " << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| | | || |_ " << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` | |__   _|" << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| |    | |  " << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_|    |_| " << endl;
	}
	else if (x == 4)
	{
		SetColor(132);
		gotoXY(Width + 30, 0); cout << " _____                           _   _____ " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | | | ____|" << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| | | |__  " << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` | |___ \\ " << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| |  ___) |" << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_| |____/ " << endl;
	}
	else if (x == 5)
	{
		SetColor(209);
		gotoXY(Width + 30, 0); cout << " _____                           _     __  " << endl;
		gotoXY(Width + 30, 1); cout << "|  __ \\                         | |   / /  " << endl;
		gotoXY(Width + 30, 2); cout << "| |__) | ___   _   _  _ __    __| |  / /_  " << endl;
		gotoXY(Width + 30, 3); cout << "|  _  / / _ \\ | | | || '_ \\  / _` | | '_ \\ " << endl;
		gotoXY(Width + 30, 4); cout << "| | \\ \\| (_) || |_| || | | || (_| | | (_) |" << endl;
		gotoXY(Width + 30, 5); cout << "|_|  \\_\\\\___/  \\__,_||_| |_| \\__,_|  \\___/ " << endl;
	}
}
void displayRoundCenter(int x)
{
	if (x == 0)
	{
		SetColor(70);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ___" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  <  /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /   / / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   / /  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /_/   " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ___" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  <  /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /   / / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   / /  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /_/   " << endl;
	}
	else if (x == 1)
	{
		SetColor(133);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ___ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  |__ \\" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /   __/ /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   / __/ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /____/ " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ___ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  |__ \\" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /   __/ /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   / __/ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /____/ " << endl;
	}
	else if (x == 2)
	{
		SetColor(138);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   _____" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  |__  /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /    /_ < " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   ___/ / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /____/  " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   _____" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  |__  /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /    /_ < " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /   ___/ / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   /____/  " << endl;
	}
	else if (x == 3)
	{
		SetColor(142);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   __ __" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / // /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  / // /_" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  /__  __/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/     /_/   " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   __ __" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / // /" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  / // /_" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  /__  __/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/     /_/   " << endl;
	}
	else if (x == 4)
	{
		SetColor(132);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ______" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / ____/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  /___ \\  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  ____/ /  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/  /_____/   " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   ______" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / ____/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  /___ \\  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  ____/ /  " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/  /_____/   " << endl;
	}
	else if (x == 5)
	{
		SetColor(209);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   _____" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / ___/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  / __ \\ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  / /_/ / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   \\____/  " << endl;

		Sleep(1000);

		SetColor(128);
		gotoXY(Width / 4 - 6, Height / 2 - 4); cout << "    ____                            __   _____" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 3); cout << "   / __ \\ ____   __  __ ____   ____/ /  / ___/" << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 2); cout << "  / /_/ // __ \\ / / / // __ \\ / __  /  / __ \\ " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 1); cout << " / _, _// /_/ // /_/ // / / // /_/ /  / /_/ / " << endl;
		gotoXY(Width / 4 - 6, Height / 2 - 0); cout << "/_/ |_| \\____/ \\__,_//_/ /_/ \\__,_/   \\____/  " << endl;
	}
}