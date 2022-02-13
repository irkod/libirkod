#include <irkod/grid.h>
#include <irkod/common.h>
#include <irkod/thing.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_call.h>
#include <irkod/i_grid_field.h>
#include <irkod/i_grid_line.h>
#include <irkod/i_sequence.h>
#include <irkod/i_size.h>

IRKOD_FAIL_FILE(irkod_module_id);

void 
irkod_grid_insert(struct irkod_thing *field,
	struct irkod_thing *left_line,
       	struct irkod_thing *top_line, struct irkod_thing *bottom_line,
       	struct irkod_thing *right_line)
{
	assert(field);
	assert(top_line);
	assert(left_line);
	assert(right_line);
	assert(bottom_line);

	struct irkod_i_grid_field *i_field = irkod_i_grid_field_geti(field);

	struct irkod_thing *lines[irkod_orientation_count][irkod_direction_count] =
       	{ { left_line, right_line }, { top_line, bottom_line }};
	
	int o;
	int d;
	
	for(o = 0; o < irkod_orientation_count; o++)
		for(d = 0; d < irkod_direction_count; d++)
		{
			struct irkod_thing *line = lines[o][d];

			i_field->set_line(field, line, o, d);
			irkod_i_grid_line_geti(line)->add_field(line, field, IRKOD_DIRECTION_OPPOSITE(d));
		}

	return;
}

void irkod_grid_traverse(struct irkod_thing *first_line, struct irkod_thing *last_line,
	enum irkod_direction direction, struct irkod_grid_traverse_functors *functors, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	struct irkod_thing *line;
	struct irkod_i_grid_line *i_line;

	line = first_line;
	
	i_line = irkod_i_grid_line_geti(line);
	
	enum irkod_orientation orientation = i_line->get_orientation(line);	
	
	orientation = IRKOD_ORIENTATION_OPPOSITE(orientation);

	for(;;)
	{
		if(functors->line_functor)
		{
			functors->line_functor(line, functors->line_data, IRKOD_FAIL);
			IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
		}

		struct irkod_thing *list = i_line->get_fields(line, direction);
		
		struct irkod_i_sequence *i_sequence = irkod_i_sequence_geti(list);

		i_sequence->reset(list);

		for(;;)
		{
			void *peeked;
			struct irkod_thing *field;
			struct irkod_i_grid_field *i_field;

			if(!i_sequence->peek(list, &peeked))
			{
				if(functors->back_line_functor)
				{
					functors->back_line_functor(line, functors->back_line_data, IRKOD_FAIL);
					IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
				}

				struct irkod_thing *in_line = i_line->traverse_get_in_line(line);

				i_line->traverse_clear_in_line(line);

				line = in_line;

				if(!line)
					return;

				i_line = irkod_i_grid_line_geti(line);

				list = i_line->get_fields(line, direction);

				irkod_i_sequence_geti(list)->next(list);
				continue;
			}
	
			field = peeked;

			if(functors->field_functor)
			{
				functors->field_functor(field, functors->field_data, IRKOD_FAIL);
				IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
			}

			i_field = irkod_i_grid_field_geti(field);

		        struct irkod_thing *next_line = i_field->get_line(field, orientation, direction);

			struct irkod_i_grid_line *i_next_line = irkod_i_grid_line_geti(next_line);
			size_t count = i_next_line->traverse_get_in_fields_count(next_line);

			++count;

			assert(count);

			i_next_line->traverse_set_in_fields_count(next_line, count);

			struct irkod_thing *next_line_list = i_next_line->get_fields(next_line,
				IRKOD_DIRECTION_OPPOSITE(direction));

			struct irkod_i_size *i_next_line_list_size = irkod_i_size_geti(next_line_list);

			if(count != i_next_line_list_size->get(next_line_list))
			{
				i_sequence->next(list);
				continue;
			}
			else
			{
				i_next_line->traverse_set_in_fields_count(next_line, 0);
				i_next_line->traverse_set_in_line(next_line, line);
				
				line = next_line;
				i_line = irkod_i_grid_line_geti(line);

				break;
			}
		}
	}
}

