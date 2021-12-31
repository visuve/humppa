#include <iostream>
#include <cmath>

const std::wstring message[] =
{
	{
		L"Tässä on hatšapuri eli georgialainen juustoleipä "
		L"ja tota ni hatša tarkoittaa juustoa, puri on leipä."
	},
	{
		L"Hatšapurissa on olennaista se, että aina sen verran, "
		L"kun laitetaan taikinaa, niin aina saman verran "
		L"laitetaan siihen myös juustoa."
	}
};

#if _WIN32
#include <fcntl.h>
#include <io.h>
int wmain()
{
	_setmode(_fileno(stdout), _O_U8TEXT);
#else
#include <clocale>
int main()
{
	std::setlocale(LC_ALL, "en_US.UTF-8");
#endif
	float radius = 20.0f;
	std::wcout << L"Syötä hatšapurin koko: ";
	std::wcin >> radius;
	std::wcout << L'\n' << std::endl;

	float console_ratio = 2;
	float w = console_ratio * radius;
	float h = radius;

	for (const auto& line : message)
	{
		std::wcout << line << std::endl;
	}

	for (int y = -h; y <= h; ++y)
	{
		for (int x = -w; x <= w; ++x)
		{
			float d = std::hypot(x / w, y / h);

			if (d < 0.9)
			{
				std::wcout << L'*';
			}
			else if (d < 1.0)
			{
				std::wcout << L'#';
			}
			else
			{
				std::wcout << L' ';
			}
		}
		std::wcout << std::endl;
	}

	return 0;
}
