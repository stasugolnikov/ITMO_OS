#include <zconf.h>
#include <iostream>
#include "Elf_info.h"

Elf_info::Elf_info(const char* file_path) {
    ifs.open(file_path, std::ios::binary);

    /// file to sequence of bytes
     data.reserve(INT32_MAX);
     data.insert(data.begin(), std::istream_iterator<char>(ifs), std::istream_iterator<char>());
    /// copy header
    copy(data.begin(), data.begin() + sizeof(elf64_Ehdr), (char *) &elf64_Ehdr);

    /// copy process header table
    phtable.resize(elf64_Ehdr.e_phnum);
    std::copy(data.begin() + elf64_Ehdr.e_phoff,
              data.begin() + elf64_Ehdr.e_phoff + elf64_Ehdr.e_phentsize * elf64_Ehdr.e_phnum,
              (char *) &phtable[0]);

    /// copy section header table
    shtable.resize(elf64_Ehdr.e_shnum);
    std::copy(data.begin() + elf64_Ehdr.e_shoff,
              data.begin() + elf64_Ehdr.e_shoff + elf64_Ehdr.e_shnum * elf64_Ehdr.e_shentsize,
              (char *) &shtable[0]);

    /// copy symbol table
    shtable.reserve(elf64_Ehdr.e_shnum * elf64_Ehdr.e_shentsize);
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_DYNSYM || sh.sh_type == SHT_SYMTAB) {
            std::copy(data.begin() + sh.sh_offset, data.begin() + sh.sh_offset + sh.sh_entsize,
                      (char *) &symtable[symtable.size() - 1]);
        }
    }

    /// copy relocation table
    shtable.reserve(elf64_Ehdr.e_shnum * elf64_Ehdr.e_shentsize);
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_REL) {
            std::copy(data.begin() + sh.sh_offset, data.begin() + sh.sh_offset + sh.sh_entsize,
                      (char *) &reltable[reltable.size() - 1]);
        }
    }
}

void Elf_info::write_info(int descriptor) {
    write(descriptor, &elf64_Ehdr, sizeof(elf64_Ehdr));
    printf("\nElf header written\n");

    for (auto &ph : phtable) {
        write(descriptor, &ph, sizeof(ph));
    }
    printf("\nphtable written\n");


    for (auto &sh : shtable) {
        write(descriptor, &sh, sizeof(sh));
    }
    printf("\nshtable written\n");

    for (auto &sym : symtable) {
        write(descriptor, &sym, sizeof(sym));
    }
    printf("\nsymtable written\n");

    for (auto &rel : reltable) {
        write(descriptor, &rel, sizeof(rel));
    }
    printf("\nreltable written\n");

}
