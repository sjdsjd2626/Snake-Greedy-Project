#define _CRT_SECURE_NO_WARNINGS 1
#include"snack.h"
int main()
{
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "");//����C���Ա��ػ���Ϊ�˴�ӡ���ַ�
	InitWindow();//���ô��ڴ�С��ʹ��겻�ɼ�
	char ch = 0;
	do
	{
		ch = 0;
		system("cls");
		PrintGameInfo();//��ӡ��Ϸ��Ϣ
		snake s;
		GameStart(&s);//��Ϸ��ʼ
		CleanSource(&s);//������Դ
		Set_Cursor_Pos(45,20);
		printf("�Ƿ�Ҫ���¿�ʼ��Y/N��");
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