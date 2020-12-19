#pragma once

#include <cstdint>
#include <vector>


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

struct DE {
    unsigned char fileName[8];
    unsigned char fileExt[3];
    unsigned char attributes;
    unsigned char caseFlag;
    unsigned char createTimeMS;
    unsigned short createTime;
    unsigned short createDate;
    unsigned short accessedDate;
    unsigned short startClusterH;
    unsigned short timestamp;
    unsigned short datestamp;
    unsigned short startClusterL;
    unsigned long fileSize;
};


class FAT {
protected:
    std::vector<uint32_t> FATTable;
    BPB BIOS_ParameterBlock;
    BS BootSector;
    DE DirEntry;
    uint32_t clustersAmount;
    uint32_t diskDescriptor;
    uint32_t firstDataSector;
    uint32_t rootDirSectors;

    uint32_t ReadSectors(uint32_t, void *, uint32_t);

    uint32_t WriteSectors(uint32_t, void *, uint32_t);

public:
    FAT(uint32_t);

    void CreateFAT(const char *);

    uint32_t ReadCluster(uint32_t, void *);

    uint32_t WriteCluster(uint32_t, void *);

    void ReadFat(uint32_t, uint32_t *);

    void WriteFat(uint32_t, uint32_t);

    uint32_t FindFirstAvailableCluster();

    std::vector<uint32_t> GetClusterChain(uint32_t startCluster);

};

class FAT12 : public FAT {
public:
    FAT12(uint32_t);
};

class FAT16 : public FAT {
    FAT16(uint32_t);
};

class FAT32 : public FAT {
    FAT32(uint32_t);
};

