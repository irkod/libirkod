#ifndef IRKOD_LIST_H
#define IRKOD_LIST_H

#include <stddef.h>
#include <irkod/node.h>
#include <irkod/thing.h>

struct irkod_list
{
	struct irkod_node *first;
	struct irkod_node *last;
	struct irkod_node *sequence;
	size_t size;
	IRKOD_THING_MEMBER;
};

void irkod_list_init(struct irkod_thing *it);
void irkod_list_append(struct irkod_list *list, struct irkod_node *node);
size_t irkod_list_get_size(const struct irkod_list *list);
void irkod_list_clear(struct irkod_thing *it);
IRKOD_THING_DECLARE(irkod_list);

#endif /* IRKOD_LIST_H */
