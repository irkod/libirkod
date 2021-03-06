#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <irkod/mprintf.h>


char *irkod_mprintf(const char *format, ...)
{
	va_list ap;
	int size_0;
	int size_1;
	char *buffer = NULL;

	va_start(ap, format);
	size_0 = vsnprintf(buffer, 0, format, ap);
	va_end(ap);		

	buffer = malloc(size_0 + 1);

	if(!buffer)
		return NULL;
	
	va_start(ap, format);
	size_1 = vsnprintf(buffer, size_0 + 1, format, ap);
	va_end(ap);

	assert(size_1 == size_0);

	return buffer;
}

size_t irkod_vmprintf_size(const char *format, va_list ap)
{
	char *buffer = NULL;

	return vsnprintf(buffer, 0, format, ap);
}

char *irkod_vmprintf_str(const char *format, size_t size, va_list ap)
{
	int size_2;
	char *buffer;

	buffer = malloc(size + 1);

	if(!buffer)
		return NULL;
	
	size_2 = vsnprintf(buffer, size + 1, format, ap);

	assert(size_2 == size);

	return buffer;
}
