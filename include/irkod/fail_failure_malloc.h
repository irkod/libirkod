#ifndef IRKOD_FAIL_FAILURE_MALLOC_H
#define IRKOD_FAIL_FAILURE_MALLOC_H

#include <stddef.h>
#include <irkod/fail_failure_and_details.h>

struct irkod_fail_failure_and_details irkod_fail_failure_malloc();

#define IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(pointer) \
do \
{ \
	assert(irkod_fail_node); \
\
	if((pointer) == NULL) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_malloc()); \
		return; \
	} \
} while(0)

#define IRKOD_FAIL_RETURN_RESULT_ON_MALLOC_FAILURE(pointer, result) \
do \
{ \
	assert(irkod_fail_node); \
\
	if((pointer) == NULL) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_malloc()); \
		return (result); \
	} \
} while(0)

#endif /* !IRKOD_FAIL_FAILURE_MALLOC_H */
