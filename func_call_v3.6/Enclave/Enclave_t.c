#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


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

static sgx_status_t SGX_CDECL sgx_encall_print_int(void* pms)
{
	ms_encall_print_int_t* ms = SGX_CAST(ms_encall_print_int_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_int_array = ms->ms_int_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_print_int_t));

	ms->ms_retval = encall_print_int(ms->ms_line, _tmp_int_array);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_print_double(void* pms)
{
	ms_encall_print_double_t* ms = SGX_CAST(ms_encall_print_double_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	double* _tmp_double_array = ms->ms_double_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_print_double_t));

	ms->ms_retval = encall_print_double(ms->ms_line, _tmp_double_array);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_print_float(void* pms)
{
	ms_encall_print_float_t* ms = SGX_CAST(ms_encall_print_float_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	float* _tmp_float_array = ms->ms_float_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_print_float_t));

	ms->ms_retval = encall_print_float(ms->ms_line, _tmp_float_array);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_print_char(void* pms)
{
	ms_encall_print_char_t* ms = SGX_CAST(ms_encall_print_char_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_char_array = ms->ms_char_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_print_char_t));

	ms->ms_retval = encall_print_char(ms->ms_line, _tmp_char_array);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_print_long(void* pms)
{
	ms_encall_print_long_t* ms = SGX_CAST(ms_encall_print_long_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	long int* _tmp_long_array = ms->ms_long_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_print_long_t));

	ms->ms_retval = encall_print_long(ms->ms_line, _tmp_long_array);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_switch_type(void* pms)
{
	ms_encall_switch_type_t* ms = SGX_CAST(ms_encall_switch_type_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_int_array = ms->ms_int_array;
	double* _tmp_double_array = ms->ms_double_array;
	float* _tmp_float_array = ms->ms_float_array;
	char* _tmp_char_array = ms->ms_char_array;
	long int* _tmp_long_array = ms->ms_long_array;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_switch_type_t));

	ms->ms_retval = encall_switch_type(ms->ms_Line, ms->ms_intype, _tmp_int_array, ms->ms_lenint, _tmp_double_array, ms->ms_lendouble, _tmp_float_array, ms->ms_lenfloat, _tmp_char_array, ms->ms_lenchar, _tmp_long_array, ms->ms_lenlong);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_table_load(void* pms)
{
	ms_encall_table_load_t* ms = SGX_CAST(ms_encall_table_load_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_table_load_t));

	ms->ms_retval = encall_table_load();


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_add_matrix(void* pms)
{
	ms_encall_add_matrix_t* ms = SGX_CAST(ms_encall_add_matrix_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_right = ms->ms_right;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_add_matrix_t));

	ms->ms_retval = encall_add_matrix(ms->ms_type, ms->ms_left, _tmp_right, ms->ms_op);


	return status;
}

static sgx_status_t SGX_CDECL sgx_encall_load_hash(void* pms)
{
	ms_encall_load_hash_t* ms = SGX_CAST(ms_encall_load_hash_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_hash_int = ms->ms_hash_int;
	double* _tmp_hash_double = ms->ms_hash_double;
	float* _tmp_hash_float = ms->ms_hash_float;
	char* _tmp_hash_char = ms->ms_hash_char;
	long int* _tmp_hash_long = ms->ms_hash_long;

	CHECK_REF_POINTER(pms, sizeof(ms_encall_load_hash_t));

	ms->ms_retval = encall_load_hash(_tmp_hash_int, _tmp_hash_double, _tmp_hash_float, _tmp_hash_char, _tmp_hash_long);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[9];
} g_ecall_table = {
	9,
	{
		{(void*)(uintptr_t)sgx_encall_print_int, 0},
		{(void*)(uintptr_t)sgx_encall_print_double, 0},
		{(void*)(uintptr_t)sgx_encall_print_float, 0},
		{(void*)(uintptr_t)sgx_encall_print_char, 0},
		{(void*)(uintptr_t)sgx_encall_print_long, 0},
		{(void*)(uintptr_t)sgx_encall_switch_type, 0},
		{(void*)(uintptr_t)sgx_encall_table_load, 0},
		{(void*)(uintptr_t)sgx_encall_add_matrix, 0},
		{(void*)(uintptr_t)sgx_encall_load_hash, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[5][9];
} g_dyn_entry_table = {
	5,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 1, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_str);
		memcpy((void*)ms->ms_str, str, _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_write(char* file, char* buf, int len)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_write_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_write_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_write_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_write_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_len = len;
	status = sgx_ocall(1, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_add(char* file, char* buf, int len)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_add_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_add_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_add_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_add_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_len = len;
	status = sgx_ocall(2, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_read(char* file, int* buf, int* start)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_read_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_read_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_read_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_read_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(int*, buf);
	ms->ms_start = SGX_CAST(int*, start);
	status = sgx_ocall(3, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_file_getline(char* file, char* buf, int* line_num)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_file_getline_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_file_getline_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_file_getline_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_file_getline_t));

	ms->ms_file = SGX_CAST(char*, file);
	ms->ms_buf = SGX_CAST(char*, buf);
	ms->ms_line_num = SGX_CAST(int*, line_num);
	status = sgx_ocall(4, ms);


	sgx_ocfree();
	return status;
}

