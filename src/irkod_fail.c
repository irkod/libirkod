#include <stddef.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <irkod/fail.h>
#include <irkod/fail_failure_malloc.h>
#include <irkod/i_fail_details.h>
#include <irkod/i_str.h>
#include <irkod/thing.h>

const char *irkod_module_id = "libirkod";
IRKOD_FAIL_FILE(irkod_module_id);

void 
irkod_fail_node_init(struct irkod_fail_node *object)
{
	assert(object);

	irkod_fail_node_erase(object);
	object->next = NULL;
}

void 
irkod_fail_node_erase(struct irkod_fail_node *object)
{
	assert(object);

	object->file = NULL;
	object->function_name = NULL;
	object->line = 0;
	object->failure = NULL;
	object->details = NULL;
}

void 
irkod_fail_set(struct irkod_fail_node *object, struct irkod_fail_file *file, const char *function_name, int line,
	struct irkod_fail_failure_and_details fad)
{
	assert(object);

	object->file = file;
	object->function_name = function_name;
	object->line = line;
	object->failure = fad.failure;
	object->details = fad.details;
}

int 
irkod_fail_node_append(struct irkod_fail_node *object)
{
	assert(object);
	assert(!object->file);
	assert(!object->function_name);
	assert(!object->line);
	assert(!object->failure);
	assert(!object->details);
	assert(!object->next);

	object->next = malloc(sizeof(struct irkod_fail_node));

	if(!object->next)
	{
		irkod_fail_set(object, &irkod_fail_file, __func__, __LINE__, irkod_fail_failure_malloc());
		return 0;
	}

	irkod_fail_node_init(object->next);
	return 1;
}

void 
irkod_fail_node_clear(struct irkod_fail_node *object)
{
	assert(object);

	if(object->details)
		IRKOD_THING_DETACH(object->details);		

	irkod_fail_node_erase(object);
}

void 
irkod_fail_nodes_clear(struct irkod_fail_node *object)
{
	while(object && object->file)
	{
		irkod_fail_node_clear(object);
		object = object->next;
	}
}

void 
irkod_fail_nodes_free(struct irkod_fail_node *object)
{
	struct irkod_fail_node *next;

	irkod_fail_nodes_clear(object);

	while(object)
	{
		next = object->next;
		free(object);
		object = next;
	}
}

void 
irkod_fail_nodes_print(struct irkod_fail_node *object, FILE *file)
{
	const char *info = 
		"error\n"
		"{\n"
	        " module:%s\n"
	        " file:%s\n"
	        " function:%s\n"
	        " line:%d \n"
		" id:%s \n"
		" message:%s\n"
		"}\n";
	const char *info_with_details = 
		"error\n"
		"{\n"
	        " module:%s\n"
	        " file:%s\n"
	        " function:%s\n"
	        " line:%d \n"
		" id:%s \n"
		" message:%s\n"
		" details:\n"
		" {\n"
		"  %s\n"
		" }\n"
		"}\n";
	struct irkod_thing *text = NULL;
	const char *dump = "";

	while(object && object->file)
	{
		if(object->details)
		{
			struct irkod_fail_node irkod_fail_node;
			irkod_fail_node_init(&irkod_fail_node);

			text = irkod_i_fail_details_geti(object->details)
				->dump(object->details, &irkod_fail_node);

			if(!irkod_fail_node.file)
			{
				dump = irkod_i_str_geti(text)->get(text);

				if(!dump)
					dump = "";
			}

			if(irkod_fail_node.next)
				irkod_fail_nodes_free(irkod_fail_node.next);

			irkod_fail_node_clear(&irkod_fail_node);

			fprintf(file, info_with_details, 
					*object->file->module_id,
					object->file->file_name,
					object->function_name,
					object->line,
					object->failure->id,
					object->failure->message,
					dump
			       );

			if(text)
				IRKOD_THING_DETACH(text);
		}
		else
			fprintf(file, info, 
					*object->file->module_id,
					object->file->file_name,
					object->function_name,
					object->line,
					object->failure->id,
					object->failure->message
			       );

		object = object->next;
	}
}

