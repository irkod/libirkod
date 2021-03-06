#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_attach_count.h>
#include <irkod/fail_failure_call.h>
#include <irkod/fail_failure_errno.h>
#include <irkod/fail_failure_malloc.h>
#include <irkod/thing.h>
#include <irkod/text.h>
#include <irkod/mprintf.h>
#include <irkod/i_fail_details.h>

IRKOD_FAIL_FILE(irkod_module_id);

static struct irkod_thing *irkod_i_fail_details__dump(struct irkod_thing *it, IRKOD_FAIL_PARAM);

static struct irkod_i_fail_details irkod_i_fail_details =
{
	irkod_i_fail_details__dump
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_fail_details)
IRKOD_THING_END(irkod_fail_details_errno)

void irkod_fail_details_errno_init(struct irkod_thing *it, int error)
{
	assert(it);
	
	struct irkod_fail_details_errno *object = IRKOD_THING_GET_OBJECT(irkod_fail_details_errno, it);

	IRKOD_THING_INIT(object);
	object->error = error;
}

struct irkod_fail_failure_and_details
irkod_fail_failure_errno(int error)
{
	static struct irkod_fail_failure failure = { "irkod_errno", "system function failed" };
	struct irkod_fail_failure_and_details fad = { &failure, NULL };

	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(fad);

	struct irkod_thing *details = irkod_fail_details_errno_new(IRKOD_FAIL);

	IRKOD_FAIL_ON_FAILURE
	{
		IRKOD_FAIL_ROOT_FREE;
		return fad;
	}

	irkod_fail_details_errno_init(details, error);
	fad.details = details;
	IRKOD_FAIL_ROOT_FREE;
	return fad;
}

struct irkod_thing *irkod_i_fail_details__dump(struct irkod_thing *it, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT_WITH_RESULT(NULL);

	assert(it);

	struct irkod_fail_details_errno *object = IRKOD_THING_GET_OBJECT(irkod_fail_details_errno, it);

	struct irkod_thing *text = irkod_text_new(IRKOD_FAIL);
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);

	irkod_text_init_mprintf(text, IRKOD_FAIL, "{ errno:%d, strerror:%s }", object->error, strerror(object->error));
	IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(NULL);

	return text;
}
