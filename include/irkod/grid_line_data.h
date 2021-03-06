#ifndef IRKOD_GRID_LINE_DATA_H
#define IRKOD_GRID_LINE_DATA_H

#include <stddef.h>
#include <irkod/common.h>
#include <irkod/thing.h>
#include <irkod/list.h>

struct irkod_grid_line_data
{
	enum irkod_orientation orientation;
	struct irkod_list fields[irkod_direction_count];
	size_t traverse_in_fields_count;
	struct irkod_thing *traverse_in_line;

};

void irkod_grid_line_data_init(struct irkod_grid_line_data *data, enum irkod_orientation o);
enum irkod_orientation irkod_grid_line_data_get_orientation(struct irkod_grid_line_data *data);
void irkod_grid_line_data_add_field(struct irkod_grid_line_data *data, struct irkod_thing *field, enum irkod_direction d);
struct irkod_thing *irkod_grid_line_data_get_fields(struct irkod_grid_line_data *data, enum irkod_direction d);
void irkod_grid_line_data_traverse_set_in_fields_count(struct irkod_grid_line_data *data, size_t count);
size_t irkod_grid_line_data_traverse_get_in_fields_count(struct irkod_grid_line_data *data);
void irkod_grid_line_data_traverse_set_in_line(struct irkod_grid_line_data *data, struct irkod_thing *in_line);
struct irkod_thing *irkod_grid_line_data_traverse_get_in_line(struct irkod_grid_line_data *data);
void irkod_grid_line_data_traverse_clear_in_line(struct irkod_grid_line_data *data);

#endif /* !IRKOD_GRID_LINE_DATA_H */
