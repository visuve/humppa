#include <iostream>
#include <string>
#include <random>

constexpr char fillers[] = 
{
	'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	':', ';', '<', '=', '>', '?', '@',
	'[', '\\', ']', '^', '_', '`',
	'{', '|', '}', '~'
};

char random_filler()
{
	thread_local std::random_device device;	
	thread_local std::mt19937 engine(device());
	std::uniform_int_distribution<size_t> distribution(0, sizeof(fillers));
	size_t index = distribution(engine);
	return fillers[index];
}

int main(int argc, char** argv)
{
	const uint16_t max = argc > 1 ? std::stoi(argv[1]) : 50;
	
	for (uint16_t size = 0; size < max; ++size)
	{
		for (uint16_t pad = size; pad < max; ++pad)
		{
			std::cout << ' ';
		}

		for (uint16_t fill = 1; fill < size * 2; ++fill)
		{
			std::cout << random_filler();
		}

		std::cout << std::endl;
	}

	return 0;
}

