#include <ex.h>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void pkcs_pad(vector<uint8_t>& data, size_t pad_sz)
{
	assert(data.size() < pad_sz);

	auto num_bytes = pad_sz - (data.size() % pad_sz);

	data.resize(data.size() + num_bytes, (uint8_t)num_bytes);
}
