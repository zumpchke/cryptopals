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

	unsigned int working_size = 0;
	if (plaintext.size() % BLOCK_SIZE == 0) {
		pkcs_pad(plaintext, plaintext.size() + BLOCK_SIZE);
	} else {
		working_size = (plaintext.size() +
			(BLOCK_SIZE - 1)) & ~(BLOCK_SIZE - 1);
		pkcs_pad(plaintext, working_size);
	}

	working_data.resize(working_size);
	assert(working_data.size() >= plaintext.size());

	vector<uint8_t>::iterator start, work_start, iv_start;
	for(;i < working_size / BLOCK_SIZE; i++) {
		start = plaintext.begin() + i * BLOCK_SIZE;
		work_start = working_data.begin() + i * BLOCK_SIZE;
		iv_start = working_data.begin() + (i - 1) * BLOCK_SIZE;

		/* ECB mode */
		if (iv != nullptr) {
			xor_block(start, i == 0 ? iv : &(*iv_start));
		}
		aes_encrypt_block(&(*start),
			(unsigned char *)key, &(*work_start));
	}

	return 0;
}

int aes_cbc_decrypt(vector<uint8_t>& ciphertext, size_t sz,
	vector<uint8_t>& plaintext, const char *key, uint8_t *iv)
{
	assert(ciphertext.size() % BLOCK_SIZE == 0);

	plaintext.resize(ciphertext.size());

	vector<uint8_t>::iterator start, output_start, iv_start;
	unsigned int i = 0;

	for(; i < sz / BLOCK_SIZE; i++) {
		start = ciphertext.begin() + i * BLOCK_SIZE;
		output_start = plaintext.begin() + i * BLOCK_SIZE;
		iv_start = ciphertext.begin() + (i - 1) * BLOCK_SIZE;

		aes_decrypt_block(&(*start), (unsigned char *) key,
			&(*output_start));

		xor_block(output_start, i == 0 ? iv : &(*iv_start));
	}
	auto pad = int(plaintext.back());
	assert(pad < BLOCK_SIZE);

	plaintext.resize(ciphertext.size() - pad);

	return 0;
}
