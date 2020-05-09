#include <cstring>
#include <iostream>
#include <cassert>
#include <ex.h>

using namespace std;

const char *input_str = "66" "6f" "6f" "62" "61" "72";

const char *test_strs[] = {"Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy"};

int main(int argc, char *argv[])
{
	/* Ex 1 */
	assert(strlen(input_str) % 2 == 0);
	uint8_t bytes[(strlen(input_str)/2) + 1] = {0};
	for(unsigned int j = 2; j <= strlen(input_str); j += 2) {
		string b64 = convert_to_b64((const char *)input_str, j, (uint8_t *)bytes);
		assert(b64 == test_strs[j / 2 - 1]);
	}

	uint8_t output_bytes[20] = {0};
	b64_to_bytes((const char *)test_strs[5], strlen(test_strs[5]), output_bytes);
	assert(!strcmp((const char *)output_bytes, "foobar"));

	/* Ex 2 */
	fixed_xor("1c0111001f010100061a024b53535009181c",
		"686974207468652062756c6c277320657965");

	/* Ex 3 */
	auto res = decrypt_single_byte_xor("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	cout << "Exercise 3 result: " << res << "\n";

	/* Ex 4 */
	res = find_single_byte_xor("set1/data/q4.txt");
	cout << "Exercise 4 result: " << res << "\n";

}
