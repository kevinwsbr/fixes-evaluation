// Example input
int work[] = {1, 2, 3, 4};
int lens[] = {3, 4, 2, 5};
int count[] = {2, 1, 1, 1};

// Create a Huffman coding table
unsigned char table[16];
int bits;

int main() {
    huffman(work, lens, count, NULL, NULL, LENS, 2, 4, &table, &bits);

    // Print the Huffman coding table
    for (int i = 0; i < 16; i++) {
        printf("%d\n", table[i]);
    }

    return 0;
}
