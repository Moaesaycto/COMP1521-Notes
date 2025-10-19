#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void find_and_replace(FILE *input_stream, FILE *output_stream, char find, char replace) {
    int c = 0;
    c = fgetc(input_stream);
    while (c != EOF) {
        if (c == find) {
            c = replace;
        }
        fputc(c, output_stream);
        c = fgetc(input_stream);
    }
}


int char_count(FILE *input_stream, char find) {
    int count = 0;
    int c = 0;
    c = fgetc(input_stream);
    while (c != EOF) {
        if (c == find) {
            count++;
        }
        c = fgetc(input_stream);
    }
    return count;
}


void find_byte(FILE *input_stream, int n) {
    // You must use fopen(, "rb");
    fseek(input_stream, n, SEEK_SET);
    int c = fgetc(input_stream);
    printf("The character in byte %d is %c.\n", n, c);
}


int main(int argc, char *argv[]) {
    FILE *out_f = fopen("result.txt", "w+");
    if (out_f == NULL) {
        perror("result.txt");
        return EXIT_FAILURE;
    }

    FILE *in_f = fopen(argv[1], "r");
    if (in_f == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    // find_and_replace(in_f, out_f, 'e', 'k');
    // printf("%d\n", char_count(in_f, 'e'));
    find_byte(in_f, 30);
    fclose(out_f);
    fclose(in_f);

    return EXIT_SUCCESS;
}