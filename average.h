#ifndef __AVERAGE_H__
#define __AVERAGE_H__

#include "lib_io.h"

extern int   flavor[][3];//����������ں������ڴ��С,1:�ں���;2:�ڴ��С
extern int t_gap, i_gap;
void average(unsigned int * t_flavor_num, char ** const i_flavor, 
			 int  class_flavor[][3], unsigned int i_flavor_N,int data_num);
			
			
#endif
