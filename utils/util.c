#include <stdio.h>
#include <stdlib.h>

char image[0xA000]; // 0x8000 + 0x2000

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Please provide a bin file\n");

        exit(1);
    }

    FILE* fileptr = fopen(argv[1], "rb");
    if(fileptr == NULL) {
        printf("Unable to open file\n");

        exit(1);
    }

    fread(image, sizeof(char), 0x10000, fileptr);
    fclose(fileptr);

    FILE* fileptr1 = fopen(argv[1], "wb");

    fwrite(image + 0x8000, sizeof(char), 0x2000, fileptr1);
    fclose(fileptr1);
}
