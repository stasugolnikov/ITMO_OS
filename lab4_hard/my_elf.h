#pragma once

#define	SHT_SYMTAB	2
#define	SHT_DYNSYM	11
#define	SHT_REL		9

#define	ET_NONE		0		
#define	ET_REL		1
#define	ET_EXEC		2
#define	ET_DYN		3
#define	ET_CORE		4
#define	ET_NUM		5


#define	EI_MAG0		0	
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CLASS	4	
#define	EI_DATA		5	
#define	EI_VERSION	6	
#define	EI_OSABI	7	
#define	EI_ABIVERSION	8	
#define	EI_PAD		9

#define EV_NONE		0
#define EV_CURRENT	1
#define EV_NUM		2


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
