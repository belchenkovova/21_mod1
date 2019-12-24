#include "mod1_map.h"

float					*mod1_map::model_get_ptr(const mod1_point2<int> &iter, mod1_map_slot slot)
{
	float				*ptr;

	ptr = nullptr;
	if (slot == mod1_map_slot_point)
		ptr = data.point_array.data();
	else if (slot == mod1_map_slot_normal)
		ptr = data.normal_array.data();
	else if (slot == mod1_map_slot_color)
		ptr = data.color_array.data();
	else
		global_error->raise_error("Map : Incorrect slot");
	return (ptr + 3 * model_get_index(iter));
}

mod1_point2<int>		mod1_map::model_find_ptr(const mod1_point3<int> &object)
{
	mod1_point2<int>	iter;
	float 				*ptr;

	for (iter.y = 0; iter.y < model_size.y; iter.y++)
		for (iter.x = 0; iter.x < model_size.x; iter.x++)
		{
			ptr = model_get_ptr(iter, mod1_map_slot_point);
			if ((int)ptr[0] == object.x && (int)ptr[2] == object.y)
				return (iter);
		}
	global_error->raise_error("Map : Point (%d, %d) not found", object.x, object.y);
	return (iter);
}