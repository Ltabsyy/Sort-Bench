/*Sort Bench*/
/*比较各种排序算法速度(doge)*/
/*CPU:wdnmd*/
//#define _CRT_SECURE_NO_WARNINGS//vs专属(doge)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10//每组随机数数量
#define Lim 100000000//测试模式（输出形式3）测试随机数组数
#define FreshCycle 1000//刷新间隔，不建议改动

void PrintList(int* a, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		printf("%5d ", a[i]);
	}
	printf("\n");
}

int IsFreshCycle()
{
	static int clock0 = 0;
	int clock1 = clock();
	if(clock1 - clock0 >= FreshCycle)
	{
		clock0 = clock1;
		return 1;
	}
	return 0;
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

void BubbleSort2(int* a, int n)//冒泡排序优化
{
	int i, j, temp, exchange;
	for(j=1; j<n; j++)//最多执行n-1次
	{
		exchange = 0;
		for(i=0; i<n-j; i++)//最大数上浮，形成有序区
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

void MergeSortMerge(int* a, int low, int mid, int high)//归并排序合并
{
	int i = low, j = mid+1, k = 0;
	int* temp =(int*) calloc(high-low+1, sizeof(int));
	while(i<=mid && j<=high)
	{
		if(a[i] <= a[j])
		{
			temp[k] = a[i];
			i++;
		}
		else
		{
			temp[k] = a[j];
			j++;
		}
		k++;
	}
	while(i<=mid)
	{
		temp[k] = a[i];
		i++;
		k++;
	}
	while(j<=high)
	{
		temp[k] = a[j];
		j++;
		k++;
	}
	for(k=0; k<high-low+1; k++)
	{
		a[low+k] = temp[k];
	}
	free(temp);
}
void MergeSortRank(int* a, int low, int high)//归并排序递归划分
{
	int mid;
	if(low < high)
	{
		mid = (low+high)/2;
		MergeSortRank(a, low, mid);
		MergeSortRank(a, mid+1, high);
		MergeSortMerge(a, low, mid, high);
	}
}
void MergeSort(int* a, int n)//归并排序
{
	MergeSortRank(a, 0, n-1);
}

void CountingSort(int* a, int n)//计数排序，考虑同数区分和顺序
{
	int i, min, max;
	int* count;
	int* temp;
	//计算数据范围
	min = a[0];
	max = a[0];
	for(i=0; i<n; i++)
	{
		if(a[i] < min) min = a[i];
		if(a[i] > max) max = a[i];
	}
	//统计数据出现次数
	count =(int*) calloc(max-min+1, sizeof(int));
	for(i=0; i<n; i++)
	{
		count[a[i]-min]++;
	}
	//转换为待存位置
	//1 2 3 4 5
	//1 3 6 10 15
	//0 1 3 6 10 (15)
	for(i=1; i<max-min+1; i++)
	{
		count[i] += count[i-1];
	}
	for(i=max-min; i>0; i--)
	{
		count[i] = count[i-1];
	}
	count[0] = 0;
	//数据转存
	temp =(int*) calloc(n, sizeof(int));
	for(i=0; i<n; i++)
	{
		temp[count[a[i]-min]] = a[i];
		count[a[i]-min]++;
	}
	for(i=0; i<n; i++)
	{
		a[i] = temp[i];
	}
	free(count);
	free(temp);
}

void RadixSort(int* a, int n)//基数排序，考虑负数、同数区分和顺序
{
	int i, min, max, exp, digit;
	int count[10];
	int* temp =(int*) calloc(n, sizeof(int));
	//计算数据范围
	min = a[0];
	max = a[0];
	for(i=0; i<n; i++)
	{
		if(a[i] < min) min = a[i];
		if(a[i] > max) max = a[i];
	}
	if(min < 0) min *= -1;
	if(max < 0) max *= -1;
	if(min > max) max = min;
	//对从低到高十进制位使用计数排序
	for(exp=1; exp<=max; exp*=10)//考虑同数区分和顺序的计数排序
	{
		for(i=0; i<10; i++)
		{
			count[i] = 0;
		}
		//统计该位0-9出现次数
		for(i=0; i<n; i++)
		{
			digit = a[i]/exp%10;
			if(digit < 0) digit *= -1;
			count[digit]++;
		}
		//转换为待存位置
		//1 2 3 4 5
		//1 3 6 10 15
		//0 1 3 6 10 (15)
		for(i=1; i<10; i++)
		{
			count[i] += count[i-1];
		}
		for(i=9; i>0; i--)
		{
			count[i] = count[i-1];
		}
		count[0] = 0;
		//数据转存
		for(i=0; i<n; i++)
		{
			digit = a[i]/exp%10;
			if(digit < 0) digit *= -1;
			temp[count[digit]] = a[i];
			count[digit]++;
		}
		for(i=0; i<n; i++)
		{
			a[i] = temp[i];
		}
	}
	//反置负数
	int j = 0;
	for(i=n-1; i>=0; i--)
	{
		if(a[i] < 0)
		{
			temp[j] = a[i];
			j++;
		}
	}
	for(i=0; i<n; i++)
	{
		if(a[i] >= 0)
		{
			temp[j] = a[i];
			j++;
		}
	}
	for(i=0; i<n; i++)
	{
		a[i] = temp[i];
	}
	free(temp);
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
		"5.冒泡排序优化\n"
		"6.快速排序\n"
		"7.旧选择排序\n"
		"8.直接选择排序\n"
		"9.堆排序\n"
		"10.归并排序\n"
		"11.计数排序\n"
		"12.基数排序\n");
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
			//a[i] = rand();
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
		else if(choice == 10)
		{
			MergeSort(a, N);
		}
		else if(choice == 11)
		{
			CountingSort(a, N);
		}
		else if(choice == 12)
		{
			RadixSort(a, N);
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
			if(IsFreshCycle())
			{
				t = time(0);
				speed =(float) count/(t-t0);
				printf("\r已排序%d组，%.0f组/s", count, speed);
			}
		}
		else if(show == 3)
		{
			if(IsFreshCycle())
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
Sort Bench 4
——新增 更多排序算法
——优化 固定刷新时间
——优化 冒泡排序优化算法效率
--------------------------------*/
