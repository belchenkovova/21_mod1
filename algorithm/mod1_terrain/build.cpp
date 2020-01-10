#include "mod1_terrain.h"

void					mod1_terrain::build()
{
	prepare();

	set((mod1_point2<float>)min_i, (mod1_point2<float>)max_i, (float)delta_i);
	mod1_plane::build();

	//					Hills

	noise_generator.SetNoiseType(FastNoise::Perlin);

#if MOD1_ENABLED(MOD1_TERRAIN_HILLS)
	for (auto const &iter_source : data_raw)
		generate_hill(iter_source);
#endif

#if MOD1_ENABLED(MOD1_TERRAIN_NOISE_A)
	apply_noise(
		MOD1_TERRAIN_NOISE_A_FREQUENCY,
		MOD1_TERRAIN_NOISE_A_RANGE,
		MOD1_TERRAIN_NOISE_A_OFFSET,
		2.5);
#endif

#if MOD1_ENABLED(MOD1_TERRAIN_NOISE_B)
	apply_noise(
		MOD1_TERRAIN_NOISE_B_FREQUENCY,
		MOD1_TERRAIN_NOISE_B_RANGE,
		MOD1_TERRAIN_NOISE_B_OFFSET);
#endif

	update_normal();
	update_final();

	//					Colors

	mod1_point2<int>	iter;
	mod1_point3<float>	color;

	for (iter.y = 0; iter.y < size().y - 1; iter.y++)
		for (iter.x = 0; iter.x < size().x; iter.x++)
		{
			color = compute_color(read_height(iter));
			write_color(iter, color);
		}
}