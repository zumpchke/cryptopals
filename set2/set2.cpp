#include <iostream>
#include <ex.h>
#include <cassert>
#include <cstring>
#include <map>

using namespace std;

const char *ex4_str =
"Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkg"
"aGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBq"
"dXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUg"
"YnkK";

int main(int argc, char *argv[])
{
	/* Ex 1 */
	{
		std::string s("YELLOW SUBMARINE");
		vector<uint8_t> data(s.begin(), s.end());
		pkcs_pad(data, 20);
		assert(data.size() == 20);

		for(auto& c: data) {
			cout << hex << int(c) << " " << dec;
		}
		cout << "\n";
	}

	/* Ex 2 */
	{
		// TODO test vectors
		uint8_t iv[16] = {0};
		std::string s("YELLOW SUBMARINEYELLOW SUBMARINEBLARGO");
		vector<uint8_t> data(s.begin(), s.end());

		vector<uint8_t> out;

		aes_cbc_encrypt(data, s.size(), out,
			(const char *)"YELLOW SUBMARINE", iv);
		cout << out.size() << "\n";

		for (auto& c : out) {
			printf("%x ", int(c));
		}
		printf("\n");

		vector<uint8_t> orig_data;

		aes_cbc_decrypt(out, out.size(), orig_data,
			(const char *) "YELLOW SUBMARINE", iv);
		std::string newstr(orig_data.begin(), orig_data.end());
		assert(newstr == s);

		// Decrypt intelligible data.

		std::string file_data = read_file<std::string>("set1/data/q10.txt");
		vector<uint8_t> bytes(file_data.size());

		auto data_len = b64_to_bytes(file_data.c_str(),
			file_data.size(), bytes.data());

		vector<uint8_t> decode;
		// XXX why data_len + 1?
		aes_cbc_decrypt(bytes, data_len + 1, decode,
			(const char *) "YELLOW SUBMARINE", iv);

		std::string decodestr(decode.begin(), decode.end());
		cout << decodestr << "\n";

	}

	/* Ex 3 */
	{
		for (auto i = 0; i < 100; i++) {
			vector<uint8_t> v(43, 0xA);
			vector<uint8_t> ciphertext;
			auto mode = encrypt_ecb_cbc(v, ciphertext);
			auto res = oracle(ciphertext);
			assert(mode == res);
		}
	}

	/*  Ex 4 */
	{
		std::vector<uint8_t> input_data(strlen(ex4_str));
		assert(input_data.size() == strlen(ex4_str));

		auto key = get_random_bytes(16);
		key[15] = '\0';
		vector<uint8_t> ciphertext;

		auto sz = b64_to_bytes((const char *) ex4_str, strlen(ex4_str),
			input_data.data());
		input_data.resize(sz + 1); // FIXME

		auto bs = determine_block_size();
		assert(bs == 16);

		vector<uint8_t> decoded_bytes;

		// Decrypt single block
		for(int i = 0; i < bs; i++) {
			map<vector<uint8_t>, uint8_t> dict;
			// Create dictionary
			for(int j = 0; j < 256; j++) {
				vector<uint8_t> pfx(bs - 1 - i, 'A');
				vector<uint8_t> cipher;
				pfx.insert(pfx.end(), decoded_bytes.begin(),
					decoded_bytes.end());
				pfx.push_back((uint8_t)j);
				assert(pfx.size() == (unsigned)bs);
				aes_encrypt_ecb(pfx, key.data(), cipher);
				cipher.resize(bs);
				dict[cipher] = (uint8_t) j;
			}

			vector<uint8_t> prefix(bs - 1 - i, 'A');
			prefix.insert(prefix.end(), decoded_bytes.begin(),
				decoded_bytes.end());
			assert(prefix.size() == (unsigned) bs - 1);

			string t(prefix.begin(), prefix.end());

			prefix.insert(prefix.end(), input_data.begin() + i,
				input_data.end());

			aes_encrypt_ecb(prefix, key.data(), ciphertext);
			vector<uint8_t> tmp(ciphertext.begin(),
				ciphertext.begin() + 16);
			if (dict.find(tmp) != dict.end()) {
				decoded_bytes.push_back(dict[tmp]);
				cout << (char) dict[tmp] << "\n";
			} else {
				assert(0);
			}
		}
	}

	return 0;
}
