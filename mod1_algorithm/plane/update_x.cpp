#include "plane.h"

using namespace			mod1_algorithm;

void	 				plane::update_normal_helper(
						const int &index_a,
						const int &index_b,
						const int &index_c)
{
	float 				*ptr_a;
	float 				*ptr_b;
	float 				*ptr_c;
	float 				*ptr_n;

	point3<float>		a;
	point3<float>		b;
	point3<float>		c;

	point3<float>		normal;

	ptr_a = (float *) mod1_engine_gl::model::pointer(index_a, model_slot::point);
	ptr_b = (float *) mod1_engine_gl::model::pointer(index_b, model_slot::point);
	ptr_c = (float *) mod1_engine_gl::model::pointer(index_c, model_slot::point);

	a = point3<float>(ptr_a, point3<float>::convention_xzy);
	b = point3<float>(ptr_b, point3<float>::convention_xzy);
	c = point3<float>(ptr_c, point3<float>::convention_xzy);

	normal = point3<float>::cross(c - a, b - a).normalized();

	ptr_n = (float *) mod1_engine_gl::model::pointer(index_a, model_slot::normal);
	normal.write_to_ptr(ptr_n, point3<float>::convention_xzy);
}

void					plane::update_normal()
{
	point2<int>			iter;

	int					top_left;
	int					top_right;
	int					bottom_left;
	int					bottom_right;

	for (iter.y = 0; iter.y < MOD1_INTERNAL(size).y - 1; iter.y++)
		for (iter.x = 0; iter.x < MOD1_INTERNAL(size).x - 1; iter.x++)
		{
			top_left = pointer(point2<int>(iter.x, iter.y),
							   is_dual(iter) ? index_convention::dual_second : index_convention::dual_first);
			top_right = pointer(point2<int>(iter.x + 1, iter.y), index_convention::dual_first);
			bottom_left = pointer(point2<int>(iter.x, iter.y + 1));
			bottom_right = pointer(point2<int>(iter.x + 1, iter.y + 1));

			if (get_cut_style(iter) == cut_style::upwards)
			{
				update_normal_helper(top_left, bottom_left, top_right);
				update_normal_helper(top_right, bottom_left, bottom_right);
			}
			else
			{
				update_normal_helper(top_left, bottom_left, bottom_right);
				update_normal_helper(top_right, top_left, bottom_right);
			}
		}
}

void 					plane::update_final()
{
	point2<int>			iter;
	float				*ptr;
	point3<float>		point;


	MOD1_INTERNAL(final_min) = point3<float>(std::numeric_limits<float>::max());
	MOD1_INTERNAL(final_max) = point3<float>(std::numeric_limits<float>::min());
	for (iter.y = 0; iter.y < MOD1_INTERNAL(size).y - 1; iter.y++)
		for (iter.x = 0; iter.x < MOD1_INTERNAL(size).x - 1; iter.x++)
		{
			ptr = (float *) pointer(iter, model_slot::point);
			point = point3<float>(ptr[0], ptr[2], ptr[1]);
			MOD1_INTERNAL(final_min) = point3<float>::min(MOD1_INTERNAL(final_min), point);
			MOD1_INTERNAL(final_max) = point3<float>::max(MOD1_INTERNAL(final_max), point);
		}
}