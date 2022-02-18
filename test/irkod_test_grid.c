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

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(0);


	struct irkod_page_line *line_a = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_a, irkod_orientation_vertical);
	irkod_i_id_geti(IRKOD_THING(line_a))->look(IRKOD_THING(line_a), "line_a");
	struct irkod_page_line *line_b = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_b, irkod_orientation_horizontal);
	irkod_i_id_geti(IRKOD_THING(line_b))->look(IRKOD_THING(line_b), "line_b");
	struct irkod_page_line *line_c = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_c, irkod_orientation_horizontal);
	irkod_i_id_geti(IRKOD_THING(line_c))->look(IRKOD_THING(line_c), "line_c");
	struct irkod_page_line *line_d = irkod_page_line_new(IRKOD_FAIL);
	irkod_page_line_init(line_d, irkod_orientation_vertical);
	irkod_i_id_geti(IRKOD_THING(line_d))->look(IRKOD_THING(line_d), "line_d");

	struct irkod_page_field_text *text_A = irkod_page_field_text_new(IRKOD_FAIL);
	irkod_page_field_text_init(text_A, "Ala", IRKOD_FAIL);
	irkod_i_id_geti(IRKOD_THING(text_A))->look(IRKOD_THING(text_A), "text_A");
	irkod_grid_insert(IRKOD_THING(text_A),
		       	IRKOD_THING(line_a), IRKOD_THING(line_b), IRKOD_THING(line_c), IRKOD_THING(line_d));  

	struct irkod_thing *dump = irkod_i_dump_geti(IRKOD_THING(line_a))->get(IRKOD_THING(line_a), NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(IRKOD_THING(line_b))->get(IRKOD_THING(line_b), NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(IRKOD_THING(line_c))->get(IRKOD_THING(line_c), NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(IRKOD_THING(line_d))->get(IRKOD_THING(line_d), NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);
	
	dump = irkod_i_dump_geti(IRKOD_THING(text_A))->get(IRKOD_THING(text_A), NULL, IRKOD_FAIL);
	printf("%s\n", irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);

	IRKOD_THING_DETACH(IRKOD_THING(line_a));
	IRKOD_THING_DETACH(IRKOD_THING(line_b));
	IRKOD_THING_DETACH(IRKOD_THING(line_c));
	IRKOD_THING_DETACH(IRKOD_THING(line_d));
	IRKOD_THING_DETACH(IRKOD_THING(text_A));

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
