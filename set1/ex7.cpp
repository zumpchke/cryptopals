#include <ex.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <cassert>

// Reference: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

int run_aes(uint8_t *encrypted_data, size_t sz, uint8_t *plaintext)
{
	const unsigned char *key = (const unsigned char *) "YELLOW SUBMARINE";
	int len;
	int pt_len = 0;

	const EVP_CIPHER *cipher = EVP_aes_128_ecb();
	ERR_load_crypto_strings();
	EVP_CIPHER_CTX *ctx;

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		assert(0);
	}

	EVP_CIPHER_CTX_set_padding(ctx, 0);

	if (EVP_DecryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
		assert(0);
	}

	if (EVP_DecryptUpdate(ctx, plaintext, &len, encrypted_data, sz) != 1) {
		assert(0);
	}
	pt_len = len;

	if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) {
		assert(0);
	}

	pt_len += len;

	EVP_CIPHER_CTX_free(ctx);

	return pt_len;
}
