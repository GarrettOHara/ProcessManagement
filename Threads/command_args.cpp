#include <stdio.h>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: You need at least one argument.\n");
        return 1;
    } else {
        int i, x;
        int ch = 0;
        for (i=0; i<argc; i++) {
            std::cout << argv[i] << std::endl;
            for (x = 0; x < strlen(argv[i]); x++) {
                ch = argv[i][x];
                // if (ch == 'A' || ch == 'a' || ch == 'e')
                //     printf("Vowel\n");
                
            }
        }
    }
}