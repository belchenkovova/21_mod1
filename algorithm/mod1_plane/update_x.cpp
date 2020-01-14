#include "mod1_plane.h"

void	 				mod1_plane::update_normal_helper(
						const int &index_a,
						const int &index_b,
						const int &index_c)
{
	float 				*ptr_a;
	float 				*ptr_b;
	float 				*ptr_c;
	float 				*ptr_n;

	point3<float>	a;
	point3<float>	b;
	point3<float>	c;

	point3<float>	normal;

	ptr_a = (float *)model::get_ptr(index_a, model_data::slot_point);
	ptr_b = (float *)model::get_ptr(index_b, model_data::slot_point);
	ptr_c = (float *)model::get_ptr(index_c, model_data::slot_point);


	a = point3<float>(ptr_a, point3<float>::convention_xzy);
	b = point3<float>(ptr_b, point3<float>::convention_xzy);
	c = point3<float>(ptr_c, point3<float>::convention_xzy);

	normal = point3<float>::cross(c - a, b - a).normalized();

	ptr_n = (float *)model::get_ptr(index_a, model_data::slot_normal);
	normal.write_to_ptr(ptr_n, point3<float>::convention_xzy);
}

void					mod1_plane::update_normal()
{
	point2<int>	iter;

	int					top_left;
	int					top_right;
	int					bottom_left;
	int					bottom_right;


	for (iter.y = 0; iter.y < size_internal.y - 1; iter.y++)
		for (iter.x = 0; iter.x < size_internal.x - 1; iter.x++)
		{
			top_left = get_index(point2<int>(iter.x, iter.y),
				is_dual(iter) ? convention_dual_second : convention_dual_first);
			top_right = get_index(point2<int>(iter.x + 1, iter.y), convention_dual_first);
			bottom_left = get_index(point2<int>(iter.x, iter.y + 1));
			bottom_right = get_index(point2<int>(iter.x + 1, iter.y + 1));

			update_normal_helper(top_left, bottom_left, top_right);
			update_normal_helper(top_right, bottom_left, bottom_right);
		}
}

void 					mod1_plane::update_final()
{
	point2<int>	iter;
	float				*ptr;
	point3<float>	point;


	final_min_internal = point3<float>(std::numeric_limits<float>::max());
	final_max_internal = point3<float>(std::numeric_limits<float>::min());
	for (iter.y = 0; iter.y < size_internal.y - 1; iter.y++)
		for (iter.x = 0; iter.x < size_internal.x - 1; iter.x++)
		{
			ptr = (float *)get_ptr(iter, model_data::slot_point);
			point = point3<float>(ptr[0], ptr[2], ptr[1]);
			final_min_internal = point3<float>::min(final_min_internal, point);
			final_max_internal = point3<float>::max(final_max_internal, point);
		}
}