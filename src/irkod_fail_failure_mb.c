#include <irkod/fail.h>
#include <irkod/fail_failure_mb.h>

struct irkod_fail_failure_and_details
irkod_fail_failure_mb()
{
	static struct irkod_fail_failure failure = { "irkod_mb", "Multibyte character is bad" };
	struct irkod_fail_failure_and_details fad = { &failure, NULL };
	return fad;
}
