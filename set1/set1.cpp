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

	/* Ex 5 */
	const char *test1 = "Burning 'em, if you ain't quick and nimble"
	"\nI go crazy when I hear a cymbal";

	uint8_t tmp1[strlen(test1)] = {0};
	uint8_t hex1[strlen(test1)*2] = {0};

	const char *exp1 = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623"
	"d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653"
	"e2b2027630c692b20283165286326302e27282f";

	hex_to_bytes(exp1, strlen(exp1), hex1);

	repeating_xor((uint8_t *)test1, strlen(test1), "ICE", 3, tmp1);
	assert(!memcmp(hex1, tmp1, strlen(test1)));
	cout << "Exercise 5: passed" << "\n";

	/* Ex 6 */
	{
		int c = hamming("this is a test", "wokka wokka!!!");
		assert(c == 37);

		string key_data = read_file<std::string>("set1/data/q6.txt");
		uint8_t key_bytes[key_data.size()] = {0};
		auto data_len = b64_to_bytes(key_data.c_str(), key_data.size(), key_bytes);
		int key_size = get_key_size(key_bytes, data_len);
		assert(key_size == 29);

		auto chunks = break_data_into_chunks(key_bytes, data_len, key_size);
		auto transposed_chunks = transpose_chunks(chunks, (size_t)key_size);

		assert(chunks[0].size() == (unsigned int)key_size);
		vector<uint8_t> key = score_chunks(transposed_chunks);

		uint8_t output[data_len] = {0};
		repeating_xor(key_bytes, data_len, (const char *) key.data(), key_size, output);

		for(int i = 0; i < data_len; i++) {
			printf("%c", output[i]);
		}
		printf("\n");

	}

	/* Ex 7 */
	{
		string data = read_file<std::string>("set1/data/q7.txt");
		uint8_t output[data.size()] = {0};
		int data_len = b64_to_bytes(data.c_str(), data.size(), output);
		uint8_t pt[data_len + 1024] = {0};

		run_aes(output, data_len + 1, pt);
	}

	/* Ex 8 */
	{
		auto data = read_file<vector<std::string>>("set1/data/q8.txt");
		auto line = detect_aes(data);
		assert(line == 132);
		cout << "AES ECB Line " << line << "\n";
	}
}
