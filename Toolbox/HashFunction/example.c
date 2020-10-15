#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "MurmurHash3.h"

// Variable with the size of buckets of the hash table
const int N = 64;
// Variable with some arbitrary seed.
const int HASH_SEED = 1;

unsigned int hash(const char *word);

int main()
{
    int arbitrary_iterations = 10;
    for (int i = 0; i < arbitrary_iterations; i++)
    {
        printf("Type a word to hash it: ");
        char buffer[40];
        assert (fgets(buffer, sizeof(buffer), stdin) != NULL);
        
        // excluding the \0 of fgets.
        int tamanho = strlen(buffer);
        for (int j = 0; j < tamanho; j++)
        {
            if (buffer[j] == '\n')
            {
                buffer[j] = '\0';
                break;
            }
        }
        
        printf("The hash of %s is: %u\n", buffer, hash(buffer));
    }

    return 0;
}

unsigned int hash(const char *word)
{
    unsigned int hash_number = 0;
    uint32_t hash_output[4];    // Output for the hash
    unsigned short int word_length = strlen(word) + 1; // including \0
    
    MurmurHash3_x86_128(word, sizeof(char) * word_length, HASH_SEED, &hash_output);

    hash_number = (hash_output[0] + hash_output[1] + hash_output[2] + hash_output[3]) % N;
    return hash_number;
}