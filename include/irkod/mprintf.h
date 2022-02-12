#ifndef IRKOD_MPRINTF_H
#define IRKOD_MPRINTF_H

char *irkod_mprintf(const char *format, ...);
size_t irkod_vmprintf_size(const char *format, va_list ap);
char *irkod_vmprintf_str(const char *format, size_t size, va_list ap);

#endif /* !IRKOD_MPRINTF_H */

