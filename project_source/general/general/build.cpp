#include "general.h"

void					general::build()
{
MOD1_GENERATE_MESSAGE("")

	MOD1_INTERNAL(terrain)->parse_map(first_argument);
	MOD1_INTERNAL(terrain)->parse_noise(second_argument ? second_argument : "");
	MOD1_INTERNAL(terrain)->build();

	MOD1_INTERNAL(water)->build();

#if MOD1_ENABLED(MOD1_GENERAL_USE_TERRAIN)
	add_model(MOD1_INTERNAL(terrain)->model());
MOD1_GENERATE_MESSAGE("Mod1 General : Terrain object is built")
#endif

#if MOD1_ENABLED(MOD1_GENERAL_USE_WATER)
	add_model(MOD1_INTERNAL(water)->model());
MOD1_GENERATE_MESSAGE("Mod1 General : Water object is built")
#endif

//						SCENARIOS PREPARATION

	point2<int>			rain_range = MOD1_INTERNAL(water)->size() - point2<int>(2);
	point2<int>			spring_range = MOD1_INTERNAL(water)->size() - MOD1_GENERAL_WELL_SIZE;

	rain_distribution_x = std::uniform_int_distribution<int>(0, rain_range.x);
	rain_distribution_y = std::uniform_int_distribution<int>(0, rain_range.y);

	well_distribution_x = std::uniform_int_distribution<int>(0, spring_range.x);
	well_distribution_y = std::uniform_int_distribution<int>(0, spring_range.y);

//						CAMERA PREPARATION

	camera.switch_projection();
	camera.set_zoom(1.35f * window_multiplier());
	camera.set_position(glm::vec3(0, 700, 1100));
	camera.set_direction(glm::vec3(-0.55, 0, 0));

//						ROTATION PREPARATION

	rotation = glm::rotate(rotation, glm::radians(45.f), rotation_axis);

	for (int i = 0; i < 15; i++)
		camera.rotate(light.direct_direction, mod1_engine_gl::axis::y, mod1_engine_gl::sign::negative);

//						CALLS ESC MANUALLY

	script_esc();
}