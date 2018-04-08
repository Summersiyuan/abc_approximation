#ifndef __AVERAGE_H__
#define __AVERAGE_H__

#include "lib_io.h"

extern int   flavor[][3];//定义虚拟机内核数和内存大小,1:内核数;2:内存大小
extern int t_gap, i_gap;
void average(unsigned int * t_flavor_num, char ** const i_flavor, 
			 int  class_flavor[][3], unsigned int i_flavor_N,int data_num);
			
			
#endif
