#ifndef IRKOD_FAIL_FAILURE_AND_DETAILS_H
#define IRKOD_FAIL_FAILURE_AND_DETAILS_H

struct irkod_fail_failure;
struct irkod_thing;

struct irkod_fail_failure_and_details
{
	struct irkod_fail_failure *failure;
	struct irkod_thing *details;
};

#endif /* !IRKOD_FAIL_FAILURE_AND_DETAILS_H */
