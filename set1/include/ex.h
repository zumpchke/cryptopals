#ifndef __ex1__

#define __ex1__

#include <string>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

/* Exercise 1 */
string convert_to_b64(const char *input_str, size_t sz, uint8_t *bytes);
void hex_to_bytes(const char *input_str, size_t sz, uint8_t *bytes);
int b64_to_bytes(const char *input_str, size_t sz, uint8_t *output_bytes);

/* Exercise 2 */
void fixed_xor(string buf1, string buf2);

/* Exercise 3 */
double score_string(unsigned char *arr, size_t sz);
string decrypt_single_byte_xor(string input);

/* Exercise 4 */
string find_single_byte_xor(string filename);

/* Exercise 5 */
void repeating_xor(uint8_t *data, size_t sz, const char *key, size_t key_sz,
	uint8_t *output_data);


/* Exercise 6 */
template
<typename T>
T inline read_file(string filename)
{
	T res;
	ifstream f(filename);

	if (f.is_open()) {
		while (f.good()) {
			string line;
			getline(f, line);

			if (line.size() == 0) {
				continue;
			}
			if constexpr(std::is_same_v<T, std::string>) {
				res += line;
			} else if constexpr(std::is_same_v<T, vector<std::string>>) {
				res.push_back(line);
			} else {
				assert(0);
			}
		}
		f.close();
	} else {
		assert(0);
	}

	return res;
}

int hamming(string a, string b);
int get_key_size(uint8_t *data, size_t len);
vector<vector<uint8_t>> break_data_into_chunks(uint8_t *data, size_t data_len,
	size_t key_size);
vector<vector<uint8_t>> transpose_chunks(vector<vector<uint8_t>>& chunks,
		size_t key_size);
vector<uint8_t> score_chunks(vector<vector<uint8_t>>& chunks);

/* Exercise 7 */
int run_aes(uint8_t *encrypted_data, size_t sz, uint8_t *plaintext, const unsigned char *key = NULL);
int aes_encrypt_ecb(vector<uint8_t>& plaintext, unsigned char *key, vector<uint8_t>& ciphertext);


/* Exercise 8 */
int detect_aes(vector<string> data);
void aes_encrypt_block(uint8_t *plaintext, unsigned char *key, uint8_t *output);
void aes_decrypt_block(uint8_t *ciphertext, unsigned char *key, uint8_t *output);

#endif
