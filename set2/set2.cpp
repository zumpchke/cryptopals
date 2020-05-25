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
	}

	return 0;
}
