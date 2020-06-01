#include "../../set1/include/ex.h"
#include <vector>
#include <cstdint>
#include <map>

#define DUMP_VEC_HEX(x)	do { for(auto& v: x)cout << int(v) << " "; cout << "\n"; } while (0)

using namespace std;
void pkcs_pad(vector<uint8_t>& data, size_t pad_sz);
// Custom AES CBC
int aes_cbc_encrypt(vector<uint8_t> plaintext, size_t sz, vector<uint8_t>& ciphertext,
	const char *key, uint8_t *iv);
int aes_cbc_decrypt(vector<uint8_t>& ciphertext, size_t sz,
	vector<uint8_t>& plaintext, const char *key, uint8_t *iv);


/* Ex 3 */
vector<uint8_t> get_random_bytes(size_t sz);
/* Encrypt AES or CBC randomly */
int encrypt_ecb_cbc(vector<uint8_t> plaintext, vector<uint8_t>& ciphertext);

int oracle(vector<uint8_t>& ciphertext);

/* Ex 4 */
int determine_block_size();
int decrypt_block(unsigned block_size, vector<uint8_t> key,
	vector<uint8_t>& decoded_bytes, vector<uint8_t>& ciphertext,
	vector<uint8_t>& input_data);

/* Ex 5 */
void split_string(const std::string& str, vector<string>& cont, char delim);
using cookie = map<string, string>;
cookie parse_string(const std::string& str);
cookie profile_for(const string& email);
std::string cookie2str(const cookie& c);
void encrypt_profile(const string& profile, vector<uint8_t>& key,
		vector<uint8_t>& output);
cookie decrypt_profile(vector<uint8_t> ciphertext, vector<uint8_t>& key);

/* Ex 7 */
int valid_pkcs(vector<uint8_t>& plaintext);
