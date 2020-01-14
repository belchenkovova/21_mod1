#pragma once

#include "mod1_main/mod1_macro.h"
#include "mod1_main/mod1_control.h"

#include "mod1_algorithm/namespace.h"

#include "mod1_libraries/FastNoise/FastNoise.h"
#include "mod1_algorithm/plane/plane.h"

#include <fstream>
#include <vector>

class						mod1_algorithm::terrain : private mod1_algorithm::plane
{
public :
							terrain() = default;
							~terrain() = default;

	MOD1_GENERATE_EXCEPTION_DEFINITION(exception_source, "Mod1 Terrain : Invalid source file")
	MOD1_GENERATE_EXCEPTION_DEFINITION(exception_pattern, "Mod1 Terrain : Invalid pattern")
	MOD1_GENERATE_EXCEPTION_DEFINITION(exception_search, "Mod1 Terrain : Can't find given point")

	void					parse(const std::string &file);
	void					build() final;

	class model				*model() override;

	void					info(const bool &raw = true, const bool &model = true) const;

	static float			interpolate_linear(float min, float max, float ratio);
	static float			interpolate_cosine(float min, float max, float ratio);
	static float			interpolate_smooth(float min, float max, float ratio);

	using					plane::add_color;

private :

	MOD1_TERRAIN_RAW_DATA	data_raw;
	point3<int>				min_raw = point3<int>(INT_MAX, INT_MAX, INT_MAX);
	point3<int>				max_raw = point3<int>(-INT_MAX, -INT_MAX, -INT_MAX);
	point3<int>				diff_raw;
	bool					case_one_point = false;

	static float			parse_coordinate(std::ifstream &stream, bool eat_delimiter);

	point2<int>				min_i;
	point2<int>				max_i;
	int						delta_i = 0;

	void					prepare();

	void					update_delta(const int &i, const int &j, const int &index);
	void 					compute_delta();
	void					optimize_delta();

	bool					generate_hill_helper(const point2<int> &iter, const float &height);
	void					generate_hill(const point3<int> &summit);

	FastNoise				noise_generator;

	float					generate_noise(
							const point2<int> &iter,
							const float &frequency,
							const float &range,
							const point2<float> &offset = point2<float>(0),
							const float &power = 1) const;
	void					apply_noise(
							const point2<int> &iter,
							const float &frequency,
							const float &range,
							const point2<float> &offset = point2<float>(0),
							const float &power = 1);
	void					apply_noise(
							const float &frequency,
							const float &range,
							const point2<float> &offset = point2<float>(0),
							const float &power = 1);

	point2<int>				find_ptr(const point3<int> &object) const;

	friend class			water;
};