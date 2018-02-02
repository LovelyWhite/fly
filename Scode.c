#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#define WIDES 30
#define COLS 25
static int speed = 0;
typedef struct a
{
	int EmyNum;//�о��������
	int EmyPos[COLS][WIDES];//�о�λ��
	int AmmoPos[COLS][WIDES];//�ӵ�λ��
	int Pos[2];//�Ҿ�λ��X,Y
	int EmySpeed;//���������ٶ�
	int AmmoSpeed;//�ӵ��ٶ�
	int GenSpeed;//���˲����ٶ�
	int MoveSpeed;
	int score;//����
}setting;
typedef struct b
{
	int MapSize[COLS][WIDES];//-1������ˣ�1�����ҷ���0Ϊ�ո�2�����ڵ� 4�������
	int MapBefore[COLS][WIDES];
}map;
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void GenEmy(setting* dat)//���ɵ���
{
	int i = 0, x = 0;
	x = rand();
	for (i = 0; i < WIDES-1; i++)
		dat->EmyPos[1][i] = 0;
	for (i = 0; i < x % (dat->EmyNum); i++)
		dat->EmyPos[1][rand() % WIDES-1] = -1;
}
void datchng(map* start, setting* dat)//���ݸı�
{
	int i = 0, j = 0;
	speed++;                     //ʱ��
	if (speed == 1000)speed = 0;
	if (speed%dat->GenSpeed==0)//��������ʱ�ӿ���
		GenEmy(dat);
	if (speed % (dat->EmySpeed)==0)      // �����ƶ�ʱ�ӿ���
	{
		for (i = COLS - 1; i >= 0; i--)
		{
			for (j = WIDES - 1; j >= 0; j--)
			{
				if (i == COLS - 1)//�л�����
				{
					if (dat->EmyPos[i][j] == -1)
					{
						dat->EmyPos[i][j] = 0;
						dat->score--;
					}
				}
				else
				{
					if (dat->EmyPos[i][j] == -1)
					{
						dat->EmyPos[i][j] = 0; dat->EmyPos[i + 1][j] = -1;
					}
				}
			}
		}
	}
	if (speed%(dat->AmmoSpeed)==0)  //�ӵ�ʱ�ӿ���
	{
		for (i = 0; i < COLS; i++)
		{
			for (j = 0; j < WIDES; j++)
			{
				if (i == 0)//�ӵ�����
				{
					if (dat->AmmoPos[i][j] == 2)
					{
						dat->AmmoPos[i][j] = 0;
					}
				}
				else
				{
					if (dat->AmmoPos[i][j] == 2)
					{
						dat->AmmoPos[i][j] = 0; dat->AmmoPos[i - 1][j] = 2;
					}
				}
			}
		}
	}
	for (i = 1; i < COLS-1; i++)   //��ͼ���Ӻϳ�
	{
		for (j = 1; j < WIDES-1; j++)
		{
			//��ͼ���ݱ���
			start->MapBefore[i][j] = start->MapSize[i][j];
			if (dat->EmyPos[i][j] +3 == dat->AmmoPos[i][j])
			{
				dat->score++;
				dat->AmmoPos[i][j] = 0;
				dat->EmyPos[i][j] = 0;
				start->MapSize[i][j] = 4;
			}
			else if (start->MapSize[i][j] == -1 || start->MapSize[i][j] == 2)
				start->MapSize[i][j] = 0;
			else if (dat->AmmoPos[i][j] == 2)
				start->MapSize[i][j] = 2;
			else if (dat->EmyPos[i][j] == -1)
				start->MapSize[i][j] = -1;
		}
	}
}
void print(map* start, setting* dat)
{
	int i = 0, j = 0;
	for (i = 1; i < COLS-1; i++)
	{
		for (j = 1; j < WIDES-1; j++)
		{
			if (start->MapSize[i][j] != start->MapBefore[i][j])
			{
				switch (start->MapSize[i][j])
				{
				case 2:gotoxy(j, i); printf("|"); break;
				case -1:gotoxy(j, i ); printf("e"); break;
				case 1:gotoxy(j, i ); printf("$"); break;
				default:gotoxy(j, i); printf(" ");
				}
			}
		}
	} 
	gotoxy(WIDES + 1, COLS / 2-7);
	printf("X: %02d  Y: %02d", dat->Pos[1], dat->Pos[0]);
	gotoxy(WIDES + 1, COLS / 2-6);
	printf("Score:  %03d", dat->score);
	datchng(start, dat);
}
void init(map *start, setting* dat)//��ʼ������
{
	int i = 0, j = 0;
	dat->Pos[0] = COLS - 2;
	dat->Pos[1] = WIDES / 2;
	system("mode con  cols=50 lines=25");
	for (i = 1; i < COLS-1; i++)//����
	{
		gotoxy(WIDES + 15, i);
		printf("|");
	}
	for (i = WIDES; i <WIDES + 15; i++)//����
	{
		gotoxy(i,0);
		printf("-");
		gotoxy(i,COLS-1);
		printf("-");
	}
	gotoxy(WIDES, COLS/2-2); printf("��Ϸ״̬��");
	gotoxy(WIDES + 2, COLS/2);printf("��ʼ��");
	gotoxy(WIDES , COLS / 2 + 3); printf("����������");
	gotoxy(WIDES + 1, COLS / 2 + 6); printf("���������ս��");
	gotoxy(WIDES + 1, COLS / 2 + 7); printf("�ո񿪻�");
	gotoxy(WIDES + 1, COLS / 2 + 8); printf("F2��ͣ");
	for (i = 0; i < WIDES; i++)
		for (j = 0; j < COLS; j++)
		{
			if (i == 0 || i == WIDES - 1)
			{
				gotoxy(i, j); printf("|");
			}//��߿�
			if (j == 0||j == COLS - 1)
			{
				gotoxy(i, j); printf("-");//���߿�//�ױ߿�
			}
			start->MapSize[j][i] = 0;
			start->MapBefore[j][i] = 0;
			dat->AmmoPos[j][i] = 0;
			dat->EmyPos[j][i] = 0;
		}
	start->MapSize[dat->Pos[0]][dat->Pos[1]] = 1;
	dat->EmyNum = 3;
	dat->EmySpeed = 423;
	dat->AmmoSpeed = 20;
	dat->GenSpeed = 500;
	dat->MoveSpeed = 20;
	dat->score = 0;
}
void moveshoot(map *start, setting *dat)//�ƶ�
{
	if (speed % (dat->MoveSpeed)==0)
	{
		start->MapSize[dat->Pos[0]][dat->Pos[1]] = 0;
		if (GetAsyncKeyState(VK_UP) && dat->Pos[0] != 1) dat->Pos[0]--;
		if (GetAsyncKeyState(VK_LEFT) && dat->Pos[1] != 1)dat->Pos[1]--;
		if (GetAsyncKeyState(VK_DOWN) && dat->Pos[0] != COLS - 2)dat->Pos[0]++;
		if (GetAsyncKeyState(VK_RIGHT) && dat->Pos[1] != WIDES - 2)dat->Pos[1]++;
		if (GetAsyncKeyState(VK_SPACE))dat->AmmoPos[dat->Pos[0] - 1][dat->Pos[1]] = 2;
		start->MapSize[dat->Pos[0]][dat->Pos[1]] = 1;
	}
}
int main()
{
	map start;
	setting dat;
	init(&start, &dat);
	while (1)
	{
		if(GetKeyState(VK_F2) < 0)
		{
			gotoxy(WIDES+2, COLS / 2 );
			printf("��ͣ!");
			while (1)
			{
				if (GetKeyState(VK_F2) > 0)
				{
					gotoxy(WIDES + 2, COLS / 2);
					printf("��ʼ��");
					break;
				}
			}
		}
		print(&start, &dat);
		moveshoot(&start, &dat);
		if (dat.score < 0)
		{
			system("cls");
			gotoxy(WIDES / 2, COLS / 2);
			printf("You Died!");
			Sleep(2000);
			break;
		}
	}
	return 0;
}
