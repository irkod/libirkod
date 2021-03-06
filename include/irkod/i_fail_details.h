#ifndef IRKOD_I_FAIL_DETAILS_H
#define IRKOD_I_FAIL_DETAILS_H

#include <irkod/thing.h>
#include <irkod/fail.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_fail_details);

struct irkod_i_fail_details
{
	struct irkod_thing *(*dump)(struct irkod_thing *it, IRKOD_FAIL_PARAM);
};

#endif /* !IRKOD_I_FAIL_DETAILS_H */
