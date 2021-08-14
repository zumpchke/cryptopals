#include <iostream>
#include <ex.h>
#include <random>

int main(int argc, char *argv[])
{
	// Ex 1
	{

		auto strings = read_file<vector<std::string>>("set3/data/strings.txt");
		vector<vector<uint8_t>> data;
		for(auto& str: strings) {

			vector<uint8_t> v(str.size());
			auto sz = b64_to_bytes((const char *) str.c_str(), str.size(), v.data());
			v.resize(sz+1);

			data.push_back(v);
		}

		auto key = get_random_bytes(16);
		key[15] = '\0';

		auto rand = std::rand() % 10 + 1;

		vector<uint8_t> ciphertext;
		uint8_t iv[16] = {0};

		aes_cbc_encrypt(data[rand], data[rand].size(), ciphertext,
			(const char *) key.data(), iv);

		int blocks = ciphertext.size() / 16;

		vector<uint8_t> results;

		for(int i = 0; i < blocks; i++) {
			auto start_idx = 0;
			vector<uint8_t> cipher;
			if (i == 0) {
				// Special case
				std::copy(ciphertext.begin(),
					ciphertext.begin() + 16,
					back_inserter(cipher));
				start_idx = 16;
			} else {
				std::copy(ciphertext.begin() + (i - 1) * 16,
					ciphertext.begin() + (i - 1) * 16 + 32,
					back_inserter(cipher));
				start_idx = 32;
			}
			auto r = decode_block(cipher, iv, (const char *) key.data(),
				start_idx);

			results.insert(results.end(), r.begin(), r.end());

		}
		cout << "Decode\n====\n";
		cout << string(results.begin(), results.end()) << "\n";

	}
	return 0;
}
