#include <assert.h>
#include <stddef.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>
#include <irkod/fail_failure_malloc.h>
#include <irkod/thing.h>
#include <irkod/grid_line_data.h>
#include <irkod/i_dump.h>
#include <irkod/i_grid_line.h>
#include <irkod/i_id.h>
#include <irkod/i_sequence.h>
#include <irkod/i_str_owner.h>
#include <irkod/text.h>
#include <irkod/mprintf.h>
#include <irkod/page_line.h>

IRKOD_FAIL_FILE(irkod_module_id);

static enum irkod_orientation irkod_i_grid_line__get_orientation(struct irkod_thing *it);
static void irkod_i_grid_line__add_field(struct irkod_thing *it, struct irkod_thing *field, enum irkod_direction d);
static struct irkod_thing *irkod_i_grid_line__get_fields(struct irkod_thing *it, enum irkod_direction d);
static void irkod_i_grid_line__traverse_set_in_fields_count(struct irkod_thing *it, size_t count);
static size_t irkod_i_grid_line__traverse_get_in_fields_count(struct irkod_thing *it);
static void irkod_i_grid_line__traverse_set_in_line(struct irkod_thing *it, struct irkod_thing *line);
static struct irkod_thing *irkod_i_grid_line__traverse_get_in_line(struct irkod_thing *it);
static void irkod_i_grid_line__traverse_clear_in_line(struct irkod_thing *it);
static void irkod_i_id__look(struct irkod_thing *it, const char *id);
static const char *irkod_i_id__get(struct irkod_thing *it);
static struct irkod_thing *irkod_i_dump__get(void *it, void *data, IRKOD_FAIL_PARAM);

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

static struct irkod_i_dump irkod_i_dump =
{
	irkod_i_dump__get
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_grid_line)
	IRKOD_THING_I(irkod_i_id)
	IRKOD_THING_I(irkod_i_dump)
IRKOD_THING_END(irkod_page_line)

void irkod_page_line_init(struct irkod_thing *it, enum irkod_orientation o)
{
	assert(it);
	
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);
	
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

struct irkod_thing *irkod_i_dump__get(void *it, void *data, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT_WITH_RESULT(NULL);
	
	struct irkod_page_line *object = IRKOD_THING_GET_OBJECT(irkod_page_line, it);

	struct irkod_thing *text = irkod_text_new(IRKOD_FAIL);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
	
	irkod_text_init_mprintf(text, IRKOD_FAIL,
		"irkod_page_line{id=\"%s\" orientation=%d",
	       	object->id,
		irkod_grid_line_data_get_orientation(&object->grid_line_data));
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
	
	struct irkod_i_str_owner *i_str_owner = irkod_i_str_owner_geti(text);

	for(enum irkod_direction d = 0; d < irkod_direction_count; ++d)
	{
		i_str_owner->append_mprintf(text, IRKOD_FAIL, " fields[%d]={", d);
		IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);

		struct irkod_thing *fields = irkod_i_grid_line__get_fields(it, d);
		struct irkod_i_sequence *i_sequence = irkod_i_sequence_geti(fields);

		struct irkod_thing *field;
		const char *separator = "";

		for(i_sequence->reset(fields); i_sequence->peek(fields, &field); i_sequence->next(fields))
		{
			struct irkod_i_id *i_id = irkod_i_id_geti(field);
			
			i_str_owner->append_mprintf(text, IRKOD_FAIL, "%s%s", separator, i_id->get(field));
			IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
			
			separator = ",";
		}

		i_str_owner->append(text, "}", IRKOD_FAIL);
		IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);
	}
		
	i_str_owner->append(text, "}", IRKOD_FAIL);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);

	return text;
}
