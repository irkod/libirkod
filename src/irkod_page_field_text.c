#include <assert.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>
#include <irkod/thing.h>
#include <irkod/grid_field_data.h>
#include <irkod/text.h>
#include <irkod/i_dump.h>
#include <irkod/i_grid_field.h>
#include <irkod/i_id.h>
#include <irkod/i_str_owner.h>
#include <irkod/page_field_text.h>

IRKOD_FAIL_FILE(irkod_module_id);

static void irkod_i_grid_field__set_line(struct irkod_thing *it, struct irkod_thing *line,
	enum irkod_orientation o, enum irkod_direction d);
static struct irkod_thing *irkod_i_grid_field__get_line(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d);
static struct irkod_node *irkod_i_grid_field__get_siblings_node(struct irkod_thing *it,
	enum irkod_orientation o, enum irkod_direction d);
static void irkod_i_id__look(struct irkod_thing *it, const char *id);
static const char *irkod_i_id__get(struct irkod_thing *it);
static struct irkod_thing *irkod_i_dump__get(void *it, void *data, IRKOD_FAIL_PARAM);

static struct irkod_i_grid_field irkod_i_grid_field =
{
	irkod_i_grid_field__set_line,
	irkod_i_grid_field__get_line,
	irkod_i_grid_field__get_siblings_node
};

static struct irkod_i_id irkod_i_id =
{
	irkod_i_id__look,
	irkod_i_id__get
};

static struct irkod_i_dump irkod_i_dump =
{
	irkod_i_dump__get
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_grid_field)
	IRKOD_THING_I(irkod_i_id)
	IRKOD_THING_I(irkod_i_dump)
IRKOD_THING_WITH_CLEAR_END(irkod_page_field_text)

void irkod_page_field_text_init(struct irkod_thing *it, const char *text, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);

	IRKOD_THING_INIT(object);
	irkod_grid_field_data_init(&object->grid_field_data, IRKOD_THING(object));
	irkod_text_init_copy(IRKOD_THING(&object->text), text, IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
	
	object->id = "";
}

void irkod_page_field_text_clear(struct irkod_thing *it)
{
	assert(it);
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);

	irkod_text_clear(IRKOD_THING(&object->text));
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

void irkod_i_id__look(struct irkod_thing *it, const char *id)
{
	assert(it);
	assert(id);

	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);
	object->id = id;

}

const char *irkod_i_id__get(struct irkod_thing *it)
{
	assert(it);

	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);
	return object->id;

}

struct irkod_thing *irkod_i_dump__get(void *it, void *data, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT_WITH_RESULT(NULL);
	
	struct irkod_page_field_text *object = IRKOD_THING_GET_OBJECT(irkod_page_field_text, it);

	struct irkod_thing *text = irkod_text_new(IRKOD_FAIL);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
	
	irkod_text_init_mprintf(text, IRKOD_FAIL,
		"irkod_page_field_text{id=\"%s\"",
	       	object->id);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
	
	struct irkod_i_str_owner *i_str_owner = irkod_i_str_owner_geti(text);

	for(enum irkod_orientation o = 0; o < irkod_orientation_count; ++o)
		for(enum irkod_direction d = 0; d < irkod_direction_count; ++d)
		{
			struct irkod_thing *line = irkod_grid_field_data_get_line(&object->grid_field_data, o, d);
			
			i_str_owner->append_mprintf(text, IRKOD_FAIL,
				" line[%d][%d]=%s", o, d, irkod_i_id_geti(line)->get(line));
			IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
		}
		
	i_str_owner->append(text, "}", IRKOD_FAIL);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);

	return text;
}
