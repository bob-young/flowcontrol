#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_encall_print_int_t {
	int ms_retval;
	int ms_line;
	int* ms_int_array;
} ms_encall_print_int_t;

typedef struct ms_encall_print_double_t {
	int ms_retval;
	int ms_line;
	double* ms_double_array;
} ms_encall_print_double_t;

typedef struct ms_encall_print_float_t {
	int ms_retval;
	int ms_line;
	float* ms_float_array;
} ms_encall_print_float_t;

typedef struct ms_encall_print_char_t {
	int ms_retval;
	int ms_line;
	char* ms_char_array;
} ms_encall_print_char_t;

typedef struct ms_encall_print_long_t {
	int ms_retval;
	int ms_line;
	long int* ms_long_array;
} ms_encall_print_long_t;

typedef struct ms_encall_switch_type_t {
	int ms_retval;
	int ms_Line;
	int ms_intype;
	int* ms_int_array;
	int ms_lenint;
	double* ms_double_array;
	int ms_lendouble;
	float* ms_float_array;
	int ms_lenfloat;
	char* ms_char_array;
	int ms_lenchar;
	long int* ms_long_array;
	int ms_lenlong;
} ms_encall_switch_type_t;

typedef struct ms_encall_table_load_t {
	int ms_retval;
} ms_encall_table_load_t;

typedef struct ms_encall_add_matrix_t {
	int ms_retval;
	int ms_type;
	int ms_left;
	char* ms_right;
	int ms_op;
} ms_encall_add_matrix_t;

typedef struct ms_encall_load_hash_t {
	int ms_retval;
	int* ms_hash_int;
	double* ms_hash_double;
	float* ms_hash_float;
	char* ms_hash_char;
	long int* ms_hash_long;
} ms_encall_load_hash_t;

typedef struct ms_ocall_print_string_t {
	char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_file_write_t {
	char* ms_file;
	char* ms_buf;
	int ms_len;
} ms_ocall_file_write_t;

typedef struct ms_ocall_file_add_t {
	char* ms_file;
	char* ms_buf;
	int ms_len;
} ms_ocall_file_add_t;

typedef struct ms_ocall_file_read_t {
	char* ms_file;
	int* ms_buf;
	int* ms_start;
} ms_ocall_file_read_t;

typedef struct ms_ocall_file_getline_t {
	char* ms_file;
	char* ms_buf;
	int* ms_line_num;
} ms_ocall_file_getline_t;

static sgx_status_t SGX_CDECL Enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_write(void* pms)
{
	ms_ocall_file_write_t* ms = SGX_CAST(ms_ocall_file_write_t*, pms);
	ocall_file_write(ms->ms_file, ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_add(void* pms)
{
	ms_ocall_file_add_t* ms = SGX_CAST(ms_ocall_file_add_t*, pms);
	ocall_file_add(ms->ms_file, ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_read(void* pms)
{
	ms_ocall_file_read_t* ms = SGX_CAST(ms_ocall_file_read_t*, pms);
	ocall_file_read(ms->ms_file, ms->ms_buf, ms->ms_start);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_file_getline(void* pms)
{
	ms_ocall_file_getline_t* ms = SGX_CAST(ms_ocall_file_getline_t*, pms);
	ocall_file_getline(ms->ms_file, ms->ms_buf, ms->ms_line_num);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[5];
} ocall_table_Enclave = {
	5,
	{
		(void*)Enclave_ocall_print_string,
		(void*)Enclave_ocall_file_write,
		(void*)Enclave_ocall_file_add,
		(void*)Enclave_ocall_file_read,
		(void*)Enclave_ocall_file_getline,
	}
};
sgx_status_t encall_print_int(sgx_enclave_id_t eid, int* retval, int line, int* int_array)
{
	sgx_status_t status;
	ms_encall_print_int_t ms;
	ms.ms_line = line;
	ms.ms_int_array = int_array;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_print_double(sgx_enclave_id_t eid, int* retval, int line, double* double_array)
{
	sgx_status_t status;
	ms_encall_print_double_t ms;
	ms.ms_line = line;
	ms.ms_double_array = double_array;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_print_float(sgx_enclave_id_t eid, int* retval, int line, float* float_array)
{
	sgx_status_t status;
	ms_encall_print_float_t ms;
	ms.ms_line = line;
	ms.ms_float_array = float_array;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_print_char(sgx_enclave_id_t eid, int* retval, int line, char* char_array)
{
	sgx_status_t status;
	ms_encall_print_char_t ms;
	ms.ms_line = line;
	ms.ms_char_array = char_array;
	status = sgx_ecall(eid, 3, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_print_long(sgx_enclave_id_t eid, int* retval, int line, long int* long_array)
{
	sgx_status_t status;
	ms_encall_print_long_t ms;
	ms.ms_line = line;
	ms.ms_long_array = long_array;
	status = sgx_ecall(eid, 4, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_switch_type(sgx_enclave_id_t eid, int* retval, int Line, int intype, int* int_array, int lenint, double* double_array, int lendouble, float* float_array, int lenfloat, char* char_array, int lenchar, long int* long_array, int lenlong)
{
	sgx_status_t status;
	ms_encall_switch_type_t ms;
	ms.ms_Line = Line;
	ms.ms_intype = intype;
	ms.ms_int_array = int_array;
	ms.ms_lenint = lenint;
	ms.ms_double_array = double_array;
	ms.ms_lendouble = lendouble;
	ms.ms_float_array = float_array;
	ms.ms_lenfloat = lenfloat;
	ms.ms_char_array = char_array;
	ms.ms_lenchar = lenchar;
	ms.ms_long_array = long_array;
	ms.ms_lenlong = lenlong;
	status = sgx_ecall(eid, 5, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_table_load(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_encall_table_load_t ms;
	status = sgx_ecall(eid, 6, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_add_matrix(sgx_enclave_id_t eid, int* retval, int type, int left, char* right, int op)
{
	sgx_status_t status;
	ms_encall_add_matrix_t ms;
	ms.ms_type = type;
	ms.ms_left = left;
	ms.ms_right = right;
	ms.ms_op = op;
	status = sgx_ecall(eid, 7, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t encall_load_hash(sgx_enclave_id_t eid, int* retval, int* hash_int, double* hash_double, float* hash_float, char* hash_char, long int* hash_long)
{
	sgx_status_t status;
	ms_encall_load_hash_t ms;
	ms.ms_hash_int = hash_int;
	ms.ms_hash_double = hash_double;
	ms.ms_hash_float = hash_float;
	ms.ms_hash_char = hash_char;
	ms.ms_hash_long = hash_long;
	status = sgx_ecall(eid, 8, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

