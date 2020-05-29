#include <iostream>
#include <ex.h>

int determine_block_size()
{
	vector<uint8_t> ciphertext;

	vector<uint8_t> plaintext{'A'};

	aes_encrypt_ecb(plaintext, (unsigned char *) "x", ciphertext);

	auto result = ciphertext.size();
	while (true) {
		plaintext.push_back('A');
		aes_encrypt_ecb(plaintext, (unsigned char *) "x", ciphertext);

		if (ciphertext.size() != result) {
			result = ciphertext.size() - result;
			break;
		}
	}

	return result;
}
