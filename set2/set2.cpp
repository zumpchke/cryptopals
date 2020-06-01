#include <iostream>
#include <ex.h>
#include <cassert>
#include <cstring>

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

		vector<uint8_t> decode;
		vector<uint8_t> decoded_bytes;

		while (decrypt_block(bs, key, decoded_bytes, ciphertext,
			input_data)) {
			if (input_data.begin() + bs >= input_data.end()) {
				input_data.erase(input_data.begin(),
					input_data.end());
			} else {
				input_data.erase(input_data.begin(),
					input_data.begin() + bs);
			}
			ciphertext.clear();
			std::copy(decoded_bytes.begin(), decoded_bytes.end(),
				back_inserter(decode));
			decoded_bytes.clear();
		}

		cout << string(decode.begin(), decode.end()) << "\n";
	}

	// Ex 5
	{
		vector<uint8_t> ciphertext;
		auto key = get_random_bytes(16);
		key[15] = '\0';

		// Get ciphertext for block containing admin + padding.
		// This is going to replace the last block.
		string prefix{"xxxxxxxxxx"}; // FIXME ehh
		string tmp{"admin"};
		vector<uint8_t> admin(tmp.begin(), tmp.end());
		pkcs_pad(admin, 16);

		prefix.insert(prefix.end(), admin.begin(), admin.end());

		auto profile = profile_for(prefix);
		encrypt_profile(cookie2str(profile), key, ciphertext);

		auto hacked_profile_str =
			cookie2str(profile_for("fooxx@bar.com"));
		vector<uint8_t> cipher_tmp;
		encrypt_profile(hacked_profile_str, key, cipher_tmp);

		// Replace last block of first encryption with second block
		// of second

		assert(cipher_tmp.size() == 48);
		copy(ciphertext.begin() + 16,
			ciphertext.begin() + 32, cipher_tmp.begin() + 32);

		auto c = decrypt_profile(cipher_tmp, key);
		assert(c.at("role") == "admin");
	}

	// Ex 6 : TODO
	//


	// Ex 7
	{
		{
			string t{"ICE ICE BABY\04\04\04\04"};
			vector<uint8_t> v(t.begin(), t.end());
			assert(valid_pkcs(v));
		}

		{
			string t{"ICE ICE BABY\05\05\05\05"};
			vector<uint8_t> v(t.begin(), t.end());
			assert(!valid_pkcs(v));
		}

		{
			string t{"ICE ICE BABY\01\02\03\04"};
			vector<uint8_t> v(t.begin(), t.end());
			assert(!valid_pkcs(v));
		}
	}

	return 0;
}
