#ifndef IRKOD_PAGE_LINE_DATA_H
#define IRKOD_PAGE_LINE_DATA_H

#include <irkod/common.h>
#include <irkod/page.h>

struct irkod_page_line_data
{
	irkod_page_coordinate_t width;
	irkod_page_coordinate_t where[irkod_direction_count];
};

void irkod_page_line_data_init(struct irkod_page_line_data *object);
void irkod_page_line_data_set_width(struct irkod_page_line_data *object, irkod_page_coordinate_t width);
irkod_page_coordinate_t irkod_page_line_data_get_width(struct irkod_page_line_data *object);
void irkod_page_line_data_push_to(struct irkod_page_line_data *object,
	       	irkod_page_coordinate_t where, enum irkod_direction direction);
void irkod_page_line_data_set_where(struct irkod_page_line_data *object,
	       	irkod_page_coordinate_t where, enum irkod_direction direction);
irkod_page_coordinate_t irkod_page_line_data_get_where(struct irkod_page_line_data *object, enum irkod_direction direction);
#endif /* !IRKOD_PAGE_LINE_DATA_H */
