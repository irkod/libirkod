#ifndef IRKOD_THING_H
#define IRKOD_THING_H

#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <irkod/common.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_attach_count.h>
#include <irkod/fail_failure_malloc.h>

struct irkod_thing;
typedef const char *irkod_thing_i_id_t;
typedef void (*irkod_thing_functor_t)(struct irkod_thing *it, void *data, IRKOD_FAIL_PARAM);
void *irkod_thing_get_i(struct irkod_thing *it, irkod_thing_i_id_t *id);

struct irkod_thing_i_table_entry
{
	irkod_thing_i_id_t *id;
	void *i;
};

struct irkod_thing_data
{
	const char *type_name;
	struct irkod_thing_i_table_entry *i_table;
	void (*attach)(struct irkod_thing *it);
	void (*detach)(struct irkod_thing *it);
};

struct irkod_thing
{
	struct irkod_thing_data *data;
	size_t attach_count;
};

#define IRKOD_THING_MEMBER \
struct irkod_thing irkod_thing

#define IRKOD_THING(object) \
(&(object)->irkod_thing)	

#define IRKOD_THING_GET_OBJECT(object_type, it) \
	(struct object_type*)((char*)(it) - offsetof(struct object_type, irkod_thing))

#define IRKOD_THING_DECLARE_I_ID(interface) \
extern irkod_thing_i_id_t interface ## _i_id; \
struct interface *interface ## _geti(struct irkod_thing *it)


#define IRKOD_THING_DEFINE_I_ID(interface) \
irkod_thing_i_id_t interface ## _i_id = #interface; \
struct interface *interface ## _geti(struct irkod_thing *it) \
{ \
	return (struct interface *) irkod_thing_get_i((it), &interface ## _i_id); \
}

#define IRKOD_THING_ATTACH(it) \
it->data->attach((it))

#define IRKOD_THING_DETACH(it) \
it->data->detach(it)

#define IRKOD_THING_NEW_DECLARE(type) \
struct irkod_thing *type ## _new(struct irkod_fail_node *irkod_fail_node)

#define IRKOD_THING_DECLARE(type) \
IRKOD_THING_NEW_DECLARE(type)


#define IRKOD_THING_BEGIN \
static void irkod_thing_attach(struct irkod_thing *it); \
static void irkod_thing_detach(struct irkod_thing *it); \
\
static struct irkod_thing_i_table_entry irkod_i_table[] = \
{

#define IRKOD_THING_I(interface) \
	{ &interface ## _i_id, &interface },

#define IRKOD_THING_END(type) \
	{ NULL, NULL } \
}; \
IRKOD_THING_DATA_DEFINE(type) \
IRKOD_THING_NEW_DEFINE(type) \
IRKOD_THING_ATTACH_DEFINE \
IRKOD_THING_DETACH_DEFINE(type) 

#define IRKOD_THING_WITH_CLEAR_END(type) \
	{ NULL, NULL } \
}; \
IRKOD_THING_DATA_DEFINE(type) \
IRKOD_THING_NEW_DEFINE(type) \
IRKOD_THING_ATTACH_DEFINE \
IRKOD_THING_DETACH_WITH_CLEAR_DEFINE(type) \

#define IRKOD_THING_DATA_DEFINE(type) \
static struct irkod_thing_data irkod_thing_data = \
{ \
	#type, \
	irkod_i_table, \
	&irkod_thing_attach, \
       	&irkod_thing_detach \
}; 

#define IRKOD_THING_NEW_DEFINE(type) \
struct irkod_thing * \
type ## _new(IRKOD_FAIL_PARAM) \
{ \
	IRKOD_FAIL_NEXT_WITH_RESULT(NULL); \
\
	struct type *object = malloc(sizeof(struct type)); \
\
	if(!object) \
	{ \
		IRKOD_FAIL_SET(irkod_fail_failure_malloc()); \
		return NULL; \
	} \
\
	object->irkod_thing.attach_count = 1; \
	return IRKOD_THING(object); \
}

#define IRKOD_THING_ATTACH_DEFINE \
static void  \
irkod_thing_attach(struct irkod_thing *it) \
{ \
	assert(it); \
	assert(it->attach_count); \
\
	++it->attach_count; \
\
	assert(it->attach_count); \
\
} 

#define IRKOD_THING_DETACH_DEFINE(type) \
void \
irkod_thing_detach(struct irkod_thing *it) \
{ \
	assert(it); \
	assert(it->attach_count); \
\
	if(!--it->attach_count) \
		free(IRKOD_THING_GET_OBJECT(type, it)); \
}

#define IRKOD_THING_DETACH_WITH_CLEAR_DEFINE(type) \
void \
irkod_thing_detach(struct irkod_thing *it) \
{ \
	assert(it); \
	assert(it->attach_count); \
\
	if(!--it->attach_count) \
	{ \
		type ## _clear(it); \
		free(IRKOD_THING_GET_OBJECT(type, it)); \
	} \
}

#define IRKOD_THING_INIT(object) \
(object)->irkod_thing.data = &irkod_thing_data;

#endif /* !IRKOD_THING_H */
