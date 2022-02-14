#include <assert.h>
#include <irkod/thing.h>
#include <irkod/grid_line_data.h>
#include <irkod/i_grid_line.h>
#include <irkod/i_id.h>
#include <irkod/page_line.h>

IRKOD_FAIL_FILE(irkod_module_id);

enum irkod_orientation irkod_i_grid_line__get_orientation(struct irkod_thing *it);
void irkod_i_grid_line__add_field(struct irkod_thing *it, struct irkod_thing *field, enum irkod_direction d);
struct irkod_thing *irkod_i_grid_line__get_fields(struct irkod_thing *it, enum irkod_direction d);
void irkod_i_grid_line__traverse_set_in_fields_count(struct irkod_thing *it, size_t count);
size_t irkod_i_grid_line__traverse_get_in_fields_count(struct irkod_thing *it);
void irkod_i_grid_line__traverse_set_in_line(struct irkod_thing *it, struct irkod_thing *line);
struct irkod_thing *irkod_i_grid_line__traverse_get_in_line(struct irkod_thing *it);
void irkod_i_grid_line__traverse_clear_in_line(struct irkod_thing *it);
void irkod_i_id__look(struct irkod_thing *it, const char *id);
const char *irkod_i_id__get(struct irkod_thing *it);

static struct irkod_i_grid_line irkod_i_grid_line =
{
	irkod_i_grid_line__get_orientation,
	irkod_i_grid_line__add_field,
	irkod_i_grid_line__get_fields,
	irkod_i_grid_line__traverse_set_in_fields_count,
	irkod_i_grid_line__traverse_get_in_fields_count,
	irkod_i_grid_line__traverse_set_in_line,
	irkod_i_grid_line__traverse_get_in_line,
	irkod_i_grid_line__traverse_clear_in_line
};

static struct irkod_i_id irkod_i_id =
{
	irkod_i_id__look,
	irkod_i_id__get
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_grid_line)
	IRKOD_THING_I(irkod_i_id)
IRKOD_THING_END(irkod_page_line)

void irkod_page_line_init(struct irkod_page_line *object, enum irkod_orientation o)
{
	assert(object);
	
	IRKOD_THING_INIT(object);
	irkod_grid_line_data_init(&object->grid_line_data, o);
	object->id = "";
}

enum 
irkod_orientation irkod_i_grid_line__get_orientation(struct irkod_thing *it)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	return irkod_grid_line_data_get_orientation(&object->grid_line_data);
}

void irkod_i_grid_line__add_field(struct irkod_thing *it, struct irkod_thing *field, enum irkod_direction d)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	irkod_grid_line_data_add_field(&object->grid_line_data, field, d);
}

struct irkod_thing *irkod_i_grid_line__get_fields(struct irkod_thing *it, enum irkod_direction d)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	return irkod_grid_line_data_get_fields(&object->grid_line_data, d);
}

void irkod_i_grid_line__traverse_set_in_fields_count(struct irkod_thing *it, size_t count)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	irkod_grid_line_data_traverse_set_in_fields_count(&object->grid_line_data, count);
}

size_t irkod_i_grid_line__traverse_get_in_fields_count(struct irkod_thing *it)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	return irkod_grid_line_data_traverse_get_in_fields_count(&object->grid_line_data);
}

void irkod_i_grid_line__traverse_set_in_line(struct irkod_thing *it, struct irkod_thing *line)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	irkod_grid_line_data_traverse_set_in_line(&object->grid_line_data, line);
}

struct irkod_thing *irkod_i_grid_line__traverse_get_in_line(struct irkod_thing *it)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	return irkod_grid_line_data_traverse_get_in_line(&object->grid_line_data);
}

void irkod_i_grid_line__traverse_clear_in_line(struct irkod_thing *it)
{
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
	irkod_grid_line_data_traverse_clear_in_line(&object->grid_line_data);
}

void irkod_i_id__look(struct irkod_thing *it, const char *id)
{
	assert(it);
	assert(id);

	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	object->id = id;

}
const char *irkod_i_id__get(struct irkod_thing *it)
{
	assert(it);

	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	return object->id;

}
