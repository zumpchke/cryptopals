#include <ex.h>

int valid_pkcs(vector<uint8_t>& plaintext)
{
	// FIXME

	auto last = plaintext.end() - 1;

	if (*last > 16 || *last == 0) {
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
