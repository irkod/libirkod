#ifndef IRKOD_I_GRID_LINE_H
#define IRKOD_I_GRID_LINE_H

#include <irkod/common.h>
#include <irkod/page.h>
#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_page_line);

struct irkod_i_page_line
{
	void (*set_width)(struct irkod_thing *it, irkod_page_coordinate_t width);
	irkod_page_coordinate_t (*get_width)(struct irkod_thing *it);
	void (*push_to)(struct irkod_thing *it, irkod_page_coordinate_t where, enum irkod_direction direction);
	void (*set_where)(struct irkod_thing *it, irkod_page_coordinate_t where, enum irkod_direction direction);
	irkod_coordinate_t (*get_where)(istruct irkod_thing *it, enum irkod_direction direction);
};

#endif /* !IRKOD_I_GRID_LINE_H */
