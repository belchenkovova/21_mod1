#include "renderer.h"

using namespace			mod1_engine_gl;

void					renderer::glfw_callback(GLFWwindow* window, int key, int code, int action, int mode)
{
	renderer			*renderer;
	static bool			mod_line = false;
	static bool			mod_light = false;

	renderer = (mod1_engine_gl::renderer *)glfwGetWindowUserPointer(window);
	for (const auto &callback : renderer->callback_array)
		if (callback.run(key))
			renderer->render_call();
	if (key == GLFW_KEY_ESCAPE)
	{
		renderer->terminate();
		return ;
	}
	else if (key == GLFW_KEY_A)
		renderer->camera.move(axis::x, sign::negative);
	else if (key == GLFW_KEY_D)
		renderer->camera.move(axis::x, sign::positive);
	else if (key == GLFW_KEY_W)
		renderer->camera.move(axis::z, sign::negative);
	else if (key == GLFW_KEY_S)
		renderer->camera.move(axis::z, sign::positive);
	else if (key == GLFW_KEY_Q)
		renderer->camera.move(axis::y, sign::positive);
	else if (key == GLFW_KEY_E)
		renderer->camera.move(axis::y, sign::negative);
	else if (key == GLFW_KEY_LEFT && !mod_light)
		renderer->camera.rotate(axis::y, sign::positive);
	else if (key == GLFW_KEY_RIGHT && !mod_light)
		renderer->camera.rotate(axis::y, sign::negative);
	else if (key == GLFW_KEY_UP && !mod_light)
		renderer->camera.rotate(axis::x, sign::positive);
	else if (key == GLFW_KEY_DOWN && !mod_light)
		renderer->camera.rotate(axis::x, sign::negative);
//	else if (key == GLFW_KEY_LEFT && mod_light)
//		renderer->camera.rotate(renderer->light_info.direct_direction, axis::y, sign::negative);
//	else if (key == GLFW_KEY_RIGHT && mod_light)
//		renderer->camera.rotate(renderer->light_info.direct_direction, axis::y, sign::positive);
//	else if (key == GLFW_KEY_UP && mod_light)
//		renderer->camera.rotate(renderer->light_info.direct_direction, axis::x, sign::negative);
//	else if (key == GLFW_KEY_DOWN && mod_light)
//		renderer->camera.rotate(renderer->light_info.direct_direction, axis::x, sign::positive);
	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		mod_line = !mod_line;
		if (mod_line)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (key == GLFW_KEY_L && action == GLFW_PRESS)
		mod_light = !mod_light;
	else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
//		renderer->framebuffer.bind();
//		renderer->render_no_swap();
//		framebuffer::unbind();
//
//		renderer->blur_program.start();
//		renderer->framebuffer.texture().bind();
//		texture::activate();
//		renderer->blur_program.texture.upload(0);
//		renderer->blur_square.draw();
//		texture::unbind();
//		program::stop();
//
//		renderer->core.swap_buffers();
//		return ;
	}
	else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
	{
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		Character c = renderer->Characters['j'];
//
//#define X_START				100.f
//#define Y_START				100.f
//
//#define X_EXTEND			c.size.x
//#define Y_EXTEND			c.size.y
//
//		float			array[] = {
//			X_START, Y_START, 0,
//			X_START, Y_START + Y_EXTEND, 0,
//			X_START + X_EXTEND, Y_START, 0,
//			X_START + X_EXTEND, Y_START + Y_EXTEND, 0
//		};
//
//		renderer->text_square.buffer_point.copy(array);
//		renderer->text_square.update(model_slot::point);
//
//		renderer->text_program.start();
//		glBindTexture(GL_TEXTURE_2D, c.textureID);
//		texture::activate();
//		renderer->text_square.draw();
//		glBindTexture(GL_TEXTURE_2D, 0);
//		program::stop();
//
//		renderer->core.swap_buffers();
//		return ;
	}
	else
		return ;
	renderer->render_call();
}