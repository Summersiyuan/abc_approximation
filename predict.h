#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_io.h"


void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename);
//specΪ����������������,����ÿ����Ϣ

//extern char **read_file_line(char ** const buff, const unsigned int spec, const char * const filename);
//��ȡ�ļ�ÿ����Ϣ ����buff������ ����������� �ļ�·��
//���ÿ����Ϣ


#endif
