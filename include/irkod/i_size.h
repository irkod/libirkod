#ifndef IRKOD_I_SIZE_H
#define IRKOD_I_SIZE_H

#include <stddef.h>
#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_size);

struct irkod_i_size
{
	size_t (*get)(const struct irkod_thing *it);
};

#endif /* !IRKOD_I_SIZE_H */
