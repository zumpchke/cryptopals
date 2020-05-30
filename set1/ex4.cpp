#include <iostream>
#include <vector>
#include <fstream>
#include <ex.h>
#include <limits>
#include <map>

constexpr double lowest_double = std::numeric_limits<double>::lowest();

string find_single_byte_xor(string filename)
{
	string str;
	vector<string> data;
	ifstream file(filename);
	auto best_score = lowest_double;
	string result;

	while (getline(file, str)) {
		auto candidate = decrypt_single_byte_xor(str);
		auto s = score_string((unsigned char *)candidate.c_str(), candidate.size());
		if (s > best_score) {
			best_score = s;
			result = candidate;
		}
	}

	return result;
}

