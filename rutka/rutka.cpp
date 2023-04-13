#include <algorithm>
#include <cstdint>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <string_view>

namespace rutka
{
	template <typename T>
	T random_number()
	{
		thread_local std::random_device device;
		thread_local std::mt19937 engine(device());
		thread_local std::uniform_int_distribution<T> distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		return distribution(engine);
	}

	template <typename C>
	bool is_number(std::basic_string_view<C> str)
	{
		if (str.empty())
		{
			return false;
		}

		auto is_digit = [](C c)
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

	std::string generate_numeric_secret(std::string_view guess)
	{
		std::string secret;

		do
		{
			const uint16_t number = random_number<uint16_t>();
			secret += std::to_string(number);
		} while (secret.length() <= guess.length());

		return secret.erase(guess.length() + 1);
	}
}

int main()
{
	using namespace rutka;

	std::setlocale(LC_ALL, "fi_FI.UTF-8");

	std::cout << "Intialainen Rutka" << std::endl;
	std::cout << "Idea kopioitu: tAAt" << std::endl << std::endl;;

	const std::string guess = read_numeric_input("Syötä numero:");

	std::cout << "Syöttämäsi luku:\t" << guess << std::endl;
	std::cout << "Koneen luku:\t\t" << generate_numeric_secret(guess) << std::endl;
	std::cout << std::endl << "Hävisit rutkasti." << std::endl;

	return 0;
}
