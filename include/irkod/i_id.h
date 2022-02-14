#ifndef IRKOD_I_ID_H
#define IRKOD_I_ID_H

#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_id);

struct irkod_i_id
{
	void (*look)(struct irkod_thing *it, const char *id);
	const char *(*get)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_ID_H */
