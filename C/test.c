#include "string.h"

void utf8rev(char *str)
{
    /* this assumes that str is valid UTF-8 */
    char    *scanl, *scanr, *scanr2, c;

    /* first reverse the string */
    for (scanl= str, scanr= str + strlen(str); scanl < scanr;)
        c= *scanl, *scanl++= *--scanr, *scanr= c;

    /* then scan all bytes and reverse each multibyte character */
    for (scanl= scanr= str; c= *scanr++;) {
        if ( (c & 0x80) == 0) // ASCII char
            scanl= scanr;
        else if ( (c & 0xc0) == 0xc0 ) { // start of multibyte
            scanr2= scanr;
            switch (scanr - scanl) {
                case 4: c= *scanl, *scanl++= *--scanr, *scanr= c; // fallthrough
                case 3: // fallthrough
                case 2: c= *scanl, *scanl++= *--scanr, *scanr= c;
            }
            scanr= scanl= scanr2;
        }
    }
}

// quick and dirty main for testing purposes
#include "stdio.h"

int main(int argc, char* argv[])
{
    char buffer[256];
    buffer[sizeof(buffer)-1]= '\0';

    while (--argc > 0) {
        strncpy(buffer, argv[argc], sizeof(buffer)-1); // don't overwrite final null
        printf("%s → ", buffer);
        utf8rev(buffer);
        printf("%s\n", buffer);
    }
    return 0;
}