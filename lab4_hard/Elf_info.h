#pragma once

#include "my_elf.h"
#include <string>
#include <fstream>
#include <vector>

class Elf_info {
    std::ifstream ifs;
    Elf64_Ehdr elf64_Ehdr{};
    std::vector<Elf64_Phdr> ptable;
    std::vector<Elf64_Shdr> shtable;
//    Elf64_Sym elf64_Sym;
    std::vector<char> data;

public:
    Elf_info(std::string& file_path);

};



