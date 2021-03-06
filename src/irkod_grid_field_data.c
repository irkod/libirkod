#include <stddef.h>
#include <assert.h>
#include <irkod/grid_field_data.h>

void 
irkod_grid_field_data_init(struct irkod_grid_field_data *data, struct irkod_thing *it)
{
	assert(data);

	for(int o = 0; o < irkod_orientation_count; o++)
		for(int d = 0; d < irkod_direction_count; d++)
		{
			data->line[o][d] = NULL;
			irkod_node_init(&data->siblings_node[o][d], it);
		}
}

void 
irkod_grid_field_data_set_line(struct irkod_grid_field_data *data, struct irkod_thing *line,
	enum irkod_orientation o, enum irkod_direction d)
{
	assert(data);
	assert(line);

	data->line[o][d] = line;
}

struct irkod_thing *
irkod_grid_field_data_get_line(struct irkod_grid_field_data *data,
	enum irkod_orientation o, enum irkod_direction d)
{
	assert(data);

	return data->line[o][d];
}

struct irkod_node *
irkod_grid_field_data_get_siblings_node(struct irkod_grid_field_data *data,
	enum irkod_orientation o, enum irkod_direction d)
{
	assert(data);

	return &data->siblings_node[o][d];
}
