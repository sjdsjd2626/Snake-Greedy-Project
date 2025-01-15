#include"snack.h"
int foodandheadoverlap = 0;//ͷ��ʳ���ص���־

void InitWindow()
{
	system("mode con cols=150 lines=40");
	system("title ̰����");
	HANDLE cursor = NULL;
	cursor = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��꣬�������Թ����и���
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(cursor, &cursor_info);//����Ͳ�������ȡ���cursor��Ϣ���ŵ�cursor_info��
	cursor_info.bVisible = 0;
	SetConsoleCursorInfo(cursor, &cursor_info);//���ù����Ϣ
}
void Set_Cursor_Pos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}

void PrintGameInfo()
{
	Set_Cursor_Pos(60, 17);
	printf("��ӭ����̰����С��Ϸ");
	Set_Cursor_Pos(64, 34);
	system("pause");
	system("cls");
	Set_Cursor_Pos(58, 10);
	printf("�� ���������������ֱ��ʾ����");
	Set_Cursor_Pos(58, 13);
	printf("Esc�˳���Space��ͣ");
	Set_Cursor_Pos(58, 16);
	printf("F1���٣�����ʳ���ֵ����");
	Set_Cursor_Pos(58, 19);
	printf("F2���٣�����ʳ���ֵ��С");
	Set_Cursor_Pos(64, 34);
	system("pause");
}
void PrintTheWallAndInfo()
{
	system("cls");
	Set_Cursor_Pos(0,0);
	for (int i = 0; i <= MAPX; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	Set_Cursor_Pos(0, MAPY);
	for (int i = 0; i <= MAPX; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	for (int i = 1; i < MAPY; i++)
	{
		Set_Cursor_Pos(0, i);
		wprintf(L"%lc", WALL);
		Set_Cursor_Pos(MAPX, i);
		wprintf(L"%lc", WALL);
	}
	Set_Cursor_Pos(MAPX+10, MAPY-10);
	printf("�� ���������������ֱ��ʾ����");
	Set_Cursor_Pos(MAPX + 10, MAPY - 8);
	printf("Esc�˳���Space��ͣ");
	Set_Cursor_Pos(MAPX + 10, MAPY - 6);
	printf("F1���٣�����ʳ���ֵ����");
	Set_Cursor_Pos(MAPX + 10, MAPY - 4);
	printf("F2���٣�����ʳ���ֵ��С");
}
psnakenode InitBody(int length)
{
	psnakenode head = NULL;
	psnakenode cur = NULL;
	for (int i = 0; i < length; i++)
	{
		psnakenode newnode = (psnakenode)malloc(sizeof(snakenode));
		if (newnode == NULL)perror("InitBody error");
		newnode->_x = DEFAULT_POS_X - 2 * i;
		newnode->_y = DEFAULT_POS_Y;
		newnode->_next = NULL;//malloc���������ֵ,���û��仰�����һ���ڵ��next����null
		if (i == 0)head = newnode;
		if (cur == NULL)cur = newnode;
		else
		{
			cur->_next = newnode;
			cur = newnode;
		}
	}
	return head;
}
void SetTheFoodPos(psnake ps)
{
	int x=0, y = 0;
again:
	x = ((rand() % (MAPX / 2-1)) + 1) * 2;
	y = rand() % (MAPY - 1) + 1;
	psnakenode cur = ps->_ptohead;
	while (cur != NULL)
	{
		if (cur->_x == x && cur->_y == y)goto again;
		else cur = cur->_next;
	}
	ps->_foodx = x;
	ps->_foody = y;
}

void InitTheSnake(psnake ps)
{
	ps->_direction = RIGHT;
	ps->_state = NORMAL;
	ps->_foodscore = DEFAULT_FOODSCORE;
	ps->_sleeptime = DEFAULT_SLEEPTIME;
	ps->_totalscore = 0;
	ps->_ptohead = InitBody(DEFAULT_LENGTH);
	SetTheFoodPos(ps);
}
void PrintSnackAndScoreAndFood(psnake ps)
{
	psnakenode cur = ps->_ptohead;
	while (cur != NULL)
	{
		Set_Cursor_Pos(cur->_x,cur->_y);
		wprintf(L"%lc", BODY);
		cur = cur->_next;
	}
	Set_Cursor_Pos(MAPX + 10, 10);
	printf("��ǰ�ܵ÷֣�%4d", ps->_totalscore);
	Set_Cursor_Pos(ps->_foodx, ps->_foody);
	wprintf(L"%lc", FOOD);
}
void AcceptArrowKey(psnake ps)
{
	if (KEY_PRESS(VK_UP) && ps->_direction != DOWN)
	{
		ps->_direction = UP;
	}
	else if (KEY_PRESS(VK_DOWN) && ps->_direction != UP)
	{
		ps->_direction = DOWN;
	}
	else if (KEY_PRESS(VK_LEFT) && ps->_direction != RIGHT)
	{
		ps->_direction = LEFT;
	}
	else if (KEY_PRESS(VK_RIGHT) && ps->_direction != LEFT)
	{
		ps->_direction = RIGHT;
	}
}
void AcceptF1F2Key(psnake ps)
{
	if (KEY_PRESS(VK_F1)&&ps->_sleeptime>10)//����
	{
		ps->_sleeptime -= 10;
		ps->_foodscore += 5;
	}
	else if (KEY_PRESS(VK_F2) && ps->_sleeptime < 150)//����
	{
		ps->_sleeptime += 10;
		ps->_foodscore -= 5;
	}
	Set_Cursor_Pos(MAPX + 10, 12);
	printf("����ʳ��÷֣�%2d", ps->_foodscore);
}
void ClearTheKey()
{
	if(KEY_PRESS(VK_UP)|| KEY_PRESS(VK_DOWN) || KEY_PRESS(VK_LEFT) || 
		KEY_PRESS(VK_RIGHT) || KEY_PRESS(VK_F1) || KEY_PRESS(VK_F2) || 
		KEY_PRESS(VK_ESCAPE) || KEY_PRESS(VK_SPACE)){ }
}
void MoveSnake(psnake ps)
{
	int xx = ps->_ptohead->_x;
	int yy = ps->_ptohead->_y;
	switch (ps->_direction)
	{
	case UP:
		yy--;
		break;
	case DOWN:
		yy++;
		break;
	case LEFT:
		xx -= 2;
		break;
	case RIGHT:
		xx += 2;
		break;
	}
	psnakenode newnode = (psnakenode)malloc(sizeof(snakenode));
	newnode->_x = xx;
	newnode->_y = yy;
	newnode->_next = ps->_ptohead;
	ps->_ptohead = newnode;
	if (foodandheadoverlap == 1)
	{
		PrintSnackAndScoreAndFood(ps);
		foodandheadoverlap = 0;
	}
	else
	{
		Set_Cursor_Pos(xx, yy);
		wprintf(L"%lc", BODY);
		psnakenode cur = ps->_ptohead;
		while (cur->_next->_next != NULL)cur = cur->_next;
		Set_Cursor_Pos(cur->_next->_x, cur->_next->_y);
		printf("  ");
		free(cur->_next);
		cur->_next = NULL;
	}
}
void JudgeTheSituation(psnake ps)
{
	int x = ps->_ptohead->_x;
	int y = ps->_ptohead->_y;
	if (x == ps->_foodx && y == ps->_foody)
	{
		foodandheadoverlap = 1;
		ps->_totalscore += ps->_foodscore;
		SetTheFoodPos(ps);
		return;
	}
	else if (x == 0 || x == MAPX || y == 0 || y == MAPY)
	{
		ps->_state = KILL_BY_WALL;
		return;
	}
	psnakenode cur = ps->_ptohead->_next;
	while (cur != NULL)
	{
		if (cur->_x == x && cur->_y == y)
		{
			ps->_state = KILL_BY_SELF;
			break;
		}
		cur = cur->_next;
	}
}

void GameStart(psnake ps)
{
	ClearTheKey();
	PrintTheWallAndInfo();//��ӡǽ��ʱ����cls
	InitTheSnake(ps);
	PrintSnackAndScoreAndFood(ps);
	do
	{
		Sleep(ps->_sleeptime);
		AcceptArrowKey(ps);
		AcceptF1F2Key(ps);
		if (KEY_PRESS(VK_ESCAPE))
		{
			Set_Cursor_Pos(0, MAPY+1);
			ps->_state = QUIT;
			break;
		}
		if (KEY_PRESS(VK_SPACE))
		{
			Set_Cursor_Pos(50, 25);
			printf("����ͣ");
			system("pause");
			ClearTheKey();
			Set_Cursor_Pos(50, 25);
			printf("                             ");
		}
		JudgeTheSituation(ps);
		if (ps->_state == KILL_BY_SELF || ps->_state == KILL_BY_WALL)break;
		MoveSnake(ps);

	} while (ps->_state == NORMAL);
	if (ps->_state == KILL_BY_WALL)
	{
		Set_Cursor_Pos(MAPX / 2 - 5, MAPY / 2);
		printf("��Ϸʧ�ܣ�����ײǽ");
	}
	if (ps->_state == KILL_BY_SELF)
	{
		Set_Cursor_Pos(MAPX / 2 - 5, MAPY / 2);
		printf("��Ϸʧ�ܣ����ܳ��Լ�");
	}
	if (ps->_state == QUIT)
	{
		Set_Cursor_Pos(MAPX / 2 - 5, MAPY / 2);
		printf("��Ϸ�˳�");
	}
}

void CleanSource(psnake ps)
{
	psnakenode cur = ps->_ptohead;
	while (cur != NULL)
	{
		psnakenode next = cur->_next;
		free(cur);
		cur = next;
	}
}