#include <ex.h>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
#include <vector>
#include <map>


// Split data up into block sizes
// Find the line with the most duplicate blocks
int detect_aes(vector<string> data)
{
	data.pop_back();
	/* For each line, get histogram? */
	const auto block_size = 16 * 2;

	map<int, int> line_repeats;
	auto l = 0;

	for(auto& d: data) {
		std::map<std::string, int> counts;

		for(unsigned int i = 0; i < d.size(); i += block_size) {
			auto s = d.substr(i, block_size);
			counts[s] += 1;
		}

		auto freq = std::max_element(counts.begin(), counts.end(), []
			(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
			return a.second < b.second;
		});
		//cout << freq->second << "\n";

		line_repeats[l++] = freq->second;

	}

	return std::max_element(line_repeats.begin(), line_repeats.end(), 
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.second < b.second;
	})->first;
}
