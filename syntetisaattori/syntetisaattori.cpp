#include <fstream>
#include <numbers>

class note_base
{
public:
	constexpr note_base(double seconds, double frequency) :
		seconds(seconds),
		frequency(frequency)
	{
	}

	const double seconds;
	const double frequency;

	virtual int64_t value(const double amplitude, const double time_point) const = 0;

	static constexpr double quarter_turn = std::numbers::pi / 2.0;
	static constexpr double half_turn = std::numbers::pi;
	static constexpr double full_turn = std::numbers::pi * 2.0;
};

class note : public note_base
{
public:
	constexpr note(double seconds, double frequency) :
		note_base(seconds, frequency),
		amplitude_step(half_turn / seconds),
		frequency_step(full_turn * frequency)
	{
	}

	int64_t value(const double amplitude, const double time_point) const override
	{
		const double amplitude_radians = amplitude_step * time_point;
		const double smoothening = std::atan(20.0 * std::sin(amplitude_radians)) / std::atan(20);
		const double frequency_radians = frequency_step * time_point;
		return amplitude * smoothening * std::sin(frequency_radians);
	}

	const double amplitude_step;
	const double frequency_step;
};

class note_range : public note_base
{
public:
	note_range(double seconds, double frequency_from, double frequency_to) :
		note_base(seconds, frequency_from),
		frequency_step(full_turn * frequency),
		frequency_adjustment(half_turn * (frequency_to - frequency_from) / seconds)
	{
	}

	int64_t value(const double amplitude, const double time_point) const override
	{
		const double adjustment = frequency_adjustment * time_point;
		const double frequency_radians = (frequency_step + adjustment) * time_point;
		const double result = amplitude * std::sin(frequency_radians);
		return result;
	}

	const double frequency_step;
	const double frequency_adjustment;
};

class wave
{
public:
	struct chunk
	{
		constexpr chunk(uint32_t identifier, uint32_t size) :
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
		constexpr riff_chunk() :
			chunk(0x46464952, 36) // "RIFF"
		{
		}

		static constexpr uint32_t format = 0x45564157; // "WAVE"
	};

	struct fmt_chunk : chunk
	{
		constexpr fmt_chunk() :
			chunk(0x20746D66, 16) // "fmt "
		{
		}

		uint16_t format = 0;
		uint16_t channels = 0;
		uint32_t samples_per_second = 0;
		uint32_t bytes_per_second = 0;
		uint16_t bytes_per_frame = 0;
		uint16_t bits_per_sample = 0;
	};

	struct data_chunk : chunk
	{
		constexpr data_chunk() :
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

		void put(const fmt_chunk& fmt, int64_t sample)
		{
			char* data = reinterpret_cast<char*>(&sample);

			if (fmt.bits_per_sample == 8) // 8-bit is unsigned (usually)
			{
				data[0] += 0x80;
			}

			const size_t bytes_per_channel = fmt.bytes_per_frame / fmt.channels;

			for (uint16_t channel = 1u; channel <= fmt.channels; ++channel)
			{
				for (size_t i = 0; i < bytes_per_channel; ++i)
				{
					bytes[size] = data[i];
					++size;
				}
			}
		}

		char* bytes = nullptr;
	};

	wave() = delete;
	wave(const wave&) = delete;
	wave(wave&&) = delete;

	constexpr wave(const fmt_chunk& fmt) :
		_fmt(fmt)
	{
		_fmt.bytes_per_second = _fmt.samples_per_second * _fmt.bytes_per_frame * _fmt.channels;
		_fmt.bytes_per_frame = (_fmt.bits_per_sample / 8u) * _fmt.channels;
	}

	~wave()
	{
	}

	wave& operator << (const note_base& n)
	{
		const size_t samples_required = _fmt.samples_per_second * n.seconds;
		const size_t bytes_required = _fmt.bytes_per_frame * samples_required;
		const size_t new_size = _data.size + bytes_required;
		
		_data.realloc(new_size);

		const double damping = 4.0; // Must divide at least by two 
		const double amplitude = std::pow(2u, _fmt.bits_per_sample) / damping;

		for (size_t i = 1u; i <= samples_required; ++i)
		{
			const double time_point = double(i) / _fmt.samples_per_second;
			const int64_t sample = n.value(amplitude, time_point);
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
	write(out, fmt.bytes_per_frame);
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

void for_elise(wave& wav)
{
	constexpr double seconds = 0.18;
	constexpr note c(seconds, 261);
	constexpr note cis(seconds, 278);
	constexpr note d(seconds, 294);
	constexpr note dis(seconds, 311);
	constexpr note e(seconds, 330);
	constexpr note f(seconds, 349);
	constexpr note fis(seconds, 370);
	constexpr note g(seconds, 392);
	constexpr note gis(seconds, 415);
	constexpr note a(seconds, 440);
	constexpr note ais(seconds, 466);
	constexpr note h(seconds, 494);
	constexpr note a2(0.5, 220);
	constexpr note h2(seconds, 247);
	constexpr note p(0.13, 0);

	wav << p << e << p;
	wav << dis << p;
	wav << e << p;
	wav << dis << p;
	wav << e << p;
	wav << h2 << p;
	wav << d << p;
	wav << c << p;
	wav << a2 << p;
}

void bass_test(wave& wav)
{
	wav << note_range(30.0, 0.1, 100);
	wav << note_range(30.0, 100, 0.1);
}

void tylsa(wave& wav)
{
	wav << note(120.0, 261.6);
}

int main(int argc, char** argv)
{
	wave::fmt_chunk fmt;
	fmt.format = 1; // PCM
	fmt.channels = 2;
	fmt.samples_per_second = 44100;
	fmt.bits_per_sample = 16;

	wave wav(fmt);


	std::string filename;

	if (argc <= 1)
	{
		return -1;
	}
	else if (strcmp(argv[1], "beethoven") == 0)
	{
		for_elise(wav);
		filename = "for_elise.wav";
	}
	else if (strcmp(argv[1], "bassoa") == 0)
	{
		bass_test(wav);
		filename = "bassotesti.wav";
	}
	else if (strcmp(argv[1], "refe") == 0)
	{
		tylsa(wav);
		filename = "refe.wav";
	}

	std::ofstream file(filename, std::ios_base::binary);
	file << wav;
	file.close();

	// Hope you have a default association
	system(filename.c_str());

	return 0;
}