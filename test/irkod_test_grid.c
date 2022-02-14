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
	

	struct irkod_thing *dump = irkod_i_dump_geti(IRKOD_THING(line_a))->get(IRKOD_THING(line_a), NULL, IRKOD_FAIL);
	printf(irkod_i_str_geti(dump)->get(dump));
	IRKOD_THING_DETACH(dump);

	IRKOD_THING_DETACH(IRKOD_THING(line_a));

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
