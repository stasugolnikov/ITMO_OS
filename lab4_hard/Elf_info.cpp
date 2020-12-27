#include "Elf_info.h"

Elf_info::Elf_info(std::string &file_path) {
    ifs.open(file_path);
    /// file to sequence of bytes
    data = std::vector<char>((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    /// copy header
    copy(data.begin(), data.begin() + sizeof(elf64_Ehdr), (char *) &elf64_Ehdr);

    /// copy process header table
    ptable.resize(elf64_Ehdr.e_phnum);
    std::copy(data.begin() + elf64_Ehdr.e_phoff,
              data.begin() + elf64_Ehdr.e_phoff + elf64_Ehdr.e_phentsize * elf64_Ehdr.e_phnum,
              (char *) &ptable[0]);

    /// copy section header table
    shtable.resize(elf64_Ehdr.e_shnum);
    copy(data.begin() + elf64_Ehdr.e_shoff,
         data.begin() + elf64_Ehdr.e_shoff + elf64_Ehdr.e_shnum * elf64_Ehdr.e_shentsize,
         (char *) &shtable[0]);
}
