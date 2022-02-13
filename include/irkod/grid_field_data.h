#ifndef IRKOD_GRID_FIELD_DATA_H
#define IRKOD_GRID_FIELD_DATA_H

#include <irkod/common.h>
#include <irkod/node.h>
#include <irkod/thing.h>

struct irkod_grid_field_data
{
	struct irkod_thing *line[irkod_orientation_count][irkod_direction_count];
	struct irkod_node siblings_node[irkod_orientation_count][irkod_direction_count];
};

void irkod_grid_field_data_init(struct irkod_grid_field_data *data);
void irkod_grid_field_data_set_line(struct irkod_grid_field_data *data, struct irkod_thing *line,
	enum irkod_orientation orientation, enum irkod_direction direction);
struct irkod_thing *irkod_grid_field_data_get_line(struct irkod_grid_field_data *data, enum irkod_orientation orientation,
	enum irkod_direction direction);
struct irkod_node *irkod_grid_field_data_get_siblings_node(struct irkod_grid_field_data *data,
	enum irkod_orientation orientation, enum irkod_direction direction);

#endif /* !IRKOD_GRID_FIELD_DATA_H */
