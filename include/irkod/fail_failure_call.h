#ifndef IRKOD_FAIL_FAILURE_CALL_H
#define IRKOD_FAIL_FAILURE_CALL_H

#include <irkod/fail_failure_and_details.h>

struct irkod_fail_failure_and_details irkod_fail_failure_call();

#define IRKOD_FAIL_SET_ON_CALL_FAILURE \
do \
{ \
	assert(irkod_fail_node); \
\
	if(irkod_fail_node->next->file) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_call()); \
	} \
} while(0)

#define IRKOD_FAIL_RETURN_ON_CALL_FAILURE \
do \
{ \
	assert(irkod_fail_node); \
\
	if(irkod_fail_node->next->file) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_call()); \
		return; \
	} \
} while(0)

#define IRKOD_FAIL_RETURN_RESULT_ON_CALL_FAILURE(result) \
do \
{ \
	assert(irkod_fail_node); \
\
	if(irkod_fail_node->next->file) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_call()); \
		return (result); \
	} \
} while(0)

#endif /* !IRKOD_FAIL_FAILURE_CALL_H */
