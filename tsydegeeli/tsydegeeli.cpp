#include <iostream>
#include <clocale>
#include <random>

class coin_toss
{
public:
	coin_toss() :
		_engine(_device()),
		_distribution(
			std::numeric_limits<int64_t>::min(),
			std::numeric_limits<int64_t>::max())
	{
		_value = _distribution(_engine);
	}

	operator bool()
	{
		if (_iter >= 63)
		{
			_value = _distribution(_engine);
			_iter = 0;
		}

		return _value & (1ULL << _iter++);
	}
private:
	std::random_device _device;
	std::mt19937 _engine;
	std::uniform_int_distribution<int64_t> _distribution;

	uint8_t _iter = 0;
	int64_t _value = 0;
};

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

	coin_toss toss;

	for (char& c : text)
	{
		if (std::isalpha(c))
		{
			if (toss)
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

