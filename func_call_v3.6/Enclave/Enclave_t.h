#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "user_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


int encall_print_int(int line, int* int_array);
int encall_print_double(int line, double* double_array);
int encall_print_float(int line, float* float_array);
int encall_print_char(int line, char* char_array);
int encall_print_long(int line, long int* long_array);
int encall_switch_type(int Line, int intype, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong);
int encall_table_load();
int encall_add_matrix(int type, int left, char* right, int op);
int encall_load_hash(int* hash_int, double* hash_double, float* hash_float, char* hash_char, long int* hash_long);

sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_file_write(char* file, char* buf, int len);
sgx_status_t SGX_CDECL ocall_file_add(char* file, char* buf, int len);
sgx_status_t SGX_CDECL ocall_file_read(char* file, int* buf, int* start);
sgx_status_t SGX_CDECL ocall_file_getline(char* file, char* buf, int* line_num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
