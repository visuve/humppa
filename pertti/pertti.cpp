#include <iostream>
#include <clocale>

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "fi_FI.UTF-8");
	
	std::string text;

	if (argc == 2)
	{
		text = argv[1];
	}
	else
	{
		std::cout << "Syötä tekstiä: ";
		std::cin >> text;
		std::cout << std::endl;
	}

	const size_t z = text.size();
	
	for (size_t y = 0; y < z; ++y)
	{
		for (size_t x = y; x < y + z; ++x)
		{
			std::cout << text[x % z] << (x - y == z - 1 ? '\n' : ' ');
		}
	}
	
	return 0;
}
