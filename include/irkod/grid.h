#ifndef IRKOD_GRID_H
#define IRKOD_GRID_H

#include <irkod/common.h>
#include <irkod/thing.h>
#include <irkod/fail.h>

struct irkod_grid_traverse_functors
{
	irkod_thing_functor_t field_functor;
	void *field_data;
	irkod_thing_functor_t line_functor;
	void *line_data;
	irkod_thing_functor_t back_line_functor;
	void *back_line_data;
};

void irkod_grid_insert(struct irkod_thing *field, 
	struct irkod_thing *left_line, 
	struct irkod_thing *top_line, struct irkod_thing *bottom_line, 
	struct irkod_thing *right_line);
void irkod_grid_traverse(struct irkod_thing *first_line, struct irkod_thing *last_line,
	enum irkod_direction d,
       	struct irkod_grid_traverse_functors *functors,
       	IRKOD_FAIL_PARAM);

#endif /* !IRKOD_GRID_H */
