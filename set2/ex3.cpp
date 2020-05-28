#include <random>
#include <algorithm>
#include <ex.h>
#include <experimental/random>
#include <set>

#define BLOCK_SIZE	(16)

vector<uint8_t> get_random_bytes(size_t sz)
{
	vector<uint8_t> data;
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<uint8_t> dist(0, UINT8_MAX);

	std::generate_n(std::back_inserter(data), sz, [&dist, &random_engine]() {
		return dist(random_engine);
	});

	return data;
}

int oracle(vector<uint8_t>& ciphertext)
{
	set<vector<uint8_t>> blocks;
	assert(ciphertext.size() % 16 == 0);

	for(unsigned int i = 0; i < ciphertext.size() / 16; i++) {
		auto start = ciphertext.begin() + i * 16;
		auto end = ciphertext.begin() + (i + 1) * 16;
		vector<uint8_t> tmp(start, end);
		if (blocks.find(tmp) != blocks.end()) {
			return 0;
		} else {
			blocks.insert(tmp);
		}
	}
	return 1;
}

/* Encrypt AES or CBC half the time */
int encrypt_ecb_cbc(vector<uint8_t> plaintext, vector<uint8_t>& ciphertext)
{
	vector<uint8_t> random_key = get_random_bytes(BLOCK_SIZE);

	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> dist(5, 10);

	auto pre = dist(random_engine);
	auto post = dist(random_engine);
	auto pre_data = get_random_bytes(pre);
	auto post_data = get_random_bytes(post);

	plaintext.insert(plaintext.begin(), pre_data.begin(), pre_data.end());
	plaintext.insert(plaintext.end(), post_data.begin(), post_data.end());

	auto rand = std::experimental::randint(0, 1);
	if (rand == 0) {
		/* ECB */
		aes_cbc_encrypt(plaintext, plaintext.size(), ciphertext,
			(const char *) random_key.data(), NULL);
	} else {
		/* CBC */
		uint8_t iv[16] = {0};
		aes_cbc_encrypt(plaintext, plaintext.size(), ciphertext,
			(const char *) random_key.data(), iv);
	}
	return rand;
}
