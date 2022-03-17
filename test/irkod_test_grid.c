#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <irkod/irkod.h>

const char *main_grid_module_id = "test_grid";
IRKOD_FAIL_FILE(main_grid_module_id);

void line_functor(struct irkod_thing *it, void *data, IRKOD_FAIL_PARAM);
void field_functor(struct irkod_thing *it, void *data, IRKOD_FAIL_PARAM);

struct irkod_grid_traverse_functors functors =
{
	field_functor, NULL,
	line_functor, NULL,
	NULL, NULL
};

void line_functor(struct irkod_thing *it, void *data, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	struct irkod_thing *dump = irkod_i_dump_geti(it)->get(it, NULL, IRKOD_FAIL);

	printf("line: %s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
}
void field_functor(struct irkod_thing *it, void *data, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	struct irkod_thing *dump = irkod_i_dump_geti(it)->get(it, NULL, IRKOD_FAIL);

	printf("field: %s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
}

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(0);


	struct irkod_thing *line_a = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_a, irkod_orientation_vertical);
	irkod_i_id_geti(line_a)->look(line_a, "line_a");
	struct irkod_thing *line_b = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_b, irkod_orientation_horizontal);
	irkod_i_id_geti(line_b)->look(line_b, "line_b");
	struct irkod_thing *line_c = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_c, irkod_orientation_horizontal);
	irkod_i_id_geti(line_c)->look(line_c, "line_c");
	struct irkod_thing *line_d = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_d, irkod_orientation_vertical);
	irkod_i_id_geti(line_d)->look(line_d, "line_d");

	struct irkod_thing *text_A = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_A, "Ala", IRKOD_FAIL);
	irkod_i_id_geti(text_A)->look(text_A, "text_A");
	irkod_grid_insert(text_A,
		       	line_a, line_b, line_c, line_d);  

	struct irkod_thing *dump = irkod_i_dump_geti(line_a)->get(line_a, NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(line_b)->get(line_b, NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(line_c)->get(line_c, NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(line_d)->get(line_d, NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(text_A)->get(text_A, NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);

	printf("TRAVERSING START\n");
	printf("TRAVERSING START\n");
	irkod_grid_traverse(line_a, line_d, irkod_direction_forward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_d, line_a, irkod_direction_backward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_b, line_c, irkod_direction_forward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_c, line_b, irkod_direction_backward, &functors, IRKOD_FAIL);
	printf("TRAVERSING STOP\n");

	IRKOD_THING_DETACH(line_a);
	IRKOD_THING_DETACH(line_b);
	IRKOD_THING_DETACH(line_c);
	IRKOD_THING_DETACH(line_d);
	IRKOD_THING_DETACH(text_A);

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
