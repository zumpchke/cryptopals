#include <ex.h>

string transform_string(string input)
{
	string output = "comment1=cooking%20MCs;userdata=" + input + ";comment2=%20like%20a%20pound%20of%20bacon";

	return output;
}

vector<uint8_t> generate_bad_input()
{
	vector<uint8_t> empty_block(16, 'A');
	
	// B = 32, C = 38
	string bad_text = "BadminCtrue\5\5\5\5\5";
	vector<uint8_t> output;

	output.insert(output.end(), empty_block.begin(), empty_block.end());
	output.insert(output.end(), bad_text.begin(), bad_text.end());

	return output;
}
