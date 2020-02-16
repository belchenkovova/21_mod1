#include "system.h"

using namespace		mod1_gui;

void				system::render(const layout &layout)
{
	for (const button *button : layout.data)
		render(*button);
	mod1_engine_gl::core::swap_buffers();
}

void				system::render(const button &button)
{
	point2<int>		start;

	start.x = button.center().x - button.size().x / 2;
	start.y = button.center().y + button.size().y / 2;
	write(start, button.text(), button.font());
}
