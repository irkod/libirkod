#ifndef IRKOD_COMMON_H
#define IRKOD_COMMON_H

enum irkod_orientation
{
	irkod_orientation_horizontal,
	irkod_orientation_vertical,
	irkod_orientation_count
};

#define IRKOD_ORIENTATION_OPPOSITE(v) (1 - (v))

enum irkod_direction
{
	irkod_direction_backward,
	irkod_direction_forward,
	irkod_direction_count
};

#define IRKOD_DIRECTION_OPPOSITE(v) (1 - (v))

enum irkod_side
{
	irkod_side_none = 0,
	irkod_side_up_left = 1,
	irkod_side_up = 2,
	irkod_side_up_right = 4,
	irkod_side_right = 8,
	irkod_side_down_right = 16,
	irkod_side_down = 32,
	irkod_side_down_left = 64,
	irkod_side_left = 128,
	irkod_side_all_up = irkod_side_up_left + irkod_side_up + irkod_side_up_right,
	irkod_side_all_right = irkod_side_up_right + irkod_side_right + irkod_side_down_right,
	irkod_side_all_down = irkod_side_down_right + irkod_side_down + irkod_side_down_left,
	irkod_side_all_left = irkod_side_down_left + irkod_side_left + irkod_side_up_left,
	irkod_side_all = irkod_side_up_left + irkod_side_up + irkod_side_up_right
	       		+ irkod_side_right
		       	+ irkod_side_down_right + irkod_side_down + irkod_side_down_left
		       	+ irkod_side_left
};

#endif /* !IRKOD_COMMON_H */
