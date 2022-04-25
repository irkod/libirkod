#ifndef IRKOD_I_KEEPER_H
#define IRKOD_I_KEEPER_H

#include <irkod/thing.h>
#include <irkod/node.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_keeper);

struct irkod_i_keeper
{
	void (*add)(struct irkod_thing *it, struct irkod_node *node);
	void (*clear)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_KEEPER_H */
