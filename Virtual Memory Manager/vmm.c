#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int PAGE_TABLE[100];
char res[100];

int parseBinInt(char addr[]) {
    int res = 0;
    int length = strlen(addr);
    int place_value = (int)pow(2, length-1);

    for (int i=0; i<length; i++) {
        if (addr[i] == '1') res += place_value;
        place_value /= 2;
    }

    return res;
}

char* toBinStr(int addr, int addrLength) {
    int mask = 1 << (addrLength-1);
    int i;
    for (i=0; i<addrLength; i++) {
        res[i] = ((addr & mask) == mask ? '1' : '0');
        mask >>= 1;
    }
    return res;
}

int main() {

    int pages, frames, frameSize;
    printf("Enter Number of pages: "); scanf("%d", &pages);
    printf("Enter Number of frames: "); scanf("%d", &frames);
    printf("Enter Frame size: "); scanf("%d", &frameSize);

    printf("Enter current page table mapping: \n");
    for (int i=0; i<pages; i++) {
        printf("page %d: ", i);
        scanf("%d", &PAGE_TABLE[i]);
    }

    char logicalAddrStr[33];
    printf("\nEnter binary logical address generated: ");
    scanf("%s", logicalAddrStr);

    int addrLength = strlen(logicalAddrStr);
    int pageBits = log2(pages);
    int wordBits = log2(frameSize);
    int frameBits = log2(frames);
    int logicalAddr = parseBinInt(logicalAddrStr);

    int pageNumber = logicalAddr >> wordBits;
    int frameNumber = PAGE_TABLE[pageNumber];
    int wordNumber = logicalAddr & ~(-1 << wordBits);

    printf("Page Number: %d\n", pageNumber);
    printf("Corresponding Frame Number: %d\n", frameNumber);
    printf("Word Number: %d\n", wordNumber);
    
    int physicalAddr = (frameNumber << wordBits) | wordNumber;
    int physicalAddrLength = frameBits + wordBits;
    toBinStr(physicalAddr, physicalAddrLength);
    printf("Corresponding Physical Address: %s\n", res);

    return 0;
}