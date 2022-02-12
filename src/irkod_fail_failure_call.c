#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>

struct irkod_fail_failure_and_details
irkod_fail_failure_call()
{
	static struct irkod_fail_failure failure = { "irkod_call", "Function failed" };
	struct irkod_fail_failure_and_details fad = { &failure, NULL };
	return fad;
}
