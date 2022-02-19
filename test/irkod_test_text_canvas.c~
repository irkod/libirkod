#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "irkod/irkod.h"

const char *main_text_program_id = "main_text";
IRKOD_FAIL_FILE(main_text_program_id);

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(0);

	setlocale(LC_ALL, "");
	struct irkod_text_canvas *tc = irkod_text_canvas_new(IRKOD_FAIL);
	irkod_text_canvas_init(tc);
	struct irkod_i_text_canvas *i_tc_canvas = irkod_i_text_canvas_geti(IRKOD_THING(tc));
	struct irkod_i_row_cursor *i_tc_cursor = irkod_i_row_cursor_geti(IRKOD_THING(tc));


	i_tc_canvas->resize(IRKOD_THING(tc), 20, 40, IRKOD_FAIL);

	for(int r = 0; r < 20; r++)
		for(int c = 0; c < 40; c++)
		{
			i_tc_canvas->put(IRKOD_THING(tc), r, c, "ć", IRKOD_FAIL);
			IRKOD_FAIL_PRINT(stdout);
		}

	int k = 0;
	int i = 0;

	for(;;)
	{
		int size = i_tc_canvas->put(IRKOD_THING(tc), 0, k++, "zażółć gęślą jaźń!" + i, IRKOD_FAIL);
		i += size;

		if(!size)
			break;

		IRKOD_FAIL_PRINT(stdout);
	}

	i_tc_cursor->set(IRKOD_THING(tc), 3);
	i_tc_canvas->print(IRKOD_THING(tc), stdout, IRKOD_FAIL);
	i_tc_canvas->resize(IRKOD_THING(tc), 10, 30, IRKOD_FAIL);
	
	IRKOD_THING_DETACH(IRKOD_THING(tc));

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
