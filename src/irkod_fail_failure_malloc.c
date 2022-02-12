#include <irkod/fail.h>
#include <irkod/fail_failure_malloc.h>

struct irkod_fail_failure_and_details
irkod_fail_failure_malloc()
{
	static struct irkod_fail_failure failure = { "irkod_malloc", "out of memory" };
	struct irkod_fail_failure_and_details fad = { &failure, NULL };
	return fad;
}
