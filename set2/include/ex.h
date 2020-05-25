#include "../../set1/include/ex.h"
#include <vector>
#include <cstdint>

using namespace std;
void pkcs_pad(vector<uint8_t>& data, size_t pad_sz);
int aes_cbc_encrypt(vector<uint8_t> plaintext, size_t sz, vector<uint8_t>& ciphertext,
	const char *key, uint8_t *iv);
