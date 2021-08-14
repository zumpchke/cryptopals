#include <iostream>
#include <unordered_map>
#include <ex.h>
#include <limits>

using namespace std;

static unordered_map<char, double> freqs{
	{'a', 0.08167},
	{'b', 0.01492},
	{'c', 0.02782},
	{'d', 0.04253},
	{'e', 0.12702},
	{'f', 0.02228},
	{'g', 0.02015},
	{'h', 0.06094},
	{'i', 0.06094},
	{'j', 0.00153},
	{'k', 0.0072},
	{'l', 0.04025},
	{'m', 0.02406},
	{'n', 0.06749},
	{'o', 0.07507},
	{'p', 0.01929},
	{'q', 0.00095},
	{'r', 0.05987},
	{'s', 0.06327},
	{'t', 0.09056},
	{'u', 0.02758},
	{'v', 0.00978},
	{'w', 0.02360},
	{'x', 0.00150},
	{'y', 0.01974},
	{'z', 0.00074},
	{' ', 0.13000}
};
static constexpr double lowest_double = std::numeric_limits<double>::lowest();

double score_string(unsigned char *arr, size_t sz)
{
	auto sum = 0.0;
	for(unsigned int i = 0; i < sz; i++) {
		if (freqs.find(arr[i]) != freqs.end()) {
			sum += freqs[std::tolower(arr[i])];
		}
	}
	return sum;
}

string decrypt_single_byte_xor(string input)
{
	auto n = input.size();
	uint8_t *bytes = (uint8_t *)alloca(n/2*sizeof(uint8_t));
	unsigned char final_chr = 0;

	hex_to_bytes(input.c_str(), n, bytes);
	unordered_map<unsigned char, string> result;

	auto score = lowest_double;

	/* For every character */
	for (unsigned char chr = 0; chr < UINT8_MAX; chr++) {
		for (unsigned int i = 0; i < n/2; i++) {
			bytes[i] ^= chr;
		}
		auto s = score_string(bytes, n/2);
		if (s > score) {
			score = s;
			result.insert({chr, string((unsigned char *)bytes, (unsigned char *) bytes + n/2)});
			final_chr = chr;
		}
		/* Reset */
		for (unsigned int i = 0; i < n/2; i++) {
			bytes[i] ^= chr;
		}
	}
	return result[final_chr];
}
