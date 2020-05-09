#include <ex.h>

void repeating_xor(uint8_t *data, size_t sz, const char *key, size_t key_sz, uint8_t *output_data)
{
	for (unsigned int i = 0; i < sz; i++) {
		output_data[i] = data[i] ^ key[i % key_sz];
	}
}
