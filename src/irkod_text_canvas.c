#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <irkod/text_canvas.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>
#include <irkod/fail_failure_malloc.h>
#include <irkod/fail_failure_mb.h>
#include <irkod/i_text_canvas.h>
#include <irkod/i_row_cursor.h>
 
IRKOD_FAIL_FILE(irkod_module_id);

static void irkod_i_text_canvas__resize(struct irkod_thing *it,
	size_t row_count, size_t column_count, IRKOD_FAIL_PARAM);
static int irkod_i_text_canvas__put(struct irkod_thing *it,
	size_t row, size_t column, const char *mb, IRKOD_FAIL_PARAM);
static void irkod_i_text_canvas__put_rectangle(struct irkod_thing *it,
        size_t row, size_t column,
        size_t row_count, size_t column_count,
        const char *mb, IRKOD_FAIL_PARAM);
static void irkod_i_text_canvas__print(struct irkod_thing *it, FILE *file,
	IRKOD_FAIL_PARAM);
static void irkod_i_row_cursor__set(struct irkod_thing *it, size_t row);
static size_t irkod_i_row_cursor__get(struct irkod_thing *it);
static size_t irkod_i_row_cursor__move_up(struct irkod_thing *it);
static size_t irkod_i_row_cursor__move_down(struct irkod_thing *it);

static struct irkod_i_text_canvas irkod_i_text_canvas =
{
	irkod_i_text_canvas__resize,
	irkod_i_text_canvas__put,
	irkod_i_text_canvas__put_rectangle,
	irkod_i_text_canvas__print
};

static struct irkod_i_row_cursor irkod_i_row_cursor =
{
	irkod_i_row_cursor__set,
	irkod_i_row_cursor__get,
	irkod_i_row_cursor__move_up,
	irkod_i_row_cursor__move_down
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_text_canvas)
	IRKOD_THING_I(irkod_i_row_cursor)
IRKOD_THING_WITH_CLEAR_END(irkod_text_canvas)

void irkod_text_canvas_init(struct irkod_thing *it)
{
	assert(it);
	
	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	IRKOD_THING_INIT(object);
	object->row_count = 0;
	object->column_count = 0;
	object->cursor_row = 0;
	object->data = NULL;
	object->mb_cur_max = MB_CUR_MAX;
}

void irkod_text_canvas_clear(struct irkod_thing *it)
{
	assert(it);
	
	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	if(object->row_count > 0)
	{
		free(object->data);
		irkod_text_canvas_init(it);	
	}
}

void irkod_i_text_canvas__resize(struct irkod_thing *it, size_t row_count, size_t column_count, IRKOD_FAIL_PARAM)
{
	assert(it);
	assert(row_count);
	assert(column_count);
	assert(MB_CUR_MAX >= 0);

	size_t size_t_max = (size_t) -1;

	assert(size_t_max / sizeof(char*) >= row_count);

	size_t row_pointers_size = sizeof(char*) * row_count;
	size_t mb_cur_max = (MB_CUR_MAX == 0) ? 1 : MB_CUR_MAX;

	assert(((size_t_max - row_pointers_size) / row_count) / mb_cur_max
	       	>= column_count);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	object->mb_cur_max = mb_cur_max;

	char *new_data = NULL;
	size_t new_size = row_pointers_size +
	       	row_count * column_count * mb_cur_max;

	new_data = malloc(new_size);
	IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(new_data);

	char *line = new_data + row_pointers_size;
	size_t line_size = column_count * mb_cur_max;

	for(size_t i = 0; i < row_count; i++)
	{
		((char**) new_data)[i] = line;
		line += line_size;
	}

	free(object->data);

	object->data = new_data;
	object->mb_cur_max = MB_CUR_MAX;
	object->row_count = row_count;
	object->column_count = column_count;
	object->cursor_row = 0;

	memset(object->data + row_pointers_size, ' ',
		new_size - row_pointers_size);
}

int irkod_i_text_canvas__put(struct irkod_thing *it, size_t row, size_t column, const char *mb, IRKOD_FAIL_PARAM)
{
	assert(it);
	
	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);
	
	assert(row < object->row_count);
	assert(column < object->column_count);

	if(object->mb_cur_max == 0)
	{
		if(*mb == '\0')
			return 0;

		((char**)object->data)[row][column] = *mb;
		return 1;
	}
	else
	{
		int size = mblen(mb, (size_t) -1);

		if(size == 0)
			return 0;

		if(size < 0)
		{
			IRKOD_FAIL_SET(irkod_fail_failure_mb());
			return 0;
		}	

		assert(size <= object->mb_cur_max);

		char *ptr = &((char**) object->data)
			[row][column * object->mb_cur_max];

		for(int i = 0; i < size; i++)
			*ptr++ = mb[i];

		return size;
	}
}
void irkod_i_text_canvas__put_rectangle(struct irkod_thing *it,
	size_t row, size_t column,
        size_t row_count, size_t column_count,
        const char *mb, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);
	
	assert(row < object->row_count);
	assert(column < object->column_count);
	assert(object->row_count - row >= row_count);
	assert(object->column_count - column >= column_count);

	for(size_t r = 0; r < row_count; r++)
		for(size_t c = 0; c < column_count; c++)
		{
			irkod_i_text_canvas__put(it, row + r, column + c,
				       	      mb, IRKOD_FAIL);
			IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
		}
}

void irkod_i_text_canvas__print(struct irkod_thing *it, FILE *file, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	assert(file);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);
	
	for(size_t r = 0; r < object->row_count; r++)
	{
		fputc((r == object->cursor_row) ? '>' : ' ', file);
		
		for(size_t c = 0; c < object->column_count; c++)
		{
			if(object->mb_cur_max == 0)
				fputc(((char**)object->data)[r][c], file);
			else
			{
				char *ptr = &((char**)object->data)
					[r][c * object->mb_cur_max];

				int size = mblen(ptr, (size_t) -1);
		
				if(size < 0)
				{
					IRKOD_FAIL_SET(irkod_fail_failure_mb());
					return;
				}
	

				assert(size <= object->mb_cur_max);

				for(int i = 0; i < size; i++)
					fputc(ptr[i], file);
			}
		}

		fputc('\n', file);
	}
}

void irkod_i_row_cursor__set(struct irkod_thing *it, size_t row)
{
	assert(it);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);
	
	assert(row < object->row_count);

	object->cursor_row = row;
}


size_t irkod_i_row_cursor__get(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	return object->cursor_row;
}

size_t irkod_i_row_cursor__move_up(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	if(object->cursor_row > 0)
		--object->cursor_row;

	return object->cursor_row;
}

size_t irkod_i_row_cursor__move_down(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text_canvas *object = 
		IRKOD_THING_GET_OBJECT(irkod_text_canvas, it);

	if(object->cursor_row + 1 < object->row_count )
		++object->cursor_row;

	return object->cursor_row;
}
