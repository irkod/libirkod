#include <assert.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>
#include <irkod/thing.h>
#include <irkod/grid_field_data.h>
#include <irkod/text.h>
#include <irkod/i_grid_field.h>
#include <irkod/page_field_text.h>

IRKOD_FAIL_FILE(irkod_module_id);

void irkod_i_grid_field__set_line(struct irkod_thing *it, struct irkod_thing *line,
	enum irkod_orientation o, enum irkod_direction d);
struct irkod_thing *irkod_i_grid_field__get_line(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d);
struct irkod_node *irkod_i_grid_field__get_siblings_node(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d);

static struct irkod_i_grid_field irkod_i_grid_field =
{
	irkod_i_grid_field__set_line,
	irkod_i_grid_field__get_line,
	irkod_i_grid_field__get_siblings_node
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_grid_field)
IRKOD_THING_WITH_CLEAR_END(irkod_page_field_text)

void irkod_page_field_text_init(struct irkod_page_field_text *object, const char *text, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(object);
	
	IRKOD_THING_INIT(object);
	irkod_grid_field_data_init(&object->grid_field_data);
	
	irkod_text_init_copy(&object->text, text, IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
}

void irkod_page_field_text_clear(struct irkod_page_field_text *object)
{
	assert(object);

	irkod_text_clear(&object->text);
}

	void 
irkod_i_grid_field__set_line(struct irkod_thing *it, struct irkod_thing *line,
	enum irkod_orientation o, enum irkod_direction d)
{
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);
	
	irkod_grid_field_data_set_line(&object->grid_field_data, line, o, d);
}

struct irkod_thing *
irkod_i_grid_field__get_line(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d)
{
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);
	
	return irkod_grid_field_data_get_line(&object->grid_field_data, o, d);
}

struct irkod_node *
irkod_i_grid_field__get_siblings_node(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d)
{
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);
	
	return irkod_grid_field_data_get_siblings_node(&object->grid_field_data, o, d);
}

