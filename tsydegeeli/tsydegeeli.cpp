#include <iostream>
#include <clocale>
#include <random>

template <typename T>
class coin_toss
{
public:
	coin_toss() :
		_engine(_device()),
		_distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max())
	{
		_value = _distribution(_engine);
	}

	operator bool()
	{
		constexpr size_t last_bit_index = 
			std::numeric_limits<T>::digits - std::is_unsigned<T>::value;

		if (_index >= last_bit_index)
		{
			_value = _distribution(_engine);
			_index = 0;
		}

		return _value & (T(1) << _index++);
	}
private:
	std::random_device _device;
	std::mt19937 _engine;
	std::uniform_int_distribution<T> _distribution;

	uint8_t _index = 0;
	T _value = 0;
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

	coin_toss<int64_t> toss;

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

