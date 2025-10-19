#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int get_bit(uint64_t value, int n) {
    return (value >> n) & 1;
}

int change_bit(uint64_t value, int n) {
    return value ^ (1UL << n);
}

void print_bits(uint64_t value) {
    for (int i = 8*sizeof(value) - 1; i >= 0; i--) {
        printf("%lu", (value >> i) & 1);
    }
    printf("\n");
}

void print_hex(uint64_t value) {
    printf("0x");
    for (int digit = 2 * sizeof(value) - 1; digit >= 0; digit--) {
        printf("%c", "0123456789ABCDEF"[(value >> 4 * digit) & 0xF]);
    }
    printf("\n");
}

int main(void) {
    print_hex(3735928559);
    return EXIT_SUCCESS;
}
