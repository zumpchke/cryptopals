#include <iostream>
#include <ex.h>
#include <cassert>

using namespace std;

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

	return 0;
}
