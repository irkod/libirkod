#include <assert.h>
#include <irkod/page_line_data.h>

void irkod_page_line_data_init(struct irkod_page_line_data *object)
{
	assert(object);

	object->width = 0;

	for(int d = 0; d < irkod_direction_count; ++d)
		object->where[d] = 0;
}

void irkod_page_line_data_set_width(struct irkod_page_line_data *object, irkod_page_coordinate_t width)
{
	assert(object);
	assert(width >= 0);

	object->width = width;
}

irkod_page_coordinate_t irkod_page_line_data_get_width(struct irkod_page_line_data *object)
{
	assert(object);
	
	return object->width;
}

void irkod_page_line_data_push_to(struct irkod_page_line_data *object,
		irkod_page_coordinate_t where, enum irkod_direction direction)
{
	switch(direction)
	{
		case irkod_direction_backward:
			if(object->where[direction] + object->width > where)
				object->where[direction] = where - object->width;
			break;
		case irkod_direction_forward:
			if(object->where[direction] < where)
				object->where[direction] = where;
			break;
		default:
			assert(0);
	};

}

void irkod_page_line_data_set_where(struct irkod_page_line_data *object,
	       	irkod_page_coordinate_t where, enum irkod_direction direction)
{
	assert(object);

	switch(direction)
	{
		case irkod_direction_backward:
			object->where[direction] = where - object->width;
			break;
		case irkod_direction_forward:
			object->where[direction] = where;
			break;
		default:
			assert(0);
	};
}

irkod_page_coordinate_t irkod_page_line_data_get_where(struct irkod_page_line_data *object, enum irkod_direction direction) 
{
	assert(object);
	
	return object->where[direction];
}
