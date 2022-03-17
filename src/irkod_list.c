#include <assert.h>
#include <stddef.h>
#include <irkod/list.h>
#include <irkod/node.h>
#include <irkod/i_sequence.h>
#include <irkod/i_size.h>
#include <irkod/i_keeper.h>
#include <irkod/fail_failure_attach_count.h>
#include <irkod/fail_failure_call.h>
#include <irkod/fail_failure_malloc.h>

IRKOD_FAIL_FILE(irkod_module_id);

static void irkod_i_sequence__reset(struct irkod_thing *it);
static int irkod_i_sequence__peek(struct irkod_thing *it, struct irkod_thing **thing);
static void irkod_i_sequence__next(struct irkod_thing *it);
static size_t irkod_i_size__get(const struct irkod_thing *it);
static void irkod_i_keeper__add(struct irkod_thing *it, struct irkod_node *node, IRKOD_FAIL_PARAM);
static void irkod_i_keeper__clear(struct irkod_thing *it);

static struct irkod_i_sequence irkod_i_sequence =
{
	irkod_i_sequence__reset,
	irkod_i_sequence__peek,
	irkod_i_sequence__next
};

static struct irkod_i_size irkod_i_size =
{
	irkod_i_size__get
};

static struct irkod_i_keeper irkod_i_keeper =
{
	irkod_i_keeper__add,
	irkod_i_keeper__clear
};

IRKOD_THING_BEGIN
	IRKOD_THING_I(irkod_i_sequence)
	IRKOD_THING_I(irkod_i_size)
	IRKOD_THING_I(irkod_i_keeper)
IRKOD_THING_WITH_CLEAR_END(irkod_list)

void irkod_list_init(struct irkod_thing *it)
{
	assert(it);
	struct irkod_list *object = IRKOD_THING_GET_OBJECT(irkod_list, it);

	IRKOD_THING_INIT(object);
	object->first = NULL;	
	object->last = NULL;
	object->sequence = NULL;
	object->size = 0;	
}

void irkod_list_clear(struct irkod_thing *it)
{
	assert(it);

	struct irkod_list *object = IRKOD_THING_GET_OBJECT(irkod_list, it);

	while(object->first)
		irkod_node_remove(object->first);
}

void irkod_list_append(struct irkod_list *list, struct irkod_node *node)
{
	assert(list);
	assert(node);

	if(!list->size)
	{
		assert(!list->first);
		assert(!list->last);

		list->first = node;
		list->last = node;
		node->list = list;
		list->size = 1;
	}
	else
	{
		assert(list->first);
		assert(list->last);

		irkod_node_append(list->last, node);
	}

	assert(list->size);
}

size_t irkod_list_get_size(const struct irkod_list *list)
{
	assert(list);

	return list->size;
}

void irkod_i_sequence__reset(struct irkod_thing *it)
{
	assert(it);

	struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);
	
	list->sequence = list->first;
}

int irkod_i_sequence__peek(struct irkod_thing *it, struct irkod_thing **thing)
{
	assert(it);
	assert(thing);
	
	struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);

	if(!list->sequence)
		return 0;
	
	*thing = list->sequence->thing;
	return 1;
}

void irkod_i_sequence__next(struct irkod_thing *it)
{
	assert(it);

	struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);

	if(list->sequence)
		list->sequence = list->sequence->next;

}

size_t irkod_i_size__get(const struct irkod_thing *it)
{
	assert(it);
	const struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);

	return list->size;
}

void irkod_i_keeper__add(struct irkod_thing *it, struct irkod_node *node, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	assert(it);
	assert(node);

	struct irkod_thing *thing = irkod_node_get_thing(node);
	
	IRKOD_THING_ATTACH(thing, IRKOD_FAIL);
	IRKOD_FAIL_RETURN_ON_CALL_FAILURE;

	struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);

	irkod_list_append(list, node);
}

void irkod_i_keeper__clear(struct irkod_thing *it)
{
	assert(it);

	struct irkod_list *list = IRKOD_THING_GET_OBJECT(irkod_list, it);

	while(list->first)
	{
		struct irkod_thing *it = irkod_node_remove(list->first);
		
		assert(it);

		IRKOD_THING_DETACH(it);
	}
}
