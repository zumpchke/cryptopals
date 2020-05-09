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


int get_bits(uint8_t *buf, uint8_t *out, int index)
{
	/* First 6 bits */
	if (index == 0) {
		return (buf[0] & (0b11111100)) >> 2;
	} else if (index == 1) {
		/* Last 2 bits of first byte | First 4 bits of second byte */
		return (buf[0] & (0b11)) << 4 | (buf[1] & 0b11110000) >> 4;
	} else if (index == 2) {
		/* Last 4 bits of 2nd byte | First two bits of 3rd byte */
		return (buf[1] & 0b00001111) << 2 | ((buf[2] & 0b11000000) >> 6);
	} else if (index ==3) {
		return (buf[2] & 0b00111111);
	} else {
		assert(0);
	}
}

void hex_to_bytes(const char *input_str, size_t sz, uint8_t *bytes) {
	assert(sz % 2 == 0);

	size_t i = 0;
	for(; i < (sz / 2); i++) {
		sscanf(input_str + 2 * i, "%02x", (unsigned int *)&bytes[i]);
	}
}


string convert_to_b64(const char *input_str, size_t sz, uint8_t *bytes)
{
	/* Input is a hex string! */
	hex_to_bytes(input_str, sz, bytes);
	/* Base64 - 3 bytes are turned into 4 B64 chars */
	string out_str{};
	assert(sz % 2 == 0);

	auto idx = 0;
	int i = 0;
	int n = sz/2;
	while (i < n) {
		idx = get_bits(bytes, NULL, 0);
		out_str += base64_chars[idx];

		if (i + 1 < n) {
			idx = get_bits(bytes, NULL, 1);
			out_str += base64_chars[idx];

			if (i + 2 < n) {
				idx = get_bits(bytes, NULL, 2);
				out_str += base64_chars[idx];
				idx = get_bits(bytes, NULL, 3);
				out_str += base64_chars[idx];
			} else {
				idx = get_bits(bytes, NULL, 2);
				out_str += base64_chars[idx];
				out_str += '=';
			}
		} else {
			idx = get_bits(bytes, NULL, 1);
			out_str += base64_chars[idx];
			out_str += '=';
			out_str += '=';
		}

		bytes += 3;
		i += 3;
	}

	return out_str;
}


/* From Rosetta Code */
int findIndex(unsigned char val) 
{
	if ('A' <= val && val <= 'Z') {
		return val - 'A';
	}

	if ('a' <= val && val <= 'z') {
		return val - 'a' + 26;
	}

	if ('0' <= val && val <= '9') {
		return val - '0' + 52;
	}

	if ('+' == val) {
		return 62;
	}

	if ('/' == val) {
		return 63;
	}

	assert(0);
}


void b64_to_bytes(const char *input_str, size_t sz, uint8_t *output_bytes)
{
	unsigned int i = 0, j = 0;;
	assert(sz >= 4);
	assert(sz % 4 == 0);
	while (i < sz) {
		auto b1 = input_str[i];
		auto b2 = input_str[i+1];
		auto b3 = input_str[i+2];
		auto b4 = input_str[i+3];
		
		auto i1 = findIndex(b1);
		auto i2 = findIndex(b2);
		uint8_t acc;
		
		acc = i1 << 2;
		acc |= i2 >> 4;

		output_bytes[j++] = acc;
		if (b3 != '=') {
			auto i3 = findIndex(b3);
			
			acc = (i2 & 0xF) << 4;
			acc |= i3 >> 2;

			output_bytes[j++] = acc;

			if (b4 != '=') {
				auto i4 = findIndex(b4);

				acc = (i3 & 0x3) << 6;
				acc |= i4;

				output_bytes[j++] = acc;
			}
		}
		i += 4;

	}
}
