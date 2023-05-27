#include <fstream>
#include <numbers>

struct note
{
	note(double frequency, double seconds) :
		frequency(frequency),
		seconds(seconds)
	{
	}

	double value(double amplitude, double time_point) const
	{
		const double amplitude_radians = std::numbers::pi * (time_point / seconds);
		const double smoothening = std::atan(20.0 * std::sin(amplitude_radians)) / std::atan(20);

		amplitude *= smoothening;

		const double frequency_radians = 2.0 * std::numbers::pi * time_point;
		return amplitude * std::sin(frequency_radians * frequency);
	}

	double frequency;
	double seconds;
};

class wave
{
public:
	struct chunk
	{
		chunk(uint32_t identifier, uint32_t size) :
			identifier(identifier),
			size(size)
		{
		}

		virtual ~chunk() = default;

		const uint32_t identifier;
		uint32_t size = 0;
	};
	
	struct riff_chunk : chunk
	{
		riff_chunk() :
			chunk(0x46464952, 36) // "RIFF"
		{
		}

		static constexpr uint32_t format = 0x45564157; // "WAVE"
	};

	struct fmt_chunk : chunk
	{
		fmt_chunk() :
			chunk(0x20746D66, 16) // "fmt "
		{
		}

		uint16_t format = 0;
		uint16_t channels = 0;
		uint32_t samples_per_second = 0;
		uint32_t bytes_per_second = 0;
		uint16_t bytes_per_sample = 0;
		uint16_t bits_per_sample = 0;
	};

	struct data_chunk : chunk
	{
		data_chunk() :
			chunk(0x61746164, 0) // "data"
		{
		}

		~data_chunk()
		{
			if (bytes)
			{
				delete[] bytes;
			}
		}

		void realloc(size_t new_size)
		{
			auto temp = new char[new_size];
			std::memcpy(temp, bytes, size);
			std::swap(temp, bytes);

			if (temp)
			{
				delete[] temp;
			}
		}

		void put(const fmt_chunk& fmt, double sample)
		{
			static size_t bytes_per_sample_per_channel = fmt.bits_per_sample / 8u;

			for (uint16_t channel = 1u; channel <= fmt.channels; ++channel)
			{
				auto data = static_cast<size_t>(sample);
				std::memcpy(&bytes[size], &data, bytes_per_sample_per_channel);
				size += bytes_per_sample_per_channel;
			}
		}

		char* bytes = nullptr;
	};

	wave() = delete;
	wave(const wave&) = delete;
	wave(wave&&) = delete;

	wave(const fmt_chunk& fmt) :
		_fmt(fmt)
	{
		_fmt.bytes_per_sample = (_fmt.bits_per_sample / 8u) * _fmt.channels;
		_fmt.bytes_per_second = _fmt.samples_per_second * _fmt.bytes_per_sample;
	}

	~wave()
	{
	}

	wave& operator << (const note& n)
	{
		const size_t samples_required = _fmt.samples_per_second * n.seconds;
		const size_t bytes_required = _fmt.bytes_per_sample * samples_required * _fmt.channels;
		const size_t new_size = _data.size + bytes_required;
		
		_data.realloc(new_size);

		const size_t damping = 4u; // Must divide at least by two 
		const double amplitude = std::pow(2u, _fmt.bits_per_sample) / damping;

		for (size_t i = 1; i <= samples_required; ++i)
		{
			const double time_point = double(i) / _fmt.samples_per_second;
			const double sample = n.value(amplitude, time_point);
			
			_data.put(_fmt, sample);
		}

		_riff.size += bytes_required;

		return *this;
	}

	friend std::ostream& operator << (std::ostream&, const wave&);

private:
	riff_chunk _riff;
	fmt_chunk _fmt;
	data_chunk _data;
	size_t _bytes_per_channel = 0;
};

template<typename T, class = typename std::enable_if<std::is_unsigned<T>::value>::type>
void write(std::ostream& out, T t)
{
	char* data = reinterpret_cast<char*>(&t);
	out.write(data, sizeof(T));
}

std::ostream& operator << (std::ostream& out, const wave::data_chunk& data)
{
	write(out, data.identifier);
	write(out, data.size);
	out.write(data.bytes, data.size);
	return out;
}

std::ostream& operator << (std::ostream& out, const wave::riff_chunk& riff)
{
	write(out, riff.identifier);
	write(out, riff.size);
	write(out, riff.format);
	return out;
}

std::ostream& operator << (std::ostream& out, const wave::fmt_chunk& fmt)
{
	write(out, fmt.identifier);
	write(out, fmt.size);
	write(out, fmt.format);
	write(out, fmt.channels);
	write(out, fmt.samples_per_second);
	write(out, fmt.bytes_per_second);
	write(out, fmt.bytes_per_sample);
	write(out, fmt.bits_per_sample);
	return out;
}

std::ostream& operator << (std::ostream& out, const wave& wav)
{
	out << wav._riff;
	out << wav._fmt;
	out << wav._data;
	return out;
}

int main()
{
	srand(123);

	wave::fmt_chunk fmt;
	fmt.format = 1; // PCM
	fmt.channels = 2;
	fmt.samples_per_second = 44100;
	fmt.bits_per_sample = 16;

	wave wav(fmt);

	const double seconds = 0.18;
	note c(261, seconds);
	note cis(278, seconds);
	note d(294, seconds);
	note dis(311, seconds);
	note e(330, seconds);
	note f(349, seconds);
	note fis(370, seconds);
	note g(392, seconds);
	note gis(415, seconds);
	note a(440, seconds);
	note ais(466, seconds);
	note h(494, seconds);
	note a2(220, 0.5);
	note h2(247, seconds);
	note p(0, seconds);

	wav << e << p;
	wav << dis << p;
	wav << e << p;
	wav << dis << p;
	wav << e << p;
	wav << h2 << p;
	wav << d << p;
	wav << c << p;
	wav << a2 << p;

	std::ofstream file("jytke.wav", std::ios_base::binary);
	file << wav;
	file.close();

	// For debugging
	//system("jytke.wav");

	return 0;
}