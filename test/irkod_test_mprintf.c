#include <irkod/irkod.h>
#include <stdio.h>
#include <malloc.h>

int main()
{
	char *s = irkod_mprintf("%s ma %d %s\n", "Ala", 7, "kotów");
	printf(s);
	free(s);
	return 0;
}
