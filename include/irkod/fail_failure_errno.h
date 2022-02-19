#ifndef IRKOD_FAIL_FAILURE_ERRNO_H
#define IRKOD_FAIL_FAILURE_ERRNO_H

#include <stddef.h>
#include <irkod/thing.h>

struct irkod_fail_details_errno
{
	int error;	
	IRKOD_THING_MEMBER;
};

struct irkod_fail_failure_and_details irkod_fail_failure_errno(int error);
void irkod_fail_details_errno_init(struct irkod_thing *it, int error);
IRKOD_THING_DECLARE(irkod_fail_details_errno);

#endif /* !IRKOD_FAIL_FAILURE_ERRNO_H */
