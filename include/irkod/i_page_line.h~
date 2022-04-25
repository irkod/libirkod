#ifndef IRKOD_I_GRID_LINE_H
#define IRKOD_I_GRID_LINE_H

#include <stddef.h>
#include <irkod/common.h>
#include <irkod/thing.h>
#include <irkod/fail.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_grid_line);

struct irkod_i_grid_line
{
	enum irkod_orientation (*get_orientation)(struct irkod_thing *it);
	void (*add_field)(struct irkod_thing *it, struct irkod_thing *field, enum irkod_direction d);
	struct irkod_thing *(*get_fields)(struct irkod_thing *it, enum irkod_direction d);
	void (*traverse_set_in_fields_count)(struct irkod_thing *it, size_t count);
	size_t (*traverse_get_in_fields_count)(struct irkod_thing *it);
	void (*traverse_set_in_line)(struct irkod_thing *it, struct irkod_thing *line);
	struct irkod_thing *(*traverse_get_in_line)(struct irkod_thing *it);
	void (*traverse_clear_in_line)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_GRID_LINE_H */
