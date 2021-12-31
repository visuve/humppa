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

	std::wstring read_numeric_input(std::wstring_view message)
	{
		std::wstring input;

		do
		{
			std::wcout << message << std::endl;
			std::wcin >> input;
		} while (!is_number<wchar_t>(input));

		std::cout << std::endl;
		return input;
	}

	std::wstring generate_numeric_secret(std::wstring_view guess)
	{
		std::wstring secret;

		do
		{
			const uint16_t number = random_number<uint16_t>();
			secret += std::to_wstring(number);
		} while (secret.length() <= guess.length());

		return secret.erase(guess.length() + 1);
	}
}

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
int wmain()
{
	_setmode(_fileno(stdout), _O_U8TEXT);
#else
int main()
{
	std::setlocale(LC_ALL, "en_US.UTF-8");
#endif
	using namespace rutka;

	std::wcout << L"Intialainen Rutka" << std::endl;
	std::wcout << L"Idea kopioitu: tAAt" << std::endl << std::endl;;

	const std::wstring guess = read_numeric_input(L"Syötä numero:");

	std::wcout << L"Syöttämäsi luku:\t" << guess << std::endl;
	std::wcout << L"Koneen luku:\t\t" << generate_numeric_secret(guess) << std::endl;
	std::wcout << std::endl << L"Hävisit rutkasti." << std::endl;

	return 0;
}
