#ifndef IRKOD_TEXT_CANVAS_H
#define IRKOD_TEXT_CANVAS_H

#include <stddef.h>
#include <irkod/thing.h>

struct irkod_text_canvas
{
	size_t row_count;
	size_t column_count;
	size_t cursor_row;
	int mb_cur_max;
	char *data;
	IRKOD_THING_MEMBER;
};

void irkod_text_canvas_init(struct irkod_text_canvas *object);
void irkod_text_canvas_clear(struct irkod_text_canvas *object);
IRKOD_THING_DECLARE(irkod_text_canvas);
#endif /* !IRKOD_TEXT_CANVAS_H */
