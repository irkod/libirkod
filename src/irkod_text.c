#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdarg.h>
#include <irkod/fail_failure_attach_count.h>
#include <irkod/fail_failure_call.h>
#include <irkod/fail_failure_malloc.h>
#include <irkod/text.h>
#include <irkod/thing.h>
#include <irkod/mprintf.h>
#include <irkod/i_str.h>
#include <irkod/i_str_owner.h>

IRKOD_FAIL_FILE(irkod_module_id);

static const char *irkod_i_str__get(struct irkod_thing *it);
static void irkod_i_str_owner__look(struct irkod_thing *it, char *str);
static void irkod_i_str_owner__take(struct irkod_thing *it, char *str);
static void irkod_i_str_owner__copy(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM);
static void irkod_i_str_owner__append(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM);
static void irkod_i_str_owner__append_mprintf(struct irkod_thing *it, IRKOD_FAIL_PARAM, const char *format, ...);
static int irkod_i_str_owner__owns(struct irkod_thing *it);

static void append(struct irkod_thing *it, const char *str, size_t size, IRKOD_FAIL_PARAM);

static struct irkod_i_str irkod_i_str =
{
	irkod_i_str__get
};

static struct irkod_i_str_owner irkod_i_str_owner =
{
	irkod_i_str_owner__look,
	irkod_i_str_owner__take,
	irkod_i_str_owner__copy,
	irkod_i_str_owner__append,
	irkod_i_str_owner__append_mprintf,
	irkod_i_str_owner__owns,
	irkod_i_str__get
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_str)
	IRKOD_THING_I(irkod_i_str_owner)
IRKOD_THING_WITH_CLEAR_END(irkod_text)

void 
irkod_text_init_look(struct irkod_thing *it, char *str)
{
	assert(it);
	assert(str);
	
	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	IRKOD_THING_INIT(object);
	object->str = str;
	object->owns = 0;
}

void 
irkod_text_init_take(struct irkod_thing *it, char *str)
{
	assert(it);
	assert(str);
	
	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	IRKOD_THING_INIT(object);
	object->str = str;
	object->owns = 1;
}

void 
irkod_text_init_copy(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM)
{
	assert(it);
	assert(str);
	
	char *new_str;
	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	IRKOD_THING_INIT(object);

	size_t size = strlen(str) + 1;

	assert(size);

	new_str = malloc(size);
	IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(new_str);

	strcpy(new_str, str);
	object->str = new_str;
	object->owns = 1;
}

void 
irkod_text_init_mprintf(struct irkod_thing *it, IRKOD_FAIL_PARAM, const char *format, ...)
{
	assert(it);
	assert(format);

	va_list ap;
	char *str;
	size_t size;
	
	va_start(ap, format);
	size = irkod_vmprintf_size(format, ap);
	va_end(ap);		

	va_start(ap, format);
	str = irkod_vmprintf_str(format, size, ap);
	va_end(ap);		

	IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(str);

	irkod_text_init_take(it, str);
}

void irkod_text_clear(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	if(object->owns)
	{
		free(object->str);
		object->owns = 0;
	}
	
	object->str = "";
}

const char *irkod_i_str__get(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	return object->str;
}

int irkod_i_str_owner__owns(struct irkod_thing *it)
{
	assert(it);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);
	return object->owns;
}

void irkod_i_str_owner__look(struct irkod_thing *it, char *str)
{
	assert(it);
	assert(str);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);
	
	if(object->owns)
		free(object->str);

	irkod_text_init_look(it, str);
}
void irkod_i_str_owner__take(struct irkod_thing *it, char *str)
{
	assert(it);
	assert(str);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);
	
	if(object->owns)
		free(object->str);

	irkod_text_init_take(it, str);
}

void irkod_i_str_owner__copy(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	assert(str);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);
	
	if(object->owns)
		free(object->str);

	irkod_text_init_copy(it, str, IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
}

void irkod_i_str_owner__append(struct irkod_thing *it, const char *str, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	assert(str);
	
	append(it, str, strlen(str), IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
}

void irkod_i_str_owner__append_mprintf(struct irkod_thing *it, IRKOD_FAIL_PARAM, const char *format, ...)
{
	IRKOD_FAIL_NEXT;
	
	assert(it);
	assert(format);

	va_list ap;
	char *str;
	size_t size;
	
	va_start(ap, format);
	size = irkod_vmprintf_size(format, ap);
	va_end(ap);		

	va_start(ap, format);
	str = irkod_vmprintf_str(format, size, ap);
	va_end(ap);		

	IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(str);

	append(it, str, size, IRKOD_FAIL);
		
	free(str);

	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;
}

void append(struct irkod_thing *it, const char *str, size_t size, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	assert(str);

	struct irkod_text *object = IRKOD_THING_GET_OBJECT(irkod_text, it);

	size_t my_size = strlen(object->str);

	if((size_t) - 2 - my_size < size)
	{
		IRKOD_FAIL_SET(irkod_fail_failure_malloc());
		return;
	}

	char *new_str = malloc(my_size + size + 1);
	IRKOD_FAIL_RETURN_ON_MALLOC_FAILURE(new_str);

	strcpy(new_str, object->str);
	strcat(new_str, str);

	if(object->owns)
		free(object->str);

	object->str = new_str;
	object->owns = 1;
}
