#ifndef __ex3__
#define __ex3__
#include "../../set1/include/ex.h"
#include "../../set2/include/ex.h"

#define BLOCK_SIZE	(16)

vector<uint8_t> decode_block(vector<uint8_t>& ciphertext, uint8_t *iv, const char *key,
	int start_index);

#endif
