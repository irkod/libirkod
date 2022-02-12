#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <irkod/irkod.h>

const char *program_id = "main_list";
IRKOD_FAIL_FILE(program_id);

void dump(struct irkod_list *obj);
void dump2(struct irkod_list *obj, IRKOD_FAIL_PARAM);
void dump3(struct irkod_list *it, IRKOD_FAIL_PARAM);

int main()
{
	IRKOD_FAIL_ROOT;
	IRKOD_FAIL_NEXT_WITH_RESULT(0);

	struct irkod_list l;
	irkod_list_init(&l);

	struct irkod_text *t1 = irkod_text_new(IRKOD_FAIL);
	irkod_text_init_copy(t1, "ala1", IRKOD_FAIL);

	struct irkod_text *t2 = irkod_text_new(IRKOD_FAIL);
	irkod_text_init_copy(t2, "ala2", IRKOD_FAIL);
	
	struct irkod_text *t3 = irkod_text_new(IRKOD_FAIL);;
	irkod_text_init_copy(t3, "ala3", IRKOD_FAIL);

	struct irkod_node n1;
	irkod_node_init(&n1, IRKOD_THING(t1));

	struct irkod_node n2;
	irkod_node_init(&n2, IRKOD_THING(t2));

	struct irkod_node n3;
	irkod_node_init(&n3, IRKOD_THING(t3));


	irkod_list_append(&l, &n1);
	dump3(&l, IRKOD_FAIL);
	
	irkod_list_append(&l, &n2);
	dump3(&l, IRKOD_FAIL);
	
	irkod_list_append(&l, &n3);
	dump3(&l, IRKOD_FAIL);

	irkod_i_keeper_geti(IRKOD_THING(&l))->clear(IRKOD_THING(&l));

/*
	irkod_node_remove(&n2);
	dump3(&l, IRKOD_FAIL);
	
	irkod_node_remove(&n1);
	dump3(&l, IRKOD_FAIL);

	irkod_node_remove(&n3);
	dump3(&l, IRKOD_FAIL);
*/
	IRKOD_FAIL_PRINT(stdout);
	IRKOD_FAIL_ROOT_FREE;
	return 0;	

}

void dump(struct irkod_list *obj)
{
	struct irkod_node *n = obj->first;


	printf ("{\n");

	while(n)
	{
		printf("%d %d %d\n", n->previous, n, n->next);
		n = n->next;
	}
	
	printf ("}\n");
}

void dump3(struct irkod_list *l, IRKOD_FAIL_PARAM)
{
	IRKOD_FAIL_NEXT;

	struct irkod_thing *t = IRKOD_THING(l);

	struct irkod_i_sequence *i_sequence = irkod_i_sequence_geti(t);
	i_sequence->reset(t);

	
	printf("%d {\n", irkod_i_size_geti(t)->get(t));

	void *peeked;
	struct irkod_thing *it;

	while(i_sequence->peek(t, &peeked))
	{
		it = peeked;
		printf("%s\n", irkod_i_str_geti(it)->get(it));
		i_sequence->next(t);
	}

	printf ("}\n");
}
