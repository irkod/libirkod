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

	struct irkod_thing *line_u = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_u, irkod_orientation_horizontal);
	irkod_i_id_geti(line_u)->look(line_u, "line_u");
	struct irkod_thing *line_d = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_d, irkod_orientation_horizontal);
	irkod_i_id_geti(line_d)->look(line_d, "line_d");
	struct irkod_thing *line_h1 = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_h1, irkod_orientation_horizontal);
	irkod_i_id_geti(line_h1)->look(line_h1, "line_h1");
	struct irkod_thing *line_h2 = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_h2, irkod_orientation_horizontal);
	irkod_i_id_geti(line_h2)->look(line_h2, "line_h2");
	struct irkod_thing *line_h3 = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_h3, irkod_orientation_horizontal);
	irkod_i_id_geti(line_h3)->look(line_h3, "line_h3");

	struct irkod_thing *line_l = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_l, irkod_orientation_vertical);
	irkod_i_id_geti(line_l)->look(line_l, "line_l");
	struct irkod_thing *line_r = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_r, irkod_orientation_vertical);
	irkod_i_id_geti(line_r)->look(line_r, "line_r");
	struct irkod_thing *line_v1 = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_v1, irkod_orientation_vertical);
	irkod_i_id_geti(line_v1)->look(line_v1, "line_v1");
	struct irkod_thing *line_v2 = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_v2, irkod_orientation_vertical);
	irkod_i_id_geti(line_v2)->look(line_v2, "line_v2");
	
	struct irkod_thing *text_A = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_A, "A", IRKOD_FAIL);
	irkod_i_id_geti(text_A)->look(text_A, "text_A");
	struct irkod_thing *text_B = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_B, "B", IRKOD_FAIL);
	irkod_i_id_geti(text_B)->look(text_B, "text_B");
	struct irkod_thing *text_C = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_C, "C", IRKOD_FAIL);
	irkod_i_id_geti(text_C)->look(text_C, "text_C");
	struct irkod_thing *text_D = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_D, "D", IRKOD_FAIL);
	irkod_i_id_geti(text_D)->look(text_D, "text_D");
	struct irkod_thing *text_E = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_E, "E", IRKOD_FAIL);
	irkod_i_id_geti(text_E)->look(text_E, "text_E");
	struct irkod_thing *text_F = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_F, "F", IRKOD_FAIL);
	irkod_i_id_geti(text_A)->look(text_F, "text_F");

	irkod_grid_insert(text_A,
		       	line_l, line_u, line_h1, line_v1);  
	irkod_grid_insert(text_B, line_v1, line_u,  line_h1, line_v2);
	irkod_grid_insert(text_C, line_l, line_h1, line_h2, line_v2);
	irkod_grid_insert(text_D, line_l, line_h2, line_d, line_v2);
	irkod_grid_insert(text_E, line_v2, line_u, line_h3, line_r);
	irkod_grid_insert(text_F, line_v2, line_h3, line_d, line_r);
	
	printf("TRAVERSING START\n");
	irkod_grid_traverse(line_l, line_r, irkod_direction_forward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_r, line_l, irkod_direction_backward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_u, line_d, irkod_direction_forward, &functors, IRKOD_FAIL);
	printf("TRAVERSING\n");
	irkod_grid_traverse(line_d, line_u, irkod_direction_backward, &functors, IRKOD_FAIL);
	printf("TRAVERSING STOP\n");

	IRKOD_THING_DETACH(line_u);
	IRKOD_THING_DETACH(line_d);
	IRKOD_THING_DETACH(line_h1);
	IRKOD_THING_DETACH(line_h2);
	IRKOD_THING_DETACH(line_h3);
	IRKOD_THING_DETACH(line_l);
	IRKOD_THING_DETACH(line_r);
	IRKOD_THING_DETACH(line_v1);
	IRKOD_THING_DETACH(line_v2);
	IRKOD_THING_DETACH(text_A);
	IRKOD_THING_DETACH(text_B);
	IRKOD_THING_DETACH(text_C);
	IRKOD_THING_DETACH(text_D);
	IRKOD_THING_DETACH(text_E);
	IRKOD_THING_DETACH(text_F);

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
