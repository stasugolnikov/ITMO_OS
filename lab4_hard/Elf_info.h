#pragma once

#include "my_elf.h"
#include <string>
#include <fstream>
#include <vector>

class Elf_info {
    std::ifstream ifs;
    Elf64_Ehdr elf64_Ehdr{};
    std::vector<Elf64_Phdr> phtable;
    std::vector<Elf64_Shdr> shtable;
    std::vector<Elf64_Sym> symtable;
    std::vector<Elf64_Rel> reltable;
    char* names;
    std::vector <Elf64_Shdr> kostil;
    std::vector<char> data;


public:
     explicit Elf_info(const char* file_path);
     void write_info(int descriptor);
};



