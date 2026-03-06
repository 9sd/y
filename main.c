#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

static void print_hex(const char *label, const unsigned char *data, int len)
{
    printf("%s: ", label);
    for (int i = 0; i < len; i++)
        printf("%02x", data[i]);
    printf("\n");
}

int main(void)
{
    /* 1. Print OpenSSL version */
    printf("OpenSSL version: %s\n\n", OpenSSL_version(OPENSSL_VERSION));

    /* 2. Generate random bytes */
    unsigned char rand_bytes[16];
    if (RAND_bytes(rand_bytes, sizeof(rand_bytes)) != 1) {
        fprintf(stderr, "RAND_bytes failed\n");
        return 1;
    }
    print_hex("Random bytes", rand_bytes, sizeof(rand_bytes));

    /* 3. Compute SHA-256 hash of a string */
    const char *message = "Hello, OpenSSL!";
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        return 1;
    }

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, message, strlen(message));
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);

    printf("\nMessage: \"%s\"\n", message);
    print_hex("SHA-256", hash, hash_len);

    return 0;
}
