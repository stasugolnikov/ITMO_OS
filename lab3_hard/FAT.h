#pragma once

#include <cstdint>

enum FAT_Type {
    FAT12,
    FAT16,
    FAT32
};

/*
  BPB stands BIOS parameter block
  It is placed at the beginning of Boot Sector
*/
struct BPB {
    uint8_t BS_jmpBoot[3] = {0xeb, 0x3c, 0x90};        // 0x00 jmp command to boot code
    char BS_OEMName[8];        // 0x03 OEM Name
    uint16_t BPB_BytsPerSec;       // 0x0b Bytes per sector 512,1024,2048 or 4096
    uint8_t BPB_SecPerClus;       // 0x0d Sectors per Cluster
    uint16_t BPB_RsvdSecCnt;       // 0x0e Reserved sectors count
    uint8_t BPB_NumFATs = 0x02;          // 0x10 FATs number
    uint16_t BPB_RootEntCnt;       // 0x11 (not used for FAT32)
    uint16_t BPB_TotSec16;         // 0x13 (not used for FAT32)
    uint8_t BPB_Media = 0xf8;            // 0x15 (not used)
    uint16_t BPB_FATSz16;          // 0x16 (not used for FAT32)
    uint16_t BPB_SecPerTrk = 0;        // 0x18 (SPT geometry for CHS)
    uint16_t BPB_NumHeads = 0;         // 0x1a (HPC geometry for CHS)
    uint32_t BPB_HiddSec;          // 0x1c (Sectors before this partition)
    uint32_t BPB_TotSec32;         // 0x20 (Total sectors must be !=0 for FAT32)
    uint32_t BPB_FATSz32;          // 0x24 Sectors count in one FAT
    uint16_t BPB_ExtFlags;         // 0x28 See Microsoft document
    uint16_t BPB_FSVer = 0;            // 0x2a Version of FAT32 filesystem
    uint32_t BPB_RootClus = 2;         // 0x2c Root Directory cluster number
    uint16_t BPB_FSInfo = 1;           // 0x30 Reserved = 1 usially see doc...
    uint16_t BPB_BkBootSec = 6;        // 0x32 Sector in reserve area with Boot Sect Copy
    uint8_t BPB_Reserved[12];     // 0x34

};

struct BS {
    uint8_t BS_DrvNum = 0x80;
    uint8_t BS_Reserved1 = 0;
    uint8_t BS_BootSig = 0x29;
    uint32_t BS_VolID;
    char BS_VolLab[11];
    char BS_FilSysType[8];
};


class FAT {
    BPB BIOS_ParameterBlock;
    BS BootSector;

public:
    FAT(FAT_Type, uint32_t);

    void CreateFAT(const char*);
};


