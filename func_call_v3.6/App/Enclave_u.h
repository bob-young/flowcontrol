#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "user_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_file_write, (char* file, char* buf, int len));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_file_add, (char* file, char* buf, int len));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_file_read, (char* file, int* buf, int* start));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_file_getline, (char* file, char* buf, int* line_num));

sgx_status_t encall_print_int(sgx_enclave_id_t eid, int* retval, int line, int* int_array);
sgx_status_t encall_print_double(sgx_enclave_id_t eid, int* retval, int line, double* double_array);
sgx_status_t encall_print_float(sgx_enclave_id_t eid, int* retval, int line, float* float_array);
sgx_status_t encall_print_char(sgx_enclave_id_t eid, int* retval, int line, char* char_array);
sgx_status_t encall_print_long(sgx_enclave_id_t eid, int* retval, int line, long int* long_array);
sgx_status_t encall_switch_type(sgx_enclave_id_t eid, int* retval, int Line, int intype, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong);
sgx_status_t encall_table_load(sgx_enclave_id_t eid, int* retval);
sgx_status_t encall_add_matrix(sgx_enclave_id_t eid, int* retval, int type, int left, char* right, int op);
sgx_status_t encall_load_hash(sgx_enclave_id_t eid, int* retval, int* hash_int, double* hash_double, float* hash_float, char* hash_char, long int* hash_long);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
