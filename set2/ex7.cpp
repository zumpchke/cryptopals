#include <ex.h>

int valid_pkcs(vector<uint8_t>& plaintext)
{
	// FIXME
	assert(plaintext.size() == 16);

	auto last = plaintext.end() - 1;

	if (*last > 15) {
		return 0;
	}

	auto start = plaintext.end() - *last;
	while (start != plaintext.end()) {
		if (*start != *last) {
			return 0;
		}
		start++;
	}
	return 1;
}
