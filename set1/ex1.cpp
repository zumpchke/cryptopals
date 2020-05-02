#include <string>
#include <ex.h>
#include <iostream>
#include <cstdio>
#include <cassert>

#define get_bit(buf, i) ((buf)[(i)/8]>>(i)%8&1)

static std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789"
             "??"; // These two question marks will be replaced based on the value of url in base64_encode


void get_bits(uint8_t *buf, uint8_t *out)
{
	/* First 6 bits */
	out[0] = (buf[0] & (0b11111100)) >> 2;
	/* Last 2 bits of first byte | First 4 bits of second byte */
	out[1] = (buf[0] & (0b11)) << 4 | (buf[1] & 0b11110000) >> 4;

	/* Last 4 bits of 2nd byte | First two bits of 3rd byte */
	out[2] = (buf[1] & 0b00001111) << 2 | ((buf[2] & 0b11000000) >> 6);
	out[3] = (buf[2] & 0b00111111);
}

void hex_to_bytes(const char *input_str, size_t sz, uint8_t *bytes) {
	assert(sz % 2 == 0);

	size_t i = 0;
	for(; i < (sz / 2); i++) {
		sscanf(input_str + 2 * i, "%02x", &bytes[i]);
	}
}


string convert_to_b64(const char *input_str, size_t sz, uint8_t *bytes)
{
	/* Input is a hex string! */
	hex_to_bytes(input_str, sz, bytes);
	assert(sz % 3 == 0);
	/* Base64 - 3 bytes are turned into 4 B64 chars */
	string out_str{};
	for(int i = 0; i < sz / 2; i += 3) {
		uint8_t out[4] = {0};
		get_bits(bytes + i, out);
		out_str += base64_chars[out[0]];
		out_str += base64_chars[out[1]];
		out_str += base64_chars[out[2]];
		out_str += base64_chars[out[3]];
	}
	return out_str;

}
