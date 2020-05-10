#include <string>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>

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
string read_file(string filename);
int hamming(string a, string b);
int get_key_size(uint8_t *data, size_t len);

