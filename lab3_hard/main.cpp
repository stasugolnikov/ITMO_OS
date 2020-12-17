#include <iostream>
#include "FAT.h"


int main() {

    FAT fat(FAT32, 1024);
    fat.CreateFAT("a.img");

    return 0;
}
