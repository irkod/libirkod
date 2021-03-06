#ifndef IRKOD_I_ROW_CURSOR_H
#define IRKOD_I_ROW_CURSOR_H

#include <stddef.h>
#include <irkod/fail.h>
#include <irkod/thing.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_row_cursor);

struct irkod_i_row_cursor
{
	void (*set)(struct irkod_thing *it, size_t row);
	size_t (*get)(struct irkod_thing *it);
	size_t (*move_up)(struct irkod_thing *it);
	size_t (*move_down)(struct irkod_thing *it);
};

#endif /* !IRKOD_I_ROW_CURSOR_H */
