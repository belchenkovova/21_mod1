#pragma once

#include "mod1_buffer.h"

class					mod1_model_data
{

public :

						mod1_model_data() = default;
						~mod1_model_data() = default;

	mod1_buffer<float>	point_buffer;
	mod1_buffer<int>	index_buffer;
	mod1_buffer<float>	normal_buffer;
	mod1_buffer<float>	color_buffer;

	struct				exception_unknown_slot : public std::exception
	{
		const char *	what() const throw() override;
	};

	typedef enum
	{
		slot_point,
		slot_index,
		slot_normal,
		slot_color
	}					slot_type;

	void 				*get_ptr(const int &index, const slot_type &slot);
};


