#ifndef IRKOD_PAGE_FIELD_TEXT_H
#define IRKOD_PAGE_FIELD_TEXT_H

#include <irkod/common.h>
#include <irkod/grid_field_data.h>
#include <irkod/text.h>
#include <irkod/fail.h>
#include <irkod/thing.h>

struct irkod_page_field_text
{
	struct irkod_grid_field_data grid_field_data;
	struct irkod_text text;
	IRKOD_THING_MEMBER;
};

void irkod_page_field_text_init(struct irkod_page_field_text *object, const char *text, IRKOD_FAIL_PARAM);
IRKOD_THING_DECLARE(irkod_page_field_text);

#endif /* !IRKOD_PAGE_FIELD_TEXT_H */
