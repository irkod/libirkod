#ifndef IRKOD_I_DUMP_H
#define IRKOD_I_DUMP_H

#include <irkod/thing.h>
#include <irkod/fail.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_dump);

struct irkod_i_dump
{
	struct irkod_thing *(*get)(void *it, void *data, IRKOD_FAIL_PARAM);
};

#endif /* !IRKOD_I_DUMP_H */
