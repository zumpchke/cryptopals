#include <iostream>
#include <ex.h>
#include <cassert>

void fixed_xor(string buf1, string buf2) {

	auto n = buf1.size();
	assert(n == buf2.size());

	uint8_t *bb1 = (uint8_t *)alloca(n/2*sizeof(uint8_t));

	uint8_t *bb2 = (uint8_t *)alloca(n/2*sizeof(uint8_t));
	memset(bb2, 0, n/2*sizeof(uint8_t));

	hex_to_bytes(buf1.c_str(), n, (uint8_t *)bb1);
	hex_to_bytes(buf2.c_str(), n, (uint8_t *)bb2);

	for(unsigned int i = 0; i < n/2; i++) {
		bb1[i] ^= bb2[i];
	}

	cout << "\n";
}
