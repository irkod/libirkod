#ifndef IRKOD_TEXT_H
#define IRKOD_TEXT_H

#include <stddef.h>
#include <irkod/fail.h>
#include <irkod/thing.h>

struct irkod_text
{
	char *str;
	int owns;
	IRKOD_THING_MEMBER;
};

void irkod_text_init_look(struct irkod_thing *it, char *str);
void irkod_text_init_take(struct irkod_thing *it, char *str);
void irkod_text_init_copy(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM);
void irkod_text_init_mprintf(struct irkod_thing *it, IRKOD_FAIL_PARAM, const char *format, ...);
void irkod_text_clear(struct irkod_thing *it);
IRKOD_THING_DECLARE(irkod_text);

#endif /* !IRKOD_TEXT_H */
