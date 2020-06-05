#include <iostream>
#include <ex.h>

vector<uint8_t> decode_block(vector<uint8_t>& ciphertext, uint8_t *iv, const char *key,
	int start_index)
{
	// Start decoding from..

	assert(start_index <= (signed)ciphertext.size());
	auto i = start_index - 1;
	vector<tuple<vector<uint8_t>::iterator, int, int, int>> update;
	vector<uint8_t> iv_vec(iv, iv + 16);
	vector<uint8_t> results;

	auto pad_count = 1;

	do {
		// Update
		for(auto& [it, val, old_pad, original] : update) {
			auto diff = (pad_count ^ old_pad);
			*it = original;
			*it ^= val ^ diff;
		}
		for(int j = 0; j < 256; j++) {
			vector<uint8_t> pt;
			
			vector<uint8_t>::iterator touch_byte;
			if (i - 16 < 0) {
				touch_byte = iv_vec.end() + (i - 16);
			} else {
				touch_byte = ciphertext.begin() + (i - 16);
			}

			*touch_byte ^= j;

			auto valid = aes_cbc_decrypt(ciphertext,
				ciphertext.size(), pt, key, iv_vec.data());

			if (j == 0 && valid && results.size() > 0) {
				results.insert(results.begin(), results.front());
				pad_count += 1;
				update.push_back(make_tuple(touch_byte, 0,
					pad_count - 1, *touch_byte));
				break;
			}

			*touch_byte ^= j;

			if (valid && (pad_count ^ j) != pad_count) {
				results.insert(results.begin(), pad_count ^ j);
				pad_count += 1;
				// Save position
				update.push_back(make_tuple(touch_byte, j,
					pad_count - 1, *touch_byte));
				break;
			}
		}

		i--;
	} while (i >= start_index - 16);

	return results;
}














