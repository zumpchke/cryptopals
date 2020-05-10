#include <ex.h>
#include <algorithm>
#include <cassert>

string read_file(string filename)
{
	string res;
	ifstream f(filename);

	if (f.is_open()) {
		while (f.good()) {
			string line;
			getline(f, line);
			res += line;
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

int hamming(uint8_t *a, uint8_t *b, size_t sz)
{
	int count = 0;

	for(unsigned int i =0; i < sz; i++) {
		count += __builtin_popcount(a[i] ^ b[i]);
	}

	return count;
}

int get_key_size(uint8_t *data, size_t sz)
{

	vector<pair<int, double>> edit_distances;

	/* Key size */
	for (unsigned int k = 2; k < 40; k++) {
		/* Start byte */
		vector<double> distances;
		auto blocks = 0;
		for(unsigned int i = 0; i + 2*k < sz; i += k) {
			double dist = hamming(&data[i], &data[i+k], k);
			distances.push_back(dist / double(k));
			blocks++;
		}

		double sum = 0;
		for(auto& n : distances) sum += n;
		edit_distances.push_back(make_pair(k, sum / blocks));
	}

	sort(edit_distances.begin(), edit_distances.end(),
		[](pair<int, double>& a, pair<int, double>& b) {
		return a.second < b.second;
	});

	return edit_distances[0].first;
}
