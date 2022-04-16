#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>

#define RAIN_SIZE 20//字符数组大小
#define RAIN_NUM 128//数字雨的数量
#define CHAR_W 15   //字符宽度

/*
*字符是变化的：随机函数
*控制台->图形窗口显示（设置文字颜色，坐标，图片...)
*easyx图形库
*/


//随机生成字符 大写 小写 数字
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

//结构体存储生成的数字雨信息
struct Rain
{
	int x;//数字雨的开始位置
	int y;
	int speed;//下落速度
	char str[RAIN_SIZE];//数字雨字符数组 20个字符
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
	//输出字符串
	//puts(r->str);//没有\0
	for (int i = 0; i < RAIN_SIZE; i++)
	{
		//设置文字的颜色
		settextcolor(RGB(0, 255 - i * 13, 0));
		//putchar(r->str[i]);//输出到控制台
		outtextxy(r->x, r->y-i* CHAR_W, r->str[i]);//绘制到图形窗口
	}	
	//putchar('\n');
}

void rain_rainning(Rain* r)
{
	//什么在变化？坐标 y
	r->y += r->speed;
	//如果坐标超出窗口的范围，重新往下掉
	if (r->y - RAIN_SIZE * CHAR_W > getheight())
	{
		r->y = 0;
	}
}

void rain_change(Rain* r)
{
	//让每一个字符都有机会去随机变化
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

void draw()//绘制
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rain_draw(rains + i);
		rain_rainning(rains + i);
	}
}

int main()
{
	//创建图形窗口
	initgraph(960, 640, EW_SHOWCONSOLE);
	//设置背景模式
	setbkmode(TRANSPARENT);

	//设置随机数种子 种子：不断变化的值
	srand(time(NULL));

	init();

	//不断地下落，循环干活
	while (true)
	{
		BeginBatchDraw();//双缓冲绘图
		cleardevice();//清屏
		draw();
		FlushBatchDraw();

		for (int i = 0; i < 10; i++)
		{
            rain_change(rains + rand() % RAIN_NUM);
		}
	
	}

	getchar();//防止图形窗口闪退
	return 0;
}