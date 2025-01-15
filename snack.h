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
#define DEFAULT_LENGTH 5//Ĭ���ߵĳ���
#define DEFAULT_POS_X 30//Ĭ���ߵ�ͷ��x����
#define DEFAULT_POS_Y 5//Ĭ���ߵ�ͷ��y����

#define WALL L'��'
#define BODY L'��'
#define FOOD L'��'

#define KEY_PRESS(vk) (GetAsyncKeyState(vk)&0x1)//virtual key value�����ֵ

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
	int _sleeptime;//ʱ��Խ�̣��ٶ�Խ��
	int _foodx;
	int _foody;
}snake,*psnake;
void Set_Cursor_Pos(int x, int y);

void InitWindow();

void PrintGameInfo();

void GameStart(psnake ps);

void CleanSource(psnake ps);