#include <string>
#include <cstdint>
#include <cstddef>

using namespace std;

string convert_to_b64(const char *input_str, size_t sz, uint8_t *bytes);
void hex_to_bytes(const char *input_str, size_t sz, uint8_t *bytes);

/* Exercise 2 */
void fixed_xor(string buf1, string buf2);

/* Exercise 3 */
double score_string(unsigned char *arr, size_t sz);
string decrypt_single_byte_xor(string input);

/* Exercise 4 */
string find_single_byte_xor(string filename);
