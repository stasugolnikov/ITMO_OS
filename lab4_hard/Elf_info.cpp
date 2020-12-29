#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include "Elf_info.h"

Elf_info::Elf_info(const char *file_path) {
    ifs.open(file_path, std::ios::binary);

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

    /// copy program header table
    phtable.resize(elf64_Ehdr.e_phnum);
    std::copy(data.begin() + elf64_Ehdr.e_phoff,
              data.begin() + elf64_Ehdr.e_phoff + elf64_Ehdr.e_phentsize * elf64_Ehdr.e_phnum,
              (char *) &phtable[0]);

    Elf64_Shdr initial;
    copy(data.begin() + elf64_Ehdr.e_shoff,
         data.begin() + elf64_Ehdr.e_shoff + elf64_Ehdr.e_shentsize,
         (char *) &initial);

    /// copy section header table
    shtable.resize(elf64_Ehdr.e_shnum);
    std::copy(data.begin() + elf64_Ehdr.e_shoff,
              data.begin() + elf64_Ehdr.e_shoff + elf64_Ehdr.e_shnum * elf64_Ehdr.e_shentsize,
              (char *) &shtable[0]);

    names = &data[shtable[elf64_Ehdr.e_shstrndx].sh_offset];
    if (elf64_Ehdr.e_shstrndx == SHN_XINDEX) {
        int index = initial.sh_link;
        names = &data[shtable[index].sh_offset];
    }

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
            std::copy(data.begin() + sh.sh_offset, data.begin() + sh.sh_offset + sizeof(Elf64_Sym),
                      (char *) &symtable[symtable.size() - 1]);
            kostil.push_back(sh);
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

    std::cout << "\t\tElf header:\n";
    std::cout << "File type: ";
    switch (elf64_Ehdr.e_type) {
        case ET_NONE:
            std::cout << "unknonw type\n";
            break;
        case ET_REL:
            std::cout << "relocatable file\n";
            break;
        case ET_EXEC:
            std::cout << "executable file\n";
            break;
        case ET_DYN:
            std::cout << "shared object\n";
            break;
        case ET_CORE:
            std::cout << "core file\n";
            break;
        default:
            printf("error\n");
            break;
    }
    std::cout << "File version: ";
    switch (elf64_Ehdr.e_ident[EI_VERSION]) {
        case EV_NONE:
            printf("invalid version\n");
            break;
        case EV_CURRENT:
            printf("current version\n");
            break;
        default:
            printf("error version\n");
            break;
    }

    std::cout << "\t\tProgram headers table:\n";
    for (auto &ph : phtable) {
        std::cout << "Type: ";
        switch (ph.p_type) {
            case PT_NULL:
                std::cout << "NULL  ";
                break;
            case PT_LOAD:
                std::cout << "LOAD  ";
                break;
            case PT_DYNAMIC:
                std::cout << "DYNAMIC  ";
                break;
            case PT_INTERP:
                std::cout << "INTERP  ";
                break;
            case PT_NOTE:
                std::cout << "NOTE  ";
                break;
            case PT_SHLIB:
                std::cout << "SHLIB  ";
                break;
            case PT_PHDR:
                std::cout << "PHDR  ";
                break;
            case PT_TLS:
                std::cout << "TLS  ";
                break;
            case PT_NUM:
                std::cout << "NUM  ";
                break;
            default:
                std::cout << "Unknown  ";
                break;

        }
        std::cout << "   MemSize: " << ph.p_memsz << std::endl;
    }

    std::cout << "\t\tSection table:\n";
    for (auto &sh : shtable) {
        std::cout << "Section name: " << names + sh.sh_name << "  ";
        std::cout << "   Section type: ";
        switch (sh.sh_type) {
            case SHT_NULL:
                std::cout << "NULL  ";
                break;

            case SHT_PROGBITS:
                std::cout << "PROGBITS  ";
                break;

            case SHT_SYMTAB:
                std::cout << "SYMTAB  ";
                break;

            case SHT_STRTAB:
                std::cout << "STRTAB  ";
                break;

            case SHT_RELA:
                std::cout << "RELA  ";
                break;

            case SHT_HASH:
                std::cout << "HASH  ";
                break;

            case SHT_DYNAMIC:
                std::cout << "DYNSYM  ";
                break;

            case SHT_NOTE:
                std::cout << "NOTE  ";
                break;

            case SHT_NOBITS:
                std::cout << "NOBITS  ";
                break;

            case SHT_REL:
                std::cout << "REL  ";
                break;

            case SHT_SHLIB:
                std::cout << "SHLIB  ";
                break;

            case SHT_DYNSYM:
                std::cout << "DYNSYM  ";
                break;

            case SHT_INIT_ARRAY:
                std::cout << "INIT_ARRAY  ";
                break;

            case SHT_FINI_ARRAY:
                std::cout << "FINIT_ARRAY  ";
                break;

            case SHT_PREINIT_ARRAY:
                std::cout << "PREINIT_ARRAY  ";
                break;

            case SHT_GROUP:
                std::cout << "GROUP  ";
                break;

            case SHT_SYMTAB_SHNDX:
                std::cout << "SYMTAB_SHNDX  ";
                break;

            case SHT_GNU_verdef:
                std::cout << "VERDEF  ";
                break;

            case SHT_GNU_verneed:
                std::cout << "VERNEED  ";
                break;

            case SHT_GNU_versym:
                std::cout << "VERSYM  ";
                break;

            default:
                std::cout << "Unknown  ";
                break;
        }
        std::cout << "   Section size: " << sh.sh_entsize << std::endl;
    }

    std::cout << "\t\tSymbol table:\n";
    int i = 0;
    for (auto &sym : symtable) {
        std::cout << "Sym Name: " << &names[kostil[i].sh_name] << "    ";
        std::cout << "  Sym Value: " << sym.st_value << " ";
        std::cout << "   Symbol info: ";
        switch (ELF64_ST_TYPE(sym.st_info)) {
            case STT_NOTYPE:
                std::cout << "NOTYPE  ";
                break;
            case STT_OBJECT:
                std::cout << "OBJECT  ";
                break;
            case STT_FUNC:
                std::cout << "FUNC  ";
                break;
            case STT_SECTION:
                std::cout << "SECTION  ";
                break;
            case STT_FILE:
                std::cout << "FILE  ";
                break;
            case STT_COMMON:
                std::cout << "COMMON  ";
                break;
            case STT_TLS:
                std::cout << "TLS  ";
                break;
            default:
                std::cout << "Unknown  ";
                break;
        }
        switch (ELF64_ST_BIND(sym.st_info)) {
            case STB_LOCAL:
                std::cout << "LOCAL  ";
                break;
            case STB_GLOBAL:
                std::cout << "GLOBAL  ";
                break;
            case STB_WEAK:
                std::cout << "WEAK  ";
                break;
            default:
                std::cout << "Unknown  ";
        }
        std::cout << std::endl;
        i++;
    }

    std::cout << "\t\tRelocation table:\n";
    for (auto &rel : reltable) {
        std::cout << "RelInfo: " << rel.r_info << std::endl;
    }

}
