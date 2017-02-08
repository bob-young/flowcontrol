#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
# include <unistd.h>
#include <string.h>
#include <sgx_cpuid.h>
#include <stdlib.h>
#include <cstring>
#define Table_Len 100

#include "Enclave.h"
#include "Enclave_t.h"  /* print_string */
//----------------struct-------------------
struct Table_attr{
  int length;
  int p2;
};
struct Table_meta{
	int p1;
    int p2;
    int op; 
	};

//---------------------global------------------
//type,left-para,right-para,operater
/*
int table1[Table_Len][3]={
  0,1,2,1,
  1,1,double_2.0,2,
  2,3,4,2,
  3,4,5,2,
  4,5,6,3,
  0,6,7,4, 
  1,7,8,5,
  2,8,9,5,
  3,9,10,6,
  4,10,1,6
};*/

char file[]="../func_call_v3.5/App/matrix/myfile.txt";
int* hash_int;
double* hash_double;
float* hash_float;
char* hash_char;
long* hash_long;

int *table=NULL;
Table_attr Enclave_Table={10,0};

/*void set_table_length(int len)
{
    Enclave_Table.length=len;
}*/
//-------------------------global_end----------------
int itoa(int val, char* buf)  
{  
    const unsigned int radix = 10;  
    char* p;  
    unsigned int a;        //every digit  
    int len;  
    char* b;            //start of the digit char  
    char temp;  
    unsigned int u;  
    p = buf;  
    if (val < 0)  
    {  
        *p++ = '-';  
        val = 0 - val;  
    }  
    u = (unsigned int)val;  
    b = p;  
    do  
    {  
        a = u % radix;  
        u /= radix;  
        *p++ = a + '0';  
    } while (u > 0);  
    len = (int)(p - buf);  
    *p-- = 0;  
    do  
    {  
        temp = *p;  
        *p = *b;  
        *b = temp;  
        --p;  
        ++b;  
    } while (b < p);  
    return len;  
}  

Table_meta get_table_meta(int Line)
{
	Table_meta meta;
	meta.p1=*(table+Line*4+1);
	meta.p2=*(table+Line*4+2);
	meta.op=*(table+Line*4+3);
	return meta;
}

int encall_table_load(void)
{
	//char msg[]="loading";
	//ocall_print_string(file);
	int s=0;
	int msgs[4096];
	memset(msgs,'\0',4096);
	ocall_file_read(file,msgs,&s);

	//----test-----------
	/*char rest[100];
	memset(rest,'\0',100);
	for(int i=0;i<10;i++){
		char cat[]="\0\0\0";
		itoa(msgs[i],cat);
		strncat(rest,cat,2);
	}
	ocall_print_string(rest);*/
	//----

    Enclave_Table.length=s;
	table=(int*)malloc(sizeof(int)*4*Enclave_Table.length);
	memcpy(table,msgs,4*Enclave_Table.length*sizeof(int));
	//ocall_load_hash();
	return 1;
}

int encall_print_int(int Line,int* int_array)//---------------------------int
{
    /*TRIPLE*  TABLE=(TRIPLE*)malloc(sizeof(TRIPLE)*10);
    for(int i=0;;i++){
      *(TABLE+i)
    }
    */
	if(table==NULL){return -2;}//table not load yet
    if(Line>=Enclave_Table.length){return -1;}
	Table_meta meta=get_table_meta(Line);
    int return_flag=-1;

    int para1;
    if(meta.p1<0){//right para is null
        int line_num=0-meta.p1;
		para1=hash_int[line_num];
    }else{
		para1=int_array[meta.p1];
	}

    int para2;
    if(meta.p2<0){//right para is null
        int line_num=0-meta.p2;
		para2=hash_int[line_num];
    }else{
		para2=int_array[meta.p2];
	}
    switch(meta.op){
      case 1:return_flag=( para1==para2?1:0);break;
      case 2:return_flag=( para1!=para2?1:0);break;
      case 3:return_flag=( para1>para2?1:0);break;
      case 4:return_flag=( para1<para2?1:0);break;
      case 5:return_flag=( para1>=para2?1:0);break;
      case 6:return_flag=( para1<=para2?1:0);break;
    } 
    return return_flag;
}

int encall_print_double(int Line,double* double_array)//---------------------------double
{
	if(table==NULL){return -2;}//table not load yet
    if(Line>=Enclave_Table.length){return -1;}
	Table_meta meta=get_table_meta(Line);
	double para1;
    double para2;
    int return_flag=-1;

    if(meta.p1<0){//right para is null
        int line_num=0-meta.p1;
		para1=hash_double[line_num];
    }else{
		para1=double_array[meta.p1];
	}

    if(meta.p2<0){//right para is null
        int line_num=0-meta.p2;
		para2=hash_double[line_num];
    }else{
		para2=double_array[meta.p2];
	}

    switch(meta.op){
      case 1:return_flag=( para1==para2?1:0);break;
      case 2:return_flag=( para1!=para2?1:0);break;
      case 3:return_flag=( para1>para2?1:0);break;
      case 4:return_flag=( para1<para2?1:0);break;
      case 5:return_flag=( para1>=para2?1:0);break;
      case 6:return_flag=( para1<=para2?1:0);break;
    } 
    return return_flag;
}

int encall_print_float(int Line,float* float_array)//------------------------float
{
	if(table==NULL){return -2;}//table not load yet
    if(Line>=Enclave_Table.length){return -1;}
	Table_meta meta=get_table_meta(Line);	
	float para1;
    float para2;
    int return_flag=-1;

    if(meta.p1<0){//left para is null
        int line_num=0-meta.p1;
		para1=hash_float[line_num];
    }else{
		para1=float_array[meta.p1];
	}

    if(meta.p2<0){//right para is null
        int line_num=0-meta.p2;
		para2=hash_float[line_num];
    }else{
		para2=float_array[meta.p2];
	}

    switch(meta.op){
      case 1:return_flag=( para1==para2?1:0);break;
      case 2:return_flag=( para1!=para2?1:0);break;
      case 3:return_flag=( para1>para2?1:0);break;
      case 4:return_flag=( para1<para2?1:0);break;
      case 5:return_flag=( para1>=para2?1:0);break;
      case 6:return_flag=( para1<=para2?1:0);break;
    } 
    return return_flag;
}

int encall_print_char(int Line,char* char_array)//----------------------char
{
	if(table==NULL){return -2;}//table not load yet

    if(Line>=Enclave_Table.length){return -1;}
	Table_meta meta=get_table_meta(Line);
	char para1;
    char para2;
    int return_flag=-1;

    if(meta.p1<0){//left para is null
        int line_num=0-meta.p1;
		para1=hash_char[line_num];
    }else{
		para1=char_array[meta.p1];
	}

    if(meta.p2<0){//right para is null
        int line_num=0-meta.p2;
		para2=hash_char[line_num];
    }else{
		para2=char_array[meta.p2];
	}

    switch(meta.op){
      case 1:return_flag=( para1==para2?1:0);break;
      case 2:return_flag=( para1!=para2?1:0);break;
      case 3:return_flag=( para1>para2?1:0);break;
      case 4:return_flag=( para1<para2?1:0);break;
      case 5:return_flag=( para1>=para2?1:0);break;
      case 6:return_flag=( para1<=para2?1:0);break;
    } 
    return return_flag;
}

int encall_print_long(int Line,long* long_array)//----------------------------long
{
	if(table==NULL){return -2;}//table not load yet

    if(Line>=Enclave_Table.length){return -1;}
	Table_meta meta=get_table_meta(Line);	
	long para1=long_array[meta.p1];
    long para2=long_array[meta.p2];
    int return_flag=-1;

    if(meta.p1<0){//right para is null
        int line_num=0-meta.p1;
		para1=hash_long[line_num];
    }else{
		para1=long_array[meta.p1];
	}

    if(meta.p2<0){//right para is null
        int line_num=0-meta.p2;
		para2=hash_long[line_num];
    }else{
		para2=long_array[meta.p2];
	}

    switch(meta.op){
      case 1:return_flag=( para1==para2?1:0);break;
      case 2:return_flag=( para1!=para2?1:0);break;
      case 3:return_flag=( para1>para2?1:0);break;
      case 4:return_flag=( para1<para2?1:0);break;
      case 5:return_flag=( para1>=para2?1:0);break;
      case 6:return_flag=( para1<=para2?1:0);break;
      default:return_flag=-3;
    } 
    return return_flag;
}

//error -999    :input data type donot match matrix
//error -5      :type not exist
//error -1      :line number is out of range
//error -2      :matrix not load yet
//error -3      :matrix internal data mistake
int encall_switch_type(int Line,int intype, int* int_array, int lenint,
	double* double_array, int lendouble,
	float* float_array, int lenfloat,
	char* char_array, int lenchar,
	long* long_array, int lenlong)
{
	int type=*(table+Line*4);
    //return type;
    if(type!=intype){
        return -999;
    }
	int return_flag=-1;
	switch(type){
		case 0:return_flag=encall_print_int(Line,int_array);break;
		case 1:return_flag=encall_print_double(Line,double_array);break;
		case 2:return_flag=encall_print_float(Line,float_array);break;
		case 3:return_flag=encall_print_char(Line,char_array);break;
		case 4:return_flag=encall_print_long(Line,long_array);break;
		default:return_flag=-5;
	}
	return return_flag;
}

int encall_load_hash(int* in_hash_int,double* in_hash_double,float* in_hash_float,char* in_hash_char,long* in_hash_long)
{
	hash_int=(int*)malloc(10000*sizeof(int));
	hash_double=(double*)malloc(10000*sizeof(double));
	hash_float=(float*)malloc(10000*sizeof(float));
	hash_char=(char*)malloc(10000*sizeof(char));
	hash_long=(long*)malloc(10000*sizeof(long));
	memcpy(hash_int,in_hash_int,10000);
	memcpy(hash_double,in_hash_double,10000);
	memcpy(hash_float,in_hash_float,10000);
	memcpy(hash_char,in_hash_char,10000);
	memcpy(hash_long,in_hash_long,10000);

	return 1;
}

int encall_add_matrix(int type,int left,char* right,int op)
{
    char buf[50];
    itoa(type,buf);
    ocall_file_add(file,buf,0);

    char buf1[50];
    itoa(left,buf1);
    ocall_file_add(file,buf1,0);
    
    ocall_file_add(file,right,0);

    char buf3[50];
    itoa(op,buf3);
    ocall_file_add(file,buf3,0);
    
    encall_table_load();
    return 1;
}
