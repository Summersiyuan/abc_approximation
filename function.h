#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "get_info.h"
#include "lib_io.h"

#define F 100 //������������������ֵ

extern int predict_server_all;//Ԥ���������CPU��MEM��������
extern int number_server;//��Ҫ�������������Ŀ
extern int output_i[][N];//[������]��[������ͺ�]�����������
extern void put(unsigned int core_num, unsigned int RAM, int flavor[][3], unsigned int opti_type);

int my_pow(int x, int y);
double my_ceil(double x);

#endif


