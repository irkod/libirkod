#include <assert.h>
#include <stddef.h>
#include <irkod/node.h>
#include <irkod/list.h>

void irkod_node_init(struct irkod_node *node, void *object)
{
	assert(node);
	assert(object);

	node->next = NULL;
	node->previous = NULL;
	node->list = NULL;
	node->object = object;
}

void *irkod_node_get_object(const struct irkod_node *node)
	
{
	assert(node);
	assert(node->object);

	return node->object;
}

void irkod_node_append(struct irkod_node *node, struct irkod_node *next)
{
	assert(node);
	assert(!node->next);
	assert(node->list);
	assert(node->list->last == node);

	if(!node->previous)
	{
		assert(node->list->first == node);
	}

	assert(next);
	assert(!next->previous);
	assert(!next->list);

	node->next = next;
	next->previous = node;
	next->list = node->list;

	node->list->last = next;
	++node->list->size;

	assert(node->list->size);
}

void *irkod_node_remove(struct irkod_node *node)
{
	assert(node);
	assert(node->list);

	if(!node->previous && !node->next)
	{
		assert(node->list->size == 1);
	}

	if(!node->previous)
	{
		assert(node->list->first == node);
		
		node->list->first = node->next;
	}
	else
		assert(node->list->first != node);

	if(!node->next)	
	{
		assert(node->list->last == node);
		
		node->list->last = node->previous;
	}
	else
		assert(node->list->last != node);

	if(node->previous)
	{
		assert(node->previous->next == node);
		assert(node->previous->list == node->list);
		
		node->previous->next = node->next;
	}

	if(node->next)
	{
		assert(node->next->previous == node);
		assert(node->next->list == node->list);
	
		node->next->previous = node->previous;
	}
	
	node->previous = NULL;
	node->next = NULL;

	--node->list->size;

	node->list = NULL;
	return node->object;
}

