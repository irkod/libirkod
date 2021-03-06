#ifndef IRKOD_FAIL_H
#define IRKOD_FAIL_H

#include <stdio.h>
#include <assert.h>
#include <irkod/fail_failure_and_details.h>

struct irkod_thing;

typedef const char *irkod_fail_module_id_t;

struct irkod_fail_file
{
	irkod_fail_module_id_t *module_id;
	const char *file_name;
};

struct irkod_fail_failure
{
	const char *id;
	const char *message;
};

struct irkod_fail_node
{
	struct irkod_fail_file *file;
	const char *function_name;
	int line;
	struct irkod_fail_failure *failure;
	struct irkod_thing *details;
	struct irkod_fail_node *next;
};

void irkod_fail_node_init(struct irkod_fail_node *node);
void irkod_fail_node_erase(struct irkod_fail_node *node);
void irkod_fail_set(struct irkod_fail_node *node, struct irkod_fail_file *file, const char *function_name, int line,
	struct irkod_fail_failure_and_details fad);
int irkod_fail_node_append(struct irkod_fail_node *node);
void irkod_fail_node_clear(struct irkod_fail_node *node);
void irkod_fail_nodes_clear(struct irkod_fail_node *node);
void irkod_fail_nodes_free(struct irkod_fail_node *node);
void irkod_fail_nodes_print(struct irkod_fail_node *node, FILE *file);

extern irkod_fail_module_id_t irkod_module_id;

#define IRKOD_FAIL_PARAM struct irkod_fail_node *irkod_fail_node

#define IRKOD_FAIL irkod_fail_node->next

#define IRKOD_FAIL_FILE(module_id) \
static struct irkod_fail_file irkod_fail_file = \
	{ &module_id, __FILE__ }

#define IRKOD_FAIL_FAILURE(name, id, message) \
static struct irkod_fail_failure irkod_fail_local_ ## name ## _failure = \
	{ id, message }

#define IRKOD_FAIL_NEXT \
do \
{ \
	assert(irkod_fail_node); \
\
	if(!irkod_fail_node->next) \
		if(!irkod_fail_node_append(irkod_fail_node)) \
			return; \
} while(0)

#define IRKOD_FAIL_NEXT_WITH_RESULT(result) \
do \
{ \
	assert(irkod_fail_node); \
\
	if(!irkod_fail_node->next) \
		if(!irkod_fail_node_append(irkod_fail_node)) \
			return (result); \
} while(0)

#define IRKOD_FAIL_ROOT \
struct irkod_fail_node irkod_fail_root_node; \
struct irkod_fail_node *irkod_fail_node = &irkod_fail_root_node; \
irkod_fail_node_init(irkod_fail_node)

#define IRKOD_FAIL_ROOT_FREE \
irkod_fail_nodes_free(irkod_fail_root_node.next)

#define IRKOD_FAIL_ON_FAILURE \
	if(irkod_fail_node->next->file) 

#define IRKOD_FAIL_SET(fad) \
	irkod_fail_set(irkod_fail_node, &irkod_fail_file, __func__, __LINE__, fad)

#define IRKOD_FAIL_PRINT(file) \
irkod_fail_nodes_print(irkod_fail_node, file)

#define IRKOD_FAIL_CLEAR \
irkod_fail_nodes_clear(irkod_fail_node)

#endif /* !IRKOD_FAIL_H */
