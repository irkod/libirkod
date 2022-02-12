#include <malloc.h>
#include <irkod/irkod.h>

const char *module_id = "test_fail";
IRKOD_FAIL_FILE(module_id);

void fun_a(IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_SET(irkod_fail_failure_errno(2));
	return;
}


void fun_b(IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	fun_a(IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;

	return;
}

void fun_c(IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	fun_b(IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;

	return;
}

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(1);

	fun_c(IRKOD_FAIL);
	IRKOD_FAIL_SET(irkod_fail_failure_call());	
	IRKOD_FAIL_PRINT(stdout);

	IRKOD_FAIL_CLEAR;;

	fun_a(IRKOD_FAIL);
	IRKOD_FAIL_SET(irkod_fail_failure_call());	
	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
