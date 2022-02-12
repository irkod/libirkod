#ifndef IRKOD_NODE_H
#define IRKOD_NODE_H

struct irkod_list;

struct irkod_node
{
	struct irkod_node *next;
	struct irkod_node *previous;
	struct irkod_list *list;
	void *object;
};

void irkod_node_init(struct irkod_node *node, void *object);
void *irkod_node_get_object(const struct irkod_node *node);
void irkod_node_append(struct irkod_node *node, struct irkod_node *next);
void *irkod_node_remove(struct irkod_node *node);

#endif /* !IRKOD_NODE_H */
