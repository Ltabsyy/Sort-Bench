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

void PrintList(int* a, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		printf("%5d ", a[i]);
	}
	printf("\n");
}

/*--插入排序--*/
void InsertSort1(int* a, int n)//从前往后寻找插入位置，随后插入，旧称插入排序
{
	int insert, i, j, temp;
	//初始有序区a[0]
	for(insert=1; insert<n; insert++)//有序区增加a[insert]
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

void InsertSort2(int* a, int n)//直接插入排序，同时后移和寻找插入位置，旧称快速插入排序(doge)
{
	int insert, i, temp;
	for(insert=1; insert<n; insert++)
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

void ShellSort(int* a, int n)
{
	int d, i, insert, temp;
	d = n;//增量初值
	while(1)
	{
		d = d/3+1;
		//一次插入排序
		for(insert=d; insert<n; insert++)
		{
			temp = a[insert];
			for(i=insert-d; i>=0; i-=d)//从后往前遍历
			{
				if(a[i] <= temp)//升序
				{
					break;//插入位置为i+1
				}
				else
				{
					a[i+d] = a[i];//a[i+d]~[insert]后移d位
				}
			}
			a[i+d] = temp;//插入
		}
		//增量为1时退出
		if(d <= 1) break;
	}
}

/*--交换排序--*/
void BubbleSort1(int* a, int n)//冒泡排序
{
	int i, j, temp;
	for(j=1; j<n; j++)//最多执行n-1次
	{
		for(i=0; i<n-1; i++)//所有元素都同时向正确位置移动
		{
			if(a[i] <= a[i+1])//升序
			{
				continue;
			}
			else//相邻交换
			{
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}
		}
	}
}

void BubbleSort2(int* a, int n)//冒泡排序提前终止
{
	int i, j, temp, exchange;
	for(j=1; j<n; j++)//最多执行n-1次
	{
		exchange = 0;
		for(i=0; i<n-1; i++)
		{
			if(a[i] <= a[i+1])//升序
			{
				continue;
			}
			else//相邻交换
			{
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
				exchange = 1;
			}
		}
		if(exchange == 0) break;//一次遍历无交换时终止
	}
}

int QuickSortPartition(int* a, int low, int high)//快速排序划分
{
	int p, i, j, temp;
	p = a[low];//选取第一个，并暂存值
	i = low;
	j = high;
	while(i < j)
	{
		while(i < j && a[j] >= p) j--;
		if(i < j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		while(i < j && a[i] <= p) i++;
		if(i < j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}//i == j
	return i;
}
void QuickSortRank(int* a, int low, int high)//快速排序递归函数
{
	int p;
	if(low < high)
	{
		// 划分
		p = QuickSortPartition(a, low, high);
		//PrintList(a, N);
		// 左右递归排序
		QuickSortRank(a, low, p-1);
		QuickSortRank(a, p+1, high);
	}
}
void QuickSort(int* a, int n)//快速排序
{
	QuickSortRank(a, 0, n-1);
}

/*--选择排序--*/
void SelectSort1(int* a, int n)//不断交换的直接选择排序，旧称选择排序
{
	int i, j, temp;
	for(i=0; i<n-1; i++)//使a[i]最小
	{
		for(j=i+1; j<n; j++)
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

void SelectSort2(int* a, int n)//直接选择排序，旧称快速选择排序
{
	int i, j, index, temp;
	for(i=0; i<=n-2; i++)//使a[i]最小
	{
		index = i;
		for(j=i+1; j<=n-1; j++)
		{
			/*if(a[i] <= a[j])//升序
			{
				continue;
			}
			else */if(a[j] < a[index])
			{
				index = j;
			}
		}//标记最小的数
		temp = a[i];
		a[i] = a[index];
		a[index] = temp;
	}
}

void HeapifyDown(int* a, int n, int i)
{
	int l, r, max, temp;
	while(1)
	{
		l = 2*i+1;
		r = 2*i+2;
		max = i;
		if(l < n && a[max] < a[l]) max = l;
		if(r < n && a[max] < a[r]) max = r;
		if(max == i) break;
		temp = a[i];
		a[i] = a[max];
		a[max] = temp;
		i = max;
	}
}
void HeapSort(int* a, int n)//堆排序
{
	int i, temp;
	// 建立大顶堆
	for(i=((n-1)-1)/2; i>=0; i--)
	{
		HeapifyDown(a, n, i);//从非叶结点向下堆化
	}
	// 依次弹出堆顶
	while(n > 0)
	{
		temp = a[0];
		a[0] = a[n-1];
		a[n-1] = temp;
		n--;
		HeapifyDown(a, n, 0);//从堆顶向下堆化
	}
}

int main()
{
	int choice, show, a[N]={0}, i, n, count, t0, t;
	float speed;
	//printf("大数据排序\n");
	printf("Sort Bench\n");
	printf("系统自动生成每组%d个随机数并排序\n", N);
	printf("算法：\n"
		"1.旧插入排序\n"
		"2.直接插入排序\n"
		"3.希尔排序\n"
		"4.冒泡排序\n"
		"5.冒泡排序提前终止\n"
		"6.快速排序\n"
		"7.旧选择排序\n"
		"8.直接选择排序\n"
		"9.堆排序\n");
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
		//int* b =(int*) calloc(n, sizeof(int));//上面的，说话！(doge)
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
		for(i=0; i<N; i++)
		{
			n = rand()%32768;
			//n = N-i;
			a[i] = n;
		}
		if(show == 1) PrintList(a, N);
		//printf("\n正在排序. . . \n");
		/*--排序--*/
		if(choice == 1)
		{
			InsertSort1(a, N);
		}
		else if(choice == 2)
		{
			InsertSort2(a, N);
		}
		else if(choice == 3)
		{
			ShellSort(a, N);
		}
		else if(choice == 4)
		{
			BubbleSort1(a, N);
		}
		else if(choice == 5)
		{
			BubbleSort2(a, N);
		}
		else if(choice == 6)
		{
			QuickSort(a, N);
		}
		else if(choice == 7)
		{
			SelectSort1(a, N);
		}
		else if(choice == 8)
		{
			SelectSort2(a, N);
		}
		else if(choice == 9)
		{
			HeapSort(a, N);
		}
		else
		{
			BubbleSort1(a, N);
		}
		/*--输出--*/
		count++;
		if(show == 1)
		{
			printf("排序：");
			PrintList(a, N);
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

/*--------------------------------
更新日志：
Sort Bench 2
——优化 代码排版风格
——优化 printf不再影响性能
——优化 对齐排序的输出数字
——修复 快速插入排序死循环
Sort Bench 3
——新增 更多排序算法
--------------------------------*/
