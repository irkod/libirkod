#ifndef IRKOD_I_TEXT_CANVAS_H
#define IRKOD_I_TEXT_CANVAS_H

#include <stddef.h>
#include <irkod/fail.h>
#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_text_canvas);

struct irkod_i_text_canvas
{
	void (*resize)(struct irkod_thing *it,
		size_t row_count, size_t column_count, IRKOD_FAIL_PARAM);
	int (*put)(struct irkod_thing *it, size_t row, size_t column,
		const char *mb, IRKOD_FAIL_PARAM);
	void (*put_rectangle)(struct irkod_thing *it, size_t row, size_t column,
		size_t row_count, size_t column_count,
		const char *mb, IRKOD_FAIL_PARAM);
	void (*print)(struct irkod_thing *it, FILE *file, IRKOD_FAIL_PARAM);
};

#endif /* !IRKOD_I_TEXT_CANVAS_H */
