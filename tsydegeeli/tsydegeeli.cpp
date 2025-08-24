#include <iostream>
#include <clocale>
#include <random>

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

	std::random_device device;
	std::mt19937 engine(device());
	std::bernoulli_distribution distribution(0.5);

	for (char& c : text)
	{
		if (std::isalpha(c))
		{
			if (distribution(engine))
			{
				c = std::toupper(c);
			}
			else
			{
				c = std::tolower(c);
			}
		}
	}

	std::cout << text << std::endl;

	return 0;
}

