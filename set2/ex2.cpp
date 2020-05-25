#include <ex.h>
#include <iostream>
#include <cassert>
#include <vector>

#define BLOCK_SIZE	(16)

void xor_block(vector<uint8_t>::iterator data, uint8_t *vec)
{
	if (!vec)
		return;

	for(auto i = 0; i < BLOCK_SIZE; i++) {
		*(data++) ^= vec[i];
	}
}

int aes_cbc_encrypt(vector<uint8_t> plaintext, size_t sz,
	vector<uint8_t>& working_data, const char *key, uint8_t *iv)
{
	// Divide data into chunks and pad the last chunk

	assert(sz >= BLOCK_SIZE);
	unsigned int i = 0;
	// Align
	auto working_size = (plaintext.size() +
		(BLOCK_SIZE - 1)) & ~(BLOCK_SIZE - 1);
	pkcs_pad(plaintext, working_size);

	working_data.resize(working_size);
	assert(working_data.size() >= plaintext.size());
	cout << plaintext.size() << "\n";

	vector<uint8_t>::iterator start, work_start, iv_start;
	for(;i < working_size / BLOCK_SIZE; i++) {
		start = plaintext.begin() + i * BLOCK_SIZE;
		work_start = working_data.begin() + i * BLOCK_SIZE;
		iv_start = working_data.begin() + (i - 1) * BLOCK_SIZE;

		xor_block(start, i == 0 ? iv : &(*iv_start));
		aes_encrypt_block(&(*start),
			(unsigned char *)key, &(*work_start));
	}

	return 0;
}



