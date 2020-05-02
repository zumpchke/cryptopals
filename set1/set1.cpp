#include <cstring>
#include <iostream>
#include <ex.h>

using namespace std;

const char input_str[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

int main(int argc, char *argv[])
{
	/* Ex 1 */
	uint8_t bytes[strlen(input_str)/2] = {0};
	string b64 = convert_to_b64((const char *)input_str, strlen(input_str), (uint8_t *)bytes);
	cout << b64 << endl;

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
