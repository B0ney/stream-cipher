#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cipher_state.h"

States* States_create(const char* str) {
    States* states = malloc(sizeof(States));

    // Blocks are 4 bytes long. 
    // Calculate how many blocks should be created to fully contain the str
    int total_blocks = (int)ceil((float)strlen(str) / (float)sizeof(BLOCK));

    // use calloc to initialize memory to zeros.
    // necessary to avoid reading and modififying uninitialized data.
    states->block_data = calloc(total_blocks, sizeof(BLOCK));
    states->total_blocks = total_blocks;

    // copy string data to blocks
    memcpy(states->block_data, str, strlen(str));

    return states;
}

BLOCK* States_get_block(States* this, int index) {
    if (index >= this->total_blocks) {
        return NULL;
    }

    return &this->block_data[index];
}

void States_free(States* this) {
    free(this->block_data);
    free(this);
}

void xorshift_32(BLOCK* state) {
    unsigned int x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
}