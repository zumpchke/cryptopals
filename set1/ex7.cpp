#include <ex.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <cassert>

// Reference: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

int run_aes(uint8_t *encrypted_data, size_t sz, uint8_t *plaintext, const unsigned char *key)
{
	if (!key) {
		key = (const unsigned char *) "YELLOW SUBMARINE";
	}
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


/* From SSL reference */
#define BLOCK_SIZE	(16)
int aes_encrypt_ecb(vector<uint8_t>& plaintext, unsigned char *key,
	vector<uint8_t>& ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	ciphertext.resize(plaintext.size() + BLOCK_SIZE);
	int len;
	int ciphertext_len = 0;
	assert(plaintext.size() > 0);

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		assert(0);
	}

	const EVP_CIPHER *cipher = EVP_aes_128_ecb();
	ERR_load_crypto_strings();

	if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
		assert(0);
	}

	if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(),
		plaintext.size()) != 1) {
		assert(0);
	}
	ciphertext_len = len;

	if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) {
		assert(0);
	}
	assert(len > 0);

	ciphertext_len += len;
	ciphertext.resize(ciphertext_len);

	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}


void aes_encrypt_block(uint8_t *plaintext, unsigned char *key, uint8_t *output)
{
	EVP_CIPHER_CTX *ctx;

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		assert(0);
	}
	int len;

	const EVP_CIPHER *cipher = EVP_aes_128_ecb();
	ERR_load_crypto_strings();
	EVP_CIPHER_CTX_set_padding(ctx, 0);

	if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
		assert(0);
	}

	if (EVP_EncryptUpdate(ctx, output, &len, plaintext, BLOCK_SIZE) != 1) {
		assert(0);
	}

	EVP_CIPHER_CTX_free(ctx);
}

void aes_decrypt_block(uint8_t *ciphertext, unsigned char *key, uint8_t *output)
{
	EVP_CIPHER_CTX *ctx;

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		assert(0);
	}

	int len;

	const EVP_CIPHER *cipher = EVP_aes_128_ecb();
	ERR_load_crypto_strings();
	EVP_CIPHER_CTX_set_padding(ctx, 0);

	if (EVP_DecryptInit_ex(ctx, cipher, NULL, key, NULL) != 1) {
		assert(0);
	}

	if (EVP_DecryptUpdate(ctx, output, &len, ciphertext, BLOCK_SIZE) != 1) {
		assert(0);
	}

	EVP_CIPHER_CTX_free(ctx);
}
