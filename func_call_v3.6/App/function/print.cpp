#include "../App.h"
#include "Enclave_u.h"

#include<fstream>
#include<iomanip>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>



using namespace std;

/* OCall functions */
int in_flag=0;
void ocall_file_write(char* file,char* buf,int len)
{
    ofstream ofile;
    ofile.open(file);
	if(! ofile.is_open()){
	cout<<"open failure in writing"<<endl;
	}
    ofile<<buf<<endl;
    ofile.close();
}
//     ocall_file_add
void ocall_file_add(char* file,char* buf,int len)
{
    ofstream ofile;
    ofile.open(file,ios::app);
	if(! ofile.is_open()){
	cout<<"open failure in writing"<<endl;
	}
    ofile<<buf<<endl;
    ofile.close();
}
//error -6 unrecognised matrix meta;


void ocall_file_getline(char* file,char* buf,int* line_num)
{
		char* buffer=(char*)malloc(sizeof(char)*50);  
		ifstream ifile(file);  
		if (! ifile.is_open())  
		{
			cout << "Error opening file"<<endl;
			exit (1);
		} 
		int line=0;
		int count=0;
		while (!ifile.eof() )  
		{
			
			if(line<*line_num){
				ifile.getline (buffer,50);
				line++;
				continue;
			}
			ifile.getline(buffer,50);
			memcpy(buf,buffer,50);
			break;
		}
		ifile.close();
}


void ocall_file_read(char* file,int* buf,int* start)
{
		char* buffer=(char*)malloc(sizeof(char)*50);  
		ifstream ifile(file);  
		if (! ifile.is_open())  
		{
			cout << "Error opening file"<<endl;
			exit (1);
		} 
		int line=0;
		int count=0;
		while (!ifile.eof() )  
		{
			
			if(line<*start){
				ifile.getline (buffer,100);
				line++;
				continue;
			}
			if(line==*start+READ_MAX){
				break;
			}
			memset(buffer,'\0',50);
			ifile.getline (buffer,100);
			int read_num=0;
			if(*buffer<48||*buffer>57){//not number
				int in_flag=999;
				in_flag=SGX_hash(buffer,line);
				if(in_flag!=1){
				printf("hash error:%d\n",in_flag);
				exit(1);
				}
			read_num=0-line;
			}else{
			read_num=atoi(buffer);
			}
			*(buf+count)=read_num;
			count++;
			line++;
		}
		ifile.close();
		*start=line;
		int re=1000;
		encall_load_hash(global_eid,&re,hash_int,hash_double,hash_float,hash_char,hash_long);
		printf("hash_load_ok:re=%d\n",re);
}

void ocall_print_string(const char *str)
{
    printf("==in ocall_print:%s", str);
}

