#include <cstring>
#include <iostream>
#include <ex.h>

using namespace std;

const char input_str[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

int main(int argc, char *argv[])
{
	uint8_t bytes[strlen(input_str)/2] = {0};
	string b64 = convert_to_b64((const char *)input_str, strlen(input_str), (uint8_t *)bytes);
	cout << b64 << endl;
}
