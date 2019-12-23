#include "mod1_loader.h"

						mod1_loader::~mod1_loader()
{
	const GLuint 		*object;

	object = nullptr;
	for (int i = 0; i < vbo_vector.size() && (object = &vbo_vector.at(i)); i++)
		glDeleteBuffers(1, object);
	for (int i = 0; i < vbo_vector.size() && (object = &vbo_vector.at(i)); i++)
		glDeleteBuffers(1, object);
	for (int i = 0; i < vbo_vector.size() && (object = &vbo_vector.at(i)); i++)
		glDeleteBuffers(1, object);
}

void					mod1_loader::load(const mod1_model_data &data, GLuint &vao)
{
	GLuint 				eab = eab_build();

	vao = vao_build();

	vao_bind(vao);
	eab_bind(eab);
	vao_edit_attribute(vao, 0, 3, GL_FLOAT, data.point_array.data(), (int)sizeof(float) * data.point_array.size());

	eab_buffer(eab, data.index_array.data(), (int)sizeof(int) * data.index_array.size());
	mod1_loader::eab_unbind();

	vao_edit_attribute(vao, 1, 3, GL_FLOAT, data.normal_array.data(), (int)sizeof(float) * data.normal_array.size());

	vao_edit_attribute(vao, 2, 3, GL_FLOAT, data.color_array.data(), (int)sizeof(float) * data.color_array.size());

	mod1_loader::vao_unbind();
}
