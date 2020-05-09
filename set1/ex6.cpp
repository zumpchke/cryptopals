#include <ex.h>
#include <cassert>

vector<string> read_file(string filename)
{
	vector<string> res;
	ifstream f(filename);

	if (f.is_open()) {
		while (f.good()) {
			string line;
			getline(f, line);
			res.push_back(line);
		}
		f.close();
	} else {
		assert(0);
	}

	return res;
}

int hamming(string a, string b)
{
	int count = 0;
	if (a.size() != b.size()) {
		if (a.size() > b.size()) {
			b.append('\0', a.size() - b.size());
		} else {
			a.append('\0', b.size() - a.size());
		}
	}

	for(unsigned int i =0; i < a.size(); i++) {
		count += __builtin_popcount(a[i] ^ b[i]);
	}

	return count;
}
