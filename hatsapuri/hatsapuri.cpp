#include <cmath>
#include <clocale>
#include <iostream>
#include <string>

const std::string message[] =
{
	{
		"   Tässä on hatšapuri eli georgialainen juustoleipä "
		"ja tota ni hatša tarkoittaa juustoa, puri on leipä."
	},
	{
		"   Hatšapurissa on olennaista se, että aina sen verran, "
		"kun laitetaan taikinaa, niin aina saman verran "
		"laitetaan siihen myös juustoa."
	},
	{
		"   Se on semmonen homma, että huulia ei tarvitse rasvata hetkeen!"
	}
};

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "fi_FI.UTF-8");

	float radius = 20.0f;

	if (argc == 2)
	{
		radius = std::stof(argv[1]);
	}
	else
	{
		std::cout << "Syötä hatšapurin koko: ";
		std::cin >> radius;
		std::cout << '\n' << std::endl;
	}

	float console_ratio = 2;
	float w = console_ratio * radius;
	float h = radius;

	std::cout << message[0] << std::endl;
	std::cout << message[1] << std::endl;

	for (int y = -h; y <= h; ++y)
	{
		for (int x = -w; x <= w; ++x)
		{
			float d = std::hypot(x / w, y / h);

			if (d < 0.9)
			{
				std::cout << '*';
			}
			else if (d < 1.0)
			{
				std::cout << '#';
			}
			else
			{
				std::cout << ' ';
			}
		}

		std::cout << std::endl;
	}
	
	std::cout << '\n' << message[2] << '\n' << std::endl;

	return 0;
}
