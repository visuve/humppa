#include <algorithm>
#include <cstdint>
#include <iostream>
#include <locale>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <clocale>

namespace niukka
{
	template <typename C>
	bool is_number(std::basic_string_view<C> str)
	{
		if (str.empty())
		{
			return false;
		}

		const auto is_digit = [](C c)
		{
			static std::locale loc;
			return std::isdigit(c, loc);
		};

		return std::all_of(str.cbegin(), str.cend(), is_digit);
	}

	std::string read_numeric_input(std::string_view message)
	{
		std::string input;

		do
		{
			std::cout << message << std::endl;
			std::cin >> input;
		} while (!is_number<char>(input));

		std::cout << std::endl;
		return input;
	}

	std::string increment_guess(std::string guess)
	{
		for (char& c : guess | std::views::reverse)
		{
			if (c == '9')
			{
				c = '0';
				continue;
			}

			++c;
			return guess;
		}

		guess.insert(guess.begin(), '1');
		return guess;
	}
}

int main()
{
	std::setlocale(LC_ALL, "fi_FI.UTF-8");

	std::cout << "Persialainen niukka" << std::endl;
	std::string guess = niukka::read_numeric_input("Syötä numero:");

	std::cout << "Syöttämäsi luku:\t" << guess << std::endl;
	std::cout << "Koneen luku:\t\t" << niukka::increment_guess(guess) << std::endl;
	std::cout << std::endl << "Hävisit niukasti." << std::endl;

	return 0;
}
