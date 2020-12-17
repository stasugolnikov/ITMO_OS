#pragma once

#include <cstdint>

enum FAT_Type {
    FAT12,
    FAT16,
    FAT32
};


struct BPB {
    uint8_t BS_jmpBoot[3] = {0xeb, 0x3c, 0x90};
    char BS_OEMName[8];
    uint16_t BPB_BytsPerSec;
    uint8_t BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t BPB_NumFATs = 0x02;
    uint16_t BPB_RootEntCnt;
    uint16_t BPB_TotSec16;
    uint8_t BPB_Media = 0xf8;
    uint16_t BPB_FATSz16;
    uint16_t BPB_SecPerTrk = 0;
    uint16_t BPB_NumHeads = 0;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;
    uint32_t BPB_FATSz32;
    uint16_t BPB_ExtFlags;
    uint16_t BPB_FSVer = 0;
    uint32_t BPB_RootClus = 2;
    uint16_t BPB_FSInfo = 1;
    uint16_t BPB_BkBootSec = 6;
    uint8_t BPB_Reserved[12];

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


