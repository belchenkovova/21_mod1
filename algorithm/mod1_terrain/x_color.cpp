#include "mod1_terrain.h"

void					mod1_terrain::push_color(const mod1_point3<float> &color)
{
	data_color.push_back(color);
}

mod1_point3<float>		mod1_terrain::compute_color(const float &height) const
{
	float				ratio;
	int 				index_from;
	int 				index_to;
	float				ratio_normal;
	mod1_point3<float>	result;

	if (data_color.empty())
		throw (exception_color());
	if (data_color.size() == 1)
		return (data_color[0]);
	ratio = height / max_raw.z * (float)(data_color.size() - 1);

	index_from = floor(ratio);
	index_to = index_from + 1;
	ratio_normal = ratio - floor(ratio);

	if (index_to == data_color.size())
		return (data_color[index_from]);

	for (int i = 0; i < 3; i++)
		result[i] = interpolate_linear(data_color[index_from][i], data_color[index_to][i], ratio_normal);
	result = mod1_point3<float>::min(result, mod1_point3<float>(1.f));
	return (result);
}