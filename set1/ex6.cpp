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

vector<vector<uint8_t>> break_data_into_chunks(uint8_t *data, size_t data_len,
	size_t key_size)
{
	vector<vector<uint8_t>> res;

	for(unsigned int i = 0; i < data_len / key_size; i++) {
		vector<uint8_t> chunk;
		for(unsigned int j = 0; j < key_size; j++) {
			chunk.push_back(data[i*key_size + j]);
		}
		res.push_back(chunk);
	}
	return res;
}

vector<vector<uint8_t>> transpose_chunks(vector<vector<uint8_t>>& chunks,
	size_t key_size)
{
	vector<vector<uint8_t>> transposed;

	for(unsigned int i = 0; i < key_size; i++) {
		vector<uint8_t> t;
		for(auto& c: chunks) {
			t.push_back(c[i]);
		}
		transposed.push_back(t);
	}
	return transposed;
}

static constexpr double lowest_double = std::numeric_limits<double>::lowest();
vector<uint8_t> score_chunks(vector<vector<uint8_t>>& chunks)
{

	vector<uint8_t> key(chunks[0].size(), 0);
	// For every chunk, a single byte is the correct key!
	for(auto it = chunks.begin(); it != chunks.end(); it++) {
		auto c = *it;
		auto score = lowest_double;
		uint8_t *data = c.data();
		// For every char
		for(unsigned char chr = 0; chr < UINT8_MAX; chr++) {

			// Xor it.
			for(unsigned int i = 0; i < c.size(); i++) {
				data[i] ^= chr;
			}

			// Score it.
			auto s = score_string(data, c.size());
			if (s > score) {
				score = s;
				key[std::distance(chunks.begin(), it)] = chr;
			}

			/* Reset */
			for(unsigned int i = 0; i < c.size(); i++) {
				data[i] ^= chr;
			}
		}
	}

	return key;
}
