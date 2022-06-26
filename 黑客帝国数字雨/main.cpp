#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>

#define RAIN_SIZE 20//�ַ������С
#define RAIN_NUM 128//�����������
#define CHAR_W 15   //�ַ����

/*
*�ַ��Ǳ仯�ģ��������
*����̨->ͼ�δ�����ʾ������������ɫ�����꣬ͼƬ...)
*easyxͼ�ο�
*/


//��������ַ� ��д Сд ����
char randChr()
{
	int ret = rand() % 3;
	if (ret == 0)
	{
		return 'A' + rand() % 26;//[0,26)->['A','Z']
	}
	else if(ret == 1)
	{
		return 'a' + rand() % 26;
	}
	else
	{
		return '0' + rand() % 10;
	}
}

//�ṹ��洢���ɵ���������Ϣ
struct Rain
{
	int x;//������Ŀ�ʼλ��
	int y;
	int speed;//�����ٶ�
	char str[RAIN_SIZE];//�������ַ����� 20���ַ�
};
void rain_init(Rain* r,int x,int y)
{
	r->x = x;
	r->y = y;
	r->speed = rand() % 3 + 1;//1 2 3
	for (int i = 0; i < RAIN_SIZE; i++)
	{
		r->str[i] = randChr();
	}
}

void rain_draw(Rain* r)
{
	//����ַ���
	//puts(r->str);//û��\0
	for (int i = 0; i < RAIN_SIZE; i++)
	{
		//�������ֵ���ɫ
		settextcolor(RGB(0, 255 - i * 13, 0));
		//putchar(r->str[i]);//���������̨
		outtextxy(r->x, r->y-i* CHAR_W, r->str[i]);//���Ƶ�ͼ�δ���
	}	
	//putchar('\n');
}

void rain_rainning(Rain* r)
{
	//ʲô�ڱ仯������ y
	r->y += r->speed;
	//������곬�����ڵķ�Χ���������µ�
	if (r->y - RAIN_SIZE * CHAR_W > getheight())
	{
		r->y = 0;
	}
}

void rain_change(Rain* r)
{
	//��ÿһ���ַ����л���ȥ����仯
	for (int i = 0; i < RAIN_NUM; i++)
	{
		r->str[rand() % RAIN_SIZE] = randChr();
	}
}

struct Rain rains[RAIN_NUM];
void init()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rain_init(rains + i, i * CHAR_W, rand() % getheight());
	}
}

void draw()//����
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rain_draw(rains + i);
		rain_rainning(rains + i);
	}
}

int main()
{
	//����ͼ�δ���
	initgraph(960, 640, EW_SHOWCONSOLE);
	//���ñ���ģʽ
	setbkmode(TRANSPARENT);

	//������������� ���ӣ����ϱ仯��ֵ
	srand(time(NULL));

	init();

	//���ϵ����䣬ѭ���ɻ�
	while (true)
	{
		BeginBatchDraw();//˫�����ͼ
		cleardevice();//����
		draw();
		FlushBatchDraw();

		for (int i = 0; i < 10; i++)
		{
            rain_change(rains + rand() % RAIN_NUM);
		}
	
	}

	getchar();//��ֹͼ�δ�������
	return 0;
}