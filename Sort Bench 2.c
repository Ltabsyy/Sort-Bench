/*Sort Bench*/
/*比较各种排序算法速度(doge)*/
/*CPU:wdnmd*/
//#define _CRT_SECURE_NO_WARNINGS//vs专属(doge)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10//每组随机数数量
#define Lim 100000000//测试模式（输出形式3）测试随机数组数
#define FreshCycle 1000000//刷新间隔，不建议改动

void Sort1(int a[]);
void Sort2(int a[]);
void Sort3(int a[]);
void Sort4(int a[]);
void Sort5(int a[]);

int main()
{
	int choice, show, a[N]={0}, i, n, count, t0, t;
	float speed;
	//printf("大数据排序\n");
	printf("Sort Bench\n");
	printf("系统自动生成每组%d个随机数并排序\n", N);
	printf("算法：\n"
		"1.冒泡排序\n"
		"2.选择排序\n"
		"3.快速选择排序\n"
		"4.插入排序\n"
		"5.快速插入排序\n");
	printf("输出形式：\n"
		"0.无输出(doge)\n"
		"1.输出随机生成的数和排序结果\n"
		"2.输出平均速度(初始波动较大!)\n"
		"3.排序%d组输出平均速度\n", Lim);
	printf("请选择算法：");
	scanf("%d", &choice);
	printf("请选择输出形式：");
	scanf("%d", &show);
	count = 0;
	t0 = time(0);
	t = time(0);
	srand(t0);
	while(1)
	{
		/*--输入--*/
		/*printf("输入随机数个数：");
		scanf("%d", &n);*///想屁吃？你无法用变量定义数组的长度(doge)
		if(show == 1)
		{
			printf("      ");
			for(i=1; i<=N; i++)
			{
				printf("%5d ", i);
			}
			printf("\n");
			printf("生成：");
		}
		for(i=1; i<=N; i++)
		{
			n = rand()%32768;
			a[i-1] = n;
			if(show == 1) printf("%5d ", n);
		}
		if(show == 1) printf("\n");
		//printf("\n正在排序. . . \n");
		/*--排序--*/
		if(choice == 1)
		{
			Sort1(a);
		}
		else if(choice == 2)
		{
			Sort2(a);
		}
		else if(choice == 3)
		{
			Sort3(a);
		}
		else if(choice == 4)
		{
			Sort4(a);
		}
		else if(choice == 5)
		{
			Sort5(a);
		}
		else
		{
			Sort1(a);
		}
		/*--输出--*/
		count++;
		if(show == 1)
		{
			printf("排序：");
			for(i=1; i<=N; i++)
			{
				printf("%5d ", a[i-1]);
			}
			printf("\n");
		}
		else if(show == 2)
		{
			if(count % FreshCycle == 0)
			{
				t = time(0);
				speed =(float) count/(t-t0);
				printf("\r已排序%d组，%.0f组/s", count, speed);
			}
		}
		else if(show == 3)
		{
			if(count % FreshCycle == 0)
			{
				t = time(0);
				speed =(float) count/(t-t0);
				printf("\r已排序%d组，%.0f组/s", count, speed);
			}
			if(count == Lim)
			{
				printf("\n");
				printf("请选择算法：");
				scanf("%d", &choice);
				count = 0;
				t0 = time(0);
				t = time(0);
				srand(t0);
			}
		}
	}
	return 0;
}
/*--冒泡排序--*/
void Sort1(int a[])
{
	int i, j, temp;
	for(j=1; j<=N-1; j++)//最多执行n-1次
	{
		for(i=0; i<=N-2; i++)//相邻排序
		{
			if(a[i] <= a[i+1])//升序
			{
				continue;
			}
			else
			{
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}
		}
	}
}
/*--选择排序--*/
void Sort2(int a[])
{
	int i, j, temp;
	for(i=0; i<=N-2; i++)//使a[i]最小
	{
		for(j=i+1; j<=N-1; j++)
		{
			if(a[i] <= a[j])//升序
			{
				continue;
			}
			else
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
/*--快速选择排序--*/
void Sort3(int a[])
{
	int i, j, index, temp;
	for(i=0; i<=N-2; i++)//使a[i]最小
	{
		index = i;
		for(j=i+1; j<=N-1; j++)
		{
			if(a[i] <= a[j])//升序
			{
				continue;
			}
			else if(a[j] < a[index])
			{
				index = j;
			}
		}//标记最小的数
		temp = a[i];
		a[i] = a[index];
		a[index] = temp;
	}
}
/*--插入排序--*/
void Sort4(int a[])
{
	int insert, i, j, temp;
	for(insert=1; insert<=N-1; insert++)
	{
		for(i=0; i<=insert-1; i++)//寻找插入位置
		{
			if(a[insert] <= a[i])//升序
			{
				break;//插入位置为i
			}
		}
		temp = a[insert];
		for(j=insert; j>=i; j--)//a[i]~[insert]后移一位
		{
			a[j] = a[j-1];
		}
		a[i] = temp;//插入
	}
}
/*--快速插入排序--*/
void Sort5(int a[])
{
	int insert, i, temp;
	for(insert=1; insert<=N-1; insert++)
	{
		temp = a[insert];
		for(i=insert-1; i>=0; i--)//从后往前遍历
		{
			if(a[i] <= temp)//升序
			{
				break;//插入位置为i+1
			}
			else
			{
				a[i+1] = a[i];//a[i+1]~[insert]后移一位
			}
		}
		a[i+1] = temp;//插入
	}
}
/*--------------------------------
更新日志：
Sort Bench 2
——优化 代码排版风格
——优化 printf不再影响性能
——优化 对齐排序的输出数字
——修复 快速插入排序死循环
--------------------------------*/
