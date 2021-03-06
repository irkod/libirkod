#include <stddef.h>
#include <assert.h>
#include <irkod/grid_line_data.h>
#include <irkod/i_grid_field.h>
#include <irkod/thing.h>

void 
irkod_grid_line_data_init(struct irkod_grid_line_data *data, enum irkod_orientation o)
{
	assert(data);

	data->orientation = o;

	for(int d = 0; d < irkod_direction_count; d++)
		irkod_list_init(IRKOD_THING(&data->fields[d]));

	data->traverse_in_fields_count = 0;
	data->traverse_in_line = NULL;
}

enum irkod_orientation 
irkod_grid_line_data_get_orientation(struct irkod_grid_line_data *data)
{
	assert(data);

	return data->orientation;
}

void 
irkod_grid_line_data_add_field(struct irkod_grid_line_data *data, struct irkod_thing *field, enum irkod_direction d)
{
	assert(data);
	assert(field);

	irkod_list_append(&data->fields[d],
		irkod_i_grid_field_geti(field)
		->get_siblings_node(field,
	       	IRKOD_ORIENTATION_OPPOSITE(data->orientation), d));
}

struct irkod_thing *
irkod_grid_line_data_get_fields(struct irkod_grid_line_data *data, enum irkod_direction d)
{
	assert(data);

	return IRKOD_THING(&data->fields[d]);
}

void 
irkod_grid_line_data_traverse_set_in_fields_count(struct irkod_grid_line_data *data, size_t count)
{
	assert(data);

	data->traverse_in_fields_count = count;
}

size_t 
irkod_grid_line_data_traverse_get_in_fields_count(struct irkod_grid_line_data *data)
{
	assert(data);

	return data->traverse_in_fields_count;
}

void 
irkod_grid_line_data_traverse_set_in_line(struct irkod_grid_line_data *data, struct irkod_thing *in_line)
{
	assert(data);
	assert(in_line);

	data->traverse_in_line = in_line;
}
struct irkod_thing *
irkod_grid_line_data_traverse_get_in_line(struct irkod_grid_line_data *data)
{
	assert(data);

	return data->traverse_in_line;

}

void 
irkod_grid_line_data_traverse_clear_in_line(struct irkod_grid_line_data *data)
{
	assert(data);

	data->traverse_in_line = NULL;
}
