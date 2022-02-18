#ifndef IRKOD_STR_OWNER_I_H
#define IRKOD_STR_OWNER_I_H

#include <irkod/thing.h>
#include <irkod/fail.h>

IRKOD_THING_DECLARE_I_ID(irkod_i_str_owner);

struct irkod_i_str_owner
{
	void (*look)(struct irkod_thing *it, char *str);
	void (*take)(struct irkod_thing *it, char *str);
	void (*copy)(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM);
	void (*append)(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM);
	void (*append_mprintf)(struct irkod_thing *it, IRKOD_FAIL_PARAM, const char *format, ...);
	int (*owns)(struct irkod_thing *it);
	const char *(*get)(struct irkod_thing *it);
};

#endif /* !IRKOD_STR_OWNER_I_H */
