#ifndef IRKOD_I_SEQUENCE_H
#define IRKOD_I_SEQUENCE_H

#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_sequence);

struct irkod_i_sequence
{
	void (*reset)(struct irkod_thing *it);
	int (*peek)(struct irkod_thing *it, struct irkod_thing **thing);
	void (*next)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_SEQUENCE_H */
