#define _CRT_SECURE_NO_WARNINGS 1
#include"snack.h"
int main()
{
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "");//设置C语言本地化，为了打印宽字符
	InitWindow();//设置窗口大小，使光标不可见
	char ch = 0;
	do
	{
		ch = 0;
		system("cls");
		PrintGameInfo();//打印游戏信息
		snake s;
		GameStart(&s);//游戏开始
		CleanSource(&s);//清理资源
		Set_Cursor_Pos(45,20);
		printf("是否要重新开始（Y/N）");
		int sign = 0;
		while (1)
		{
			if (KEY_PRESS(0x59))
			{
				sign = 1;
				printf("Y");
				Sleep(200);
				break;
			}
			else if(KEY_PRESS(0x4E))
			{
				sign = 0;
				printf("N");
				break;
			}
		}
		if (sign == 0)break;
	} while (1);
	Set_Cursor_Pos(0, MAPY + 1);
	return 0;
}