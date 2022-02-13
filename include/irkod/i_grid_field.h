#ifndef IRKOD_I_GRID_FIELD_H
#define IRKOD_I_GRID_FIELD_H

#include <irkod/common.h>
#include <irkod/node.h>
#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_grid_field);

struct irkod_i_grid_field
{
	void (*set_line)(struct irkod_thing *it, struct irkod_thing *line,
		enum irkod_orientation o, enum irkod_direction d);
	struct irkod_thing *(*get_line)(struct irkod_thing *it,
		enum irkod_orientation o, enum irkod_direction d);
	struct irkod_node *(*get_siblings_node)(struct irkod_thing *it,
		enum irkod_orientation o, enum irkod_direction d);
};

#endif /* !IRKOD_I_GRID_FIELD_H */
