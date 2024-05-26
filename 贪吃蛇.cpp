//用到数组计算蛇身 和 conio控制光标

#include <iostream>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;


#define Map_MW "▄"
#define Map_MH "▋"
#define Map_WIDTH 60
#define Map_HEIGHT 25
#define FOOD_MARK "■"
#define SPEED 300
#define SNAKE_HEAD "◎"
#define SNAKE_BODY "●"
#define MOVE 10

struct FOOD {
	int x;
	int y;
} FOOD;

struct Snake {
	int x[114];
	int y[114];
	int CurrentLen = 4;
} Snake;
void gotoxy(int x, int y);
void CreateMap();
void CreateFood();
void initSnake();
void MoveSnake();
int direct = 'a';    //键盘控制
int flag = 1;
int statement();   //判断撞墙；吃到自己
int cnt = 0;

int main() {
	CreateMap();
	initSnake();
	CreateFood();

	while (1) {

		Sleep(100 - cnt * 7);   //吃得越多蛇速度越快
		MoveSnake();
		if (!flag) {
			CreateFood();
			flag = 1;
			cnt++;
			gotoxy(96, 0);
			cout << "已经吃了" << cnt;     //记录
		}
	}


	return 0;
}

void gotoxy(int x, int y) {        //我的编译器好像自带了？

	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void CreateMap() {
	for (int i = 0 + MOVE; i <= MOVE + Map_WIDTH; i ++) { //w
		gotoxy(i, 0);

		printf("▔");
		gotoxy(i, Map_HEIGHT);
		printf(Map_MW);

	}
	for (int i = 0; i <= Map_HEIGHT; i++) {
		gotoxy(MOVE, i );
		printf(Map_MH);
		gotoxy(MOVE + Map_WIDTH, i);
		printf(Map_MH);
	}
}

void CreateFood() {

	srand(time(NULL));
	int judg = 1;
	FOOD.x = rand() % ( Map_WIDTH - 1) + MOVE + 1;
	FOOD.y = rand() % (Map_HEIGHT - 2) + 1;
	for (int i = 0; i < Snake.CurrentLen; i++) {
		if (Snake.x[i] == FOOD.x && Snake.y[i] == FOOD.y)
			judg = 0;
	}
	if (judg) {

		gotoxy(FOOD.x, FOOD.y);
		printf(FOOD_MARK);
	}
}

void initSnake() {
	Snake.x[0] = Map_WIDTH / 2;
	Snake.y[0] = Map_HEIGHT / 2;
	gotoxy(Snake.x[0], Snake.y[0]);
	printf(SNAKE_HEAD);
	for (int i = 1; i <= 3; i++) {
		Snake.x[i] = Snake.x[i - 1] + 1;
		Snake.y[i] = Snake.y[i - 1] ;
		gotoxy(Snake.x[i], Snake.y[i]);
		printf(SNAKE_BODY);

	}

}

void MoveSnake() {

	if (_kbhit()) {
		fflush(stdin);
		direct = getch();
	}

	gotoxy(Snake.x[Snake.CurrentLen - 1], Snake.y[Snake.CurrentLen - 1]    );
	printf(" ");                              //把最后一节抹掉
	for (int i = Snake.CurrentLen - 1; i > 0; i--) {
		Snake.x[i] = Snake.x[i - 1];
		Snake.y[i] = Snake.y[i - 1];
		gotoxy(Snake.x[i], Snake.y[i]);
		printf(SNAKE_BODY);
	}


	switch (direct) {
		case 'w':
		case 'W':
			Snake.y[0]--;
			break;
		case 'A':
		case 'a':
			Snake.x[0]--;
			break;
		case 's':
		case 'S':
			Snake.y[0]++;
			break;
		case 'd':
		case 'D':
			Snake.x[0]++;
			break;

	}
	gotoxy(Snake.x[0], Snake.y[0]);
	printf(SNAKE_HEAD);
	if (Snake.x[0] == FOOD.x && Snake.y[0] == FOOD.y) {

		Snake.CurrentLen++;     //吃到了就蛇身+1

	}
	if (Snake.x[0] == FOOD.x && Snake.y[0] == FOOD.y)
		flag = 0;
	if (statement()) {
		gotoxy(Map_WIDTH / 2, Map_HEIGHT / 2);
		cout << "GAME OVER!";
		Sleep(3000);
		gotoxy(96, 5);
		exit(0);
	}
}

int statement() {
	if (Snake.x[0] == MOVE || Snake.x[0] == MOVE + Map_WIDTH || Snake.y[0] == 0 || Snake.y[0] == Map_HEIGHT)
		return 1;
	for (int i = 1; i <= Snake.CurrentLen; i++)
		if (Snake.x[0] == Snake.x[i] && Snake.y[0] == Snake.y[i])
			return 1;

	return 0;
}
