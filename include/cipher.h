#include <stdio.h>
#include "cipher_state.h"


struct StreamCipher {
    States* states;
    int current_block;
};

typedef struct StreamCipher StreamCipher;

// Instantiate stream cipher
StreamCipher* StreamCipher_create();

// Initialize the stream cipher.
// A password is needed to kickstart the random stream of integers.
void StreamCipher_init(StreamCipher* this, char* password);

// Deallocate stream cipher.
void StreamCipher_free(StreamCipher* this);

// Encrypt a character from the stream cipher.
// Stream cipher will update its internal state.
char StreamCipher_encrypt(StreamCipher* this, char input);

// Encrypt contents of input file and store the result to the output file.
void StreamCipher_encrypt_file(StreamCipher* cipher, FILE* in_file, FILE* out_file);