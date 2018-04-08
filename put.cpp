/* ��Ҫ��������⣺
 * 1.�ӿ�
 * 2.����涨���͵������
 * 3.Ҫ���������в�ͬ�Ĺ��
 * 4.���������û�����
 * 5.������������ڴ治��Ϊ����(ʵ���ϲ�����)
 *
 */

#include "function.h"
#include "predict.h"
#include "get_info.h"
#include "average.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <lib_io.h>

int predict_server_all=0;//Ԥ���������CPU��MEM��������
int number_server = 0;//��Ҫ�������������Ŀ
int output_i[F][N];//[������]��[������ͺ�]�����������
//#define N 15 //��Ҫ���Ե����������

void put(unsigned int core_num,unsigned int RAM, int  flavor[][3],unsigned int opti_type) 
{
	printf("Chengcong is excellent!\n\n");
	int i = 0, j = 0;
	int total_CPU = 0, total_MEM = 0;//CPU��MEM������
	//int flavor[N][3];//�ֱ����ͬ������ĸ�����CPU��MEM
	int core_num_i= core_num;
	int RAM_i= RAM;
	int server[2] = {core_num_i , RAM_i};//������������
	int minimal_server = 0;//��Ҫ�������������Сֵ
	int capacity_server[2] = { 0, 0};//���������������
	int remain = 0;//ʣ�����������
	int actual_server_all;//ʵ�������������CPU��MEM��������
	int check_CPU;//�Ż�CPU��MEM���ж�����֮һ
	int check_1;
	double score;//�÷�

	for (i = 0; i < F; i++)//������
	{
		for (j = 0; j < N; j++)
			output_i[i][j] = 0;
	}

	//��¼����������������cpu�������ڴ棨GB��
	unsigned int exchange[N] = {0};//��������Ϊ2015��1�º�2������
	for (i = 0; i < N; i++)
	{
		remain += flavor[i][0];//����ʣ�����������
		exchange[i] = flavor[i][0];//����
		//flavor[i][1] = my_pow(2, (int)(i / 3));//����CPU
		//����MEM
		//if (i % 3 == 0)
		//	flavor[i][2] = flavor[i][1];
		//else if (i % 3 == 1)
		//	flavor[i][2] = flavor[i][1] * 2;
		//else
		//	flavor[i][2] = flavor[i][1] * 4;

		total_CPU += flavor[i][0] * flavor[i][1];//����CPU��MEM����
		total_MEM += flavor[i][0] * flavor[i][2];

	}

	if (my_ceil(total_CPU / server[0]) >= my_ceil(total_MEM / server[1]))
	{
		minimal_server = my_ceil(total_CPU / server[0]);
		printf("At least %d physical servers are needed\n", minimal_server);
	}
	else
	{
		minimal_server = my_ceil(total_MEM / server[1]);
		printf("At least %d physical servers are needed\n", minimal_server);
	}

	printf("There are %d virtual servers in total\n\n", remain);

	if (opti_type==CPU || opti_type==MEM)//�Ż�CPU�����������
	{
		while (remain > 0) //�������ʣ��ʱִ��
		{
			i = N - 1;
			while(i >= 0)
			{
				check_CPU = 0;

				if (i == 0 && flavor[0][0] == 0)
					check_1 = 1;
				else
					check_1 = 0;
				
				if ((flavor[i][0] > 0) || (i == 0))
				{
					if ((capacity_server[0] + flavor[i][1] < server[0]) && (capacity_server[1] + \
                                                flavor[i][2] == server[1]) && (check_1 == 0))
					{

						if ((flavor[i][1] / flavor[i][2]) == 1)//����������
							check_CPU = 0;
						else
							check_CPU = 1;
					}
	
					if ((check_CPU == 0) && (capacity_server[0] + flavor[i][1] <= server[0]) && \
						(capacity_server[1] + flavor[i][2] <= server[1]) && (check_1 == 0))//CPU��MEM�����ᳬ
					{
						capacity_server[0] += flavor[i][1];//����CPU
						capacity_server[1] += flavor[i][2];//����MEM
						
						output_i[number_server][i] += 1;//����ļ�������������ۼ�
						flavor[i][0] -= 1;//��i�����������������
						remain -= 1;//�������������
					}
					else
					{
						i -= 1; //printf("%d\n", i);
						if (i < 0) 
						{
							if (remain > 0)
								number_server += 1;//�Ų����ˣ��¿�һ̨���������

							capacity_server[0] = 0;//�µ����������CPU��MEM��0
							capacity_server[1] = 0;

							//i = N - 1;//����һ̨�µ������������ʱ����Ҫ�Ӵ�������������ʼװ��
						}
					}	
				}
				else
				{
					i -= 1;
				}
			}
		}
	}
	//�������
	printf("%d\n", number_server + 1);
	for (i = 0; i <= number_server; i++)
	{
		printf("%d", i + 1);
		for (j = 0; j < N; j++)
		{
			if (output_i[i][j] != 0) 
			{
				printf(" flavor%d %d", j + 1, output_i[i][j]);
			}
		}
		printf("\n");
	}

	//����÷�
	predict_server_all = 0;
	actual_server_all = 0;

	if (opti_type==CPU) 
	{
		for (i = 0; i < N; i++)
		{
			actual_server_all += exchange[i] * flavor[i][1];
		}
		predict_server_all = (number_server + 1) * server[0];

		score = (double)((double)(actual_server_all) / (double)(predict_server_all));

		printf("%d\n", predict_server_all);
		printf("%d\n", actual_server_all);

		printf("\nThis optimization is %.2lf points for CPU\n\n", score * 100);
	}
	else if (opti_type==MEM)
	{
		for (i = 0; i < N; i++)
		{
			actual_server_all += exchange[i] * flavor[i][2];
		}
		predict_server_all = (number_server + 1) * server[1];

		score = (double)((double)(actual_server_all) / (double)(predict_server_all));

		printf("%d\n", predict_server_all);
		printf("%d\n", actual_server_all);

		printf("\nThis optimization is %.2lf points for MEM\n\n", score * 100);
	}
	printf("Chengcong is excellent!\n\n");
	
	
}

int my_pow(int x, int y)//��x��y����
{
	int m = 1;
	if (y == 0)
		m = 1;
	else 
		for (int i = 0; i < y; i++)
			m = m * 2;
	return m;
}

double my_ceil(double x)//����ȡ������
{
	if (x - int(x) == 0)
		return (float)((int)x);
	else
		return (float)((int)x) + 1;
}



