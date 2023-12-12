#define BLOCK unsigned int

// struct containing an array of integers
// used for xorshift states
struct States {
    BLOCK* block_data;
    int total_blocks;
};

typedef struct States States;

// Use the input string to produce blocks of initial states for xorshift generation.
States* States_create(const char* str);

// Return a pointer to a block given an index.
// Returns NULL if out of range
BLOCK* States_get_block(States* this, int index);

// Free the states struct
void States_free(States* this);

// perform an xorshift on the state.
//
// Algorithm obtained from page 4 of G. Marsaglia, "Xorshift RNGs"
void xorshift_32(unsigned int* state);