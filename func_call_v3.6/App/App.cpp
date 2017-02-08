#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
# include <unistd.h>
# include <pwd.h>

#define MAX_PATH FILENAME_MAX

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"
#include<fstream>
#include<iomanip>
#include <iostream>
#include <vector>
using namespace std;
#include <cstdarg>
//-------------------------------------------------
int hash_int[10000];
double hash_double[10000];
float hash_float[10000];
char hash_char[10000];
long hash_long[10000];

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;
//-----------------------------------------------
int SGX_hash(char* buf,int line)
{
	char buffer[50];
	//return -10;
	char c=*buf;
	switch(c)
	{
		case 'i':strncpy(buffer,buf+4,44);//int_
			int int_data;
			int_data=atoi(buffer);
			hash_int[line]=int_data;
			break;
		case 'd':strncpy(buffer,buf+7,44);//double_
			double double_data;
			double_data=atof(buffer);
			hash_double[line]=double_data;
			break;
		case 'f':strncpy(buffer,buf+6,44);//float_
			float float_data;
			float_data=atof(buffer);
			hash_float[line]=(float)float_data;
			break;
		case 'c':strncpy(buffer,buf+5,44);//char_
			char char_data;
			char_data=*buffer;
			hash_char[line]=double_data;
			break;
		case 'l':strncpy(buffer,buf+5,44);//long_
			long long_data;
			long_data=atol(buffer);
			hash_long[line]=long_data;
			break;
		case '\0':break;
		default:return -6;
	}
	return 1;
}



//--------------------------------------------


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


/* Application entry */
//error -1 : input type is wrong
//

void SGX_Load_Matrix()
{

}
int SGX_Add_Check()
{
return 0;
}
int SGX_Add_Matrix(int type,int left,char* right,int op)
{
	SGX_Add_Check();
	int add_flag=-1;
	encall_add_matrix(global_eid,&add_flag,type,left,right,op);
	return 1;
}


//linenum ,typeid...
int SGX_Lookup(int line,int id, int* int_array, int lenint,
	double* double_array, int lendouble,
	float* float_array, int lenfloat,
	char* char_array, int lenchar,
	long* long_array, int lenlong)
{
    /* Initialize the enclave */
    if(initialize_enclave() < 0){
        printf("init Failed ...\n");
        getchar();
        return -1; 
    }
/*
int in_flag=2;
char buffe[]="ss";
encall_hash_write(global_eid,&in_flag,buffe,2);
*/
//-------------
	/*
	char msg[]="test";
	yt=(char*)malloc(10*sizeof(char));
	memcpy(yt,msg,10);
	int re=999;
	encall_print_int(global_eid,&re,line,int_array);
	printf("int re=%d\n",re);
	}else
	*/
	//------------load-----------------------
	//void SGX_Load_Matrix();
	int load_flag=-111;
	encall_table_load(global_eid,&load_flag);
	printf("load flag=%d\n",load_flag);
	//------------start----------------------
	encall_load_hash(global_eid,&load_flag,hash_int,hash_double,hash_float,hash_char,hash_long);
	printf("hash flag=%d\n",load_flag);
	//------------old_version---------------------
	/*
	if(id==0){
	int flag=-1;
	int re=999;
	encall_print_int(global_eid,&re,line,int_array);
	printf("int re=%d\n",re);
	}else
	if(id==1)
	{
	int re=999;
	encall_print_double(global_eid,&re,line,double_array);
	printf("double re=%d\n",re);
	}else
    	if(id==2){
	int re=999;
	encall_print_float(global_eid,&re,line,float_array);
	printf("float re=%d\n",re);
	}else
	if(id==3){
	int re=999;
	encall_print_char(global_eid,&re,line,char_array);
	printf("char re=%d\n",re);
	}else
	if(id==4){
	int re=999;
	encall_print_long(global_eid,&re,line,long_array);
	printf("long re=%d\n",re);
	}*/
	//------------------new_version--------------
	int re=999;
	encall_switch_type(global_eid,&re,line,id,int_array,lenint,
			double_array,lendouble,
			float_array,lenfloat,
			char_array,lenchar,
			long_array,lenlong);
	printf("re==%d\n",re);
	//----------------test---------------
	char right[]="3";
	SGX_Add_Matrix(1,2,right,4);
    //------------------------------destroy------------
    if(SGX_SUCCESS==sgx_destroy_enclave(global_eid)){
    	//printf("Enclave destroy success\n");
    }else{
		//printf("Enclave destroy failure\n");
		return -1;
    }

    return 0;
}


int SGX_CDECL main(int argc, char *argv[])
{
//line type

int a[]={1,1,1,4,5,6,7,8,9,0};
SGX_Lookup(1,0,a,10,NULL,0,NULL,0,NULL,0,NULL,0);
double a1[]={1.0,3.0,2.0,4.0,5.0,6.0,7.0,8.0,9.0,0.0};
SGX_Lookup(1,1,NULL,0,a1,10,NULL,0,NULL,0,NULL,0);
/*
float a2[]={1.0,1.0,1.0,4.0,5.0,6.0,7.0,8.0,9.0,0.0};
SGX_Lookup(1,2,NULL,0,NULL,0,a2,10,NULL,0,NULL,0);
char a3[]={'a','b','c','4','5','6','7','8','9','0'};
SGX_Lookup(1,3,NULL,0,NULL,0,NULL,0,a3,10,NULL,0);
long a4[]={1,1,1,4,5,6,7,8,9,0};
SGX_Lookup(1,4,NULL,0,NULL,0,NULL,0,NULL,0,a4,10);
*/
return 0;
}
