#ifndef IRKOD_I_STR_H
#define IRKOD_I_STR_H

#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_str);

struct irkod_i_str
{
	const char *(*get)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_STR_H */
