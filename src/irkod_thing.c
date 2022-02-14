#include <stddef.h>
#include <irkod/thing.h>

void *irkod_thing_get_i(struct irkod_thing *it, irkod_thing_i_id_t *id)
{
	struct irkod_thing_i_table_entry *entry = it->data->i_table;

	while(entry->id)
	{
		if(entry->id == id)
			return entry->i;

		++entry;
	}

	fprintf(stderr, "%s does not implement %s interface\n", it->data->type_name, *id); 
	abort(); 
}

