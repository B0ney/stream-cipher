#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"


StreamCipher* StreamCipher_create() {
    StreamCipher* cipher = malloc(sizeof(StreamCipher)); 
    return cipher;
}

void StreamCipher_init(StreamCipher* this, char* password) {
    this->states = States_create(password);
    this->current_block = 0;
}

void StreamCipher_free(StreamCipher* this) {
    States_free(this->states);
    free(this);
}

char StreamCipher_encrypt(StreamCipher* this, char input) {
    // Get pointer to current block
    BLOCK* block = States_get_block(this->states, this->current_block);

    // unrecoverable logic error
    if (block == NULL) {
        printf("block index out of range", stderr);
        abort(-1);
    }

    // Perform encryption, we only need 1 byte from the block.
    // The remaining bytes are used for entropy.
    char output = (char)(*block) ^ input;

    // Perform an xorshift on the current block.
    // This is necessary to avoid reusing the same key.
    xorshift_32(block);

    // Rotate block. The next time the function is called, it uses the next block for encryption.
    this->current_block = (this->current_block + 1) % this->states->total_blocks;

    return output;
}

void StreamCipher_encrypt_file(StreamCipher* cipher, FILE* in_file, FILE* out_file) {
    char chr[1];
    while (fread(chr, 1, 1, in_file) == 1) {
        char encrypted = StreamCipher_encrypt(cipher, chr[0]);
        fputc(encrypted, out_file);
    }
}