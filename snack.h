#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<locale.h>
#include<time.h>
#define MAPX 100
#define MAPY 35
#define DEFAULT_FOODSCORE 50
#define DEFAULT_SLEEPTIME 80
#define DEFAULT_LENGTH 5//默认蛇的长度
#define DEFAULT_POS_X 30//默认蛇的头的x坐标
#define DEFAULT_POS_Y 5//默认蛇的头的y坐标

#define WALL L'□'
#define BODY L'●'
#define FOOD L'★'

#define KEY_PRESS(vk) (GetAsyncKeyState(vk)&0x1)//virtual key value虚拟键值

enum DIRECTION
{
	UP=1,
	DOWN,
	LEFT,
	RIGHT
};
enum STATE
{
	NORMAL=1,
	QUIT,
	KILL_BY_SELF,
	KILL_BY_WALL
};

typedef struct snakenode
{
	int _x;
	int _y;
	struct snakenode* _next;
}snakenode,*psnakenode;

typedef struct snake
{
	psnakenode _ptohead;
	int _state;
	int _direction;
	int _totalscore;
	int _foodscore;
	int _sleeptime;//时间越短，速度越快
	int _foodx;
	int _foody;
}snake,*psnake;
void Set_Cursor_Pos(int x, int y);

void InitWindow();

void PrintGameInfo();

void GameStart(psnake ps);

void CleanSource(psnake ps);
