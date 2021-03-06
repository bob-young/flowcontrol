#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#include <stdlib.h>
#include <assert.h>

#if defined(__cplusplus)
extern "C" {
#endif

int encall_print_int(int line,int* int_array);
int encall_print_double(int line,double* double_array);
int encall_print_float(int line,float* float_array);
int encall_print_char(int line,char* char_array);
int encall_print_long(int line,long* long_array);
int encall_table_load(void);
int encall_load_hash(int* in_hash_int,double* in_hash_double,float* in_hash_float,char* in_hash_char,long* in_hash_long);
int encall_switch_type(int Line,int intype, int* int_array, int lenint,
			double* double_array, int lendouble,
			float* float_array, int lenfloat,
			char* char_array, int lenchar,
			long* long_array, int lenlong);
//int encall_print(char *fmt,int num);
int encall_add_matrix(int type,int left,char* right,int op);
//int encall_hash_write(char* buf,int line);
#if defined(__cplusplus)
}
#endif

#endif /* !_ENCLAVE_H_ */
