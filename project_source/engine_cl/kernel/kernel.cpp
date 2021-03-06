#include "kernel.h"

using namespace				mod1_engine_cl;

MOD1_GENERATE_EXCEPTION_DEFINITION(kernel, exception_source)
MOD1_GENERATE_EXCEPTION_DEFINITION(kernel, exception_compilation)
MOD1_GENERATE_EXCEPTION_DEFINITION(kernel, exception_build)

//							PUBLIC

void						kernel::add_source(const std::string &file)
{
	source += read_source(file);
	source += "\n\n";
}

void						kernel::build(const std::string &function, const int &number)
{
	kernel_number = number;

	compile_program();
	set_queue();
	set_kernel(function);

	is_built = true;
}


void 						kernel::run()
{
	if (not is_built)
		throw (exception_build());
	queue.enqueueNDRangeKernel(object, cl::NullRange, cl::NDRange(kernel_number), cl::NullRange);
	queue.finish();
}

argument 					kernel::generate_argument(
							void *ptr,
							const int &size,
							const argument_type &type,
							const bool &link)
{
	argument				argument;

	if (not is_built)
		throw (exception_build());
	argument = mod1_engine_cl::argument(context, &queue, ptr, size, type);
	if (link)
		link_argument(argument);
	return (argument);
}

void 						kernel::link_argument(argument &argument)
{
	if (not is_built)
		throw (exception_build());
	argument.link(object, argument_count++);
}

//							PRIVATE

							kernel::kernel(
							const cl::Device *device,
							const cl::Context *context)
{
	this->device = device;
	this->context = context;
}

std::string 				kernel::read_source(const std::string &filename)
{
	std::ifstream			stream_f;
	std::stringstream		stream_s;

	stream_f.open(filename);
	if (!stream_f.is_open())
		throw (exception_source());
	stream_s << stream_f.rdbuf();
	return (stream_s.str());
}

void 						kernel::compile_program()
{
	std::string				log;

	program = cl::Program(*context, source);
	if(program.build({*device}) != CL_SUCCESS)
	{
		log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(*device);

		printf("Log : %s\n", log.c_str());
		throw (exception_compilation());
	}
}

void 						kernel::set_queue()
{
	queue = cl::CommandQueue(*context, *device);
}

void 						kernel::set_kernel(const std::string &function)
{
	object = cl::Kernel(program, function.c_str());
}