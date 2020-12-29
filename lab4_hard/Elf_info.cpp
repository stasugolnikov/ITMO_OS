#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "Elf_info.h"

Elf_info::Elf_info(const char *file_path) {
    ifs.open(file_path, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    ifs.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    ifs.seekg(0, std::ios::end);
    fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    /// file to sequence of bytes
    data.reserve(fileSize);
    data.insert(data.begin(), std::istream_iterator<char>(ifs), std::istream_iterator<char>());
    /// copy header
    copy(data.begin(), data.begin() + sizeof(elf64_Ehdr), (char *) &elf64_Ehdr);
    //std::cout << elf64_Ehdr.e_phnum << " " << elf64_Ehdr.e_shnum << '\n';

    /// copy program header table
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
    ssize_t size = 0;
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_DYNSYM || sh.sh_type == SHT_SYMTAB) {
            size++;
        }
    }
    symtable.resize(size);
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_DYNSYM || sh.sh_type == SHT_SYMTAB) {
            std::copy(data.begin() + sh.sh_offset, data.begin() + sh.sh_offset + sh.sh_entsize,
                      (char *) &symtable[symtable.size() - 1]);
        }
    }
    /// copy relocation table
    size = 0;
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_REL) {
	    size++;
        }
    }
    reltable.resize(size);
    for (auto &sh : shtable) {
        if (sh.sh_type == SHT_REL) {
            std::copy(data.begin() + sh.sh_offset, data.begin() + sh.sh_offset + sh.sh_entsize,
                      (char *) &reltable[reltable.size() - 1]);
        }
    }
}

void Elf_info::write_info(int descriptor) {
    //write(descriptor, &elf64_Ehdr, sizeof(elf64_Ehdr));
    std::cout << "File type: " << elf64_Ehdr.e_type << std::endl;
    std::cout << "Target machine: " << elf64_Ehdr.e_machine << std::endl;
    std::cout << "File version: " << elf64_Ehdr.e_version << std::endl;
    printf("Elf header written\n");

    for (auto &ph : phtable) {
       //write(descriptor, &ph, sizeof(ph));
        std::cout << "Type: " << ph.p_type << " ";

        std::cout << "MemSize: " << ph.p_memsz << std::endl;
    }
    printf("phtable written\n");

    for (auto &sh : shtable) {
        //write(descriptor, &sh, sizeof(sh));
        std::cout << "Section name: " << sh.sh_name << " ";
        std::cout << "Section size: " <<sh.sh_entsize << std::endl;
    }
    printf("shtable written\n");

    for (auto &sym : symtable) {
        //write(descriptor, &sym, sizeof(sym));
        std::cout << "Sym Value: " << sym.st_value << " ";
        std::cout << "Symbol info: " << sym.st_info << std::endl;
    }
    printf("\nsymtable written\n");

    for (auto &rel : reltable) {
        //write(descriptor, &rel, sizeof(rel));
        std::cout << "RelInfo: " << rel.r_info << std::endl;
    }
    printf("\nreltable written\n");

}
