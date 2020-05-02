#include <iostream>
#include <ex.h>
#include <cassert>

void fixed_xor(string buf1, string buf2) {

	auto n = buf1.size();
	assert(n == buf2.size());

	uint8_t bb1[n/2] = {0};
	uint8_t bb2[n/2] = {0};

	hex_to_bytes(buf1.c_str(), n, bb1);
	hex_to_bytes(buf2.c_str(), n, bb2);

	for(int i =0; i < n/2; i++) {
		bb1[i] ^= bb2[i];
	}

	for(int i = 0; i < n/2; i++) {
		cout << std::hex << int(bb1[i]);
	}
	cout << "\n";
}
