#pragma once

#define	SHT_SYMTAB	2
#define	SHT_DYNSYM	11
#define	SHT_REL		9
#define	SHT_NULL		0
#define	SHT_PROGBITS		1
#define	SHT_SYMTAB		2
#define	SHT_STRTAB		3
#define	SHT_RELA		4
#define	SHT_HASH		5
#define	SHT_DYNAMIC		6
#define	SHT_NOTE		7
#define	SHT_NOBITS		8
#define	SHT_REL			9
#define	SHT_SHLIB		10
#define	SHT_DYNSYM		11
#define	SHT_INIT_ARRAY		14
#define	SHT_FINI_ARRAY		15
#define	SHT_PREINIT_ARRAY	16
#define	SHT_GROUP		17
#define	SHT_SYMTAB_SHNDX	18


#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11


#define	SHT_GNU_verdef		0x6ffffffd
#define	SHT_GNU_verneed		0x6ffffffe
#define	SHT_GNU_versym		0x6fffffff


#define	ET_NONE		0		
#define	ET_REL		1
#define	ET_EXEC		2
#define	ET_DYN		3
#define	ET_CORE		4

#define	EI_VERSION	6


#define EV_NONE		0
#define EV_CURRENT	1

#define	ELF64_ST_BIND(info)		((info) >> 4)
#define	ELF64_ST_TYPE(info)		((info) & 0xf)

#define	STB_LOCAL	0
#define	STB_GLOBAL	1
#define	STB_WEAK	2

#define	STT_NOTYPE	0
#define	STT_OBJECT	1
#define	STT_FUNC	2
#define	STT_SECTION	3
#define	STT_FILE	4
#define	STT_COMMON	5
#define	STT_TLS		6

#define	SHN_XINDEX	0xffff


typedef unsigned long long	Elf64_Addr;
typedef unsigned short		Elf64_Half;
typedef unsigned long long	Elf64_Off;
typedef int			        Elf64_Sword;
typedef long long		    Elf64_Sxword;
typedef	unsigned int		Elf64_Word;
typedef	unsigned long long	Elf64_Xword;
typedef	unsigned long long	Elf64_Lword;
typedef unsigned long long	Elf32_Lword;

typedef struct {
    unsigned char	e_ident[16];	/* ident bytes */
    Elf64_Half	    e_type;			/* file type */
    Elf64_Half	    e_machine;		/* target machine */
    Elf64_Word	    e_version;		/* file version */
    Elf64_Addr	    e_entry;		/* start address */
    Elf64_Off	    e_phoff;		/* phdr file offset */
    Elf64_Off	    e_shoff;		/* shdr file offset */
    Elf64_Word	    e_flags;		/* file flags */
    Elf64_Half	    e_ehsize;		/* sizeof ehdr */
    Elf64_Half	    e_phentsize;		/* sizeof phdr */
    Elf64_Half	    e_phnum;		/* number phdrs */
    Elf64_Half	    e_shentsize;		/* sizeof shdr */
    Elf64_Half	    e_shnum;		/* number shdrs */
    Elf64_Half	    e_shstrndx;		/* shdr string index */
} Elf64_Ehdr;

typedef struct {
    Elf64_Word	p_type;		/* entry type */
    Elf64_Word	p_flags;	/* entry flags */
    Elf64_Off	p_offset;	/* file offset */
    Elf64_Addr	p_vaddr;	/* virtual address */
    Elf64_Addr	p_paddr;	/* physical address */
    Elf64_Xword	p_filesz;	/* file size */
    Elf64_Xword	p_memsz;	/* memory size */
    Elf64_Xword	p_align;	/* memory/file alignment */
} Elf64_Phdr;

typedef struct {
    Elf64_Word	sh_name;	/* section name */
    Elf64_Word	sh_type;	/* SHT_... */
    Elf64_Xword	sh_flags;	/* SHF_... */
    Elf64_Addr	sh_addr;	/* virtual address */
    Elf64_Off	sh_offset;	/* file offset */
    Elf64_Xword	sh_size;	/* section size */
    Elf64_Word	sh_link;	/* misc info */
    Elf64_Word	sh_info;	/* misc info */
    Elf64_Xword	sh_addralign;	/* memory alignment */
    Elf64_Xword	sh_entsize;	/* entry size if table */
} Elf64_Shdr;

typedef struct {
    unsigned char	st_info;	/* bind, type: ELF_64_ST_... */
    unsigned char	st_other;
    Elf64_Half	    st_shndx;	/* SHN_... */
    Elf64_Addr	    st_value;
    Elf64_Xword	    st_size;
} Elf64_Sym;

typedef struct {
    Elf64_Addr	r_offset;
    Elf64_Xword	r_info;		/* sym, type: ELF64_R_... */
} Elf64_Rel;
