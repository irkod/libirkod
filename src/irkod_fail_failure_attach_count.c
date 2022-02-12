#include <irkod/fail.h>
#include <irkod/fail_failure_attach_count.h>

struct irkod_fail_failure_and_details
irkod_fail_failure_attach_count()
{
	static struct irkod_fail_failure failure = { "irkod_attach_count", "attach count too big" };
	struct irkod_fail_failure_and_details fad = { &failure, NULL };
	return fad;
}
