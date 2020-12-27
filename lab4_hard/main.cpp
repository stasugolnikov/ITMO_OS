#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include "Elf_info.h"



int main(int argc, char *argv[]) {

    Elf_info elf_info(argv[1]);
    elf_info.write_info(1);

    return 0;
}