#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <irkod/irkod.h>

const char *main_text_module_id = "test_text";
IRKOD_FAIL_FILE(main_text_module_id);

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(0);

	struct irkod_text *t = irkod_text_new(IRKOD_FAIL);
	irkod_text_init_mprintf(t, IRKOD_FAIL, "Ala ma %d koty %s.\nI %d ma %s też.\n", 3, "syjamskie", 5, "koni");
	struct irkod_i_str *i_str = irkod_i_str_geti(IRKOD_THING(t));

	printf(i_str->get(IRKOD_THING(t)));

	irkod_i_str_owner_geti(IRKOD_THING(t))->append(IRKOD_THING(t), "To tyle.", IRKOD_FAIL);
	printf(i_str->get(IRKOD_THING(t)));
	
	IRKOD_THING_DETACH(IRKOD_THING(t));

	IRKOD_FAIL_PRINT(stdout);
	
	IRKOD_FAIL_ROOT_FREE;
	return 0;
}
