#include <fcntl.h>
#include <zconf.h>
#include <unistd.h>
#include "FAT.h"

FAT::FAT(uint32_t size) {
    BootSector.BS_FilSysType[0] = 'F';
    BootSector.BS_FilSysType[1] = 'A';
    BootSector.BS_FilSysType[2] = 'T';
    BootSector.BS_FilSysType[3] = '1';
    BootSector.BS_FilSysType[5] = ' ';
    BootSector.BS_FilSysType[6] = ' ';
    BootSector.BS_FilSysType[7] = ' ';
    BIOS_ParameterBlock.BPB_BytsPerSec = 512;
    BIOS_ParameterBlock.BPB_SecPerClus = 4;
    BIOS_ParameterBlock.BPB_NumFATs = 2;
    clustersAmount = size / BIOS_ParameterBlock.BPB_BytsPerSec;
    FATTable = std::vector<uint32_t>(clustersAmount, 0);
    rootDirSectors = ((BIOS_ParameterBlock.BPB_RootEntCnt * 32) + (BIOS_ParameterBlock.BPB_BytsPerSec - 1))
                     / BIOS_ParameterBlock.BPB_BytsPerSec;
    firstDataSector = BIOS_ParameterBlock.BPB_RsvdSecCnt +
                      (BIOS_ParameterBlock.BPB_NumFATs * BIOS_ParameterBlock.BPB_NumFATs) + rootDirSectors;
}

FAT12::FAT12(uint32_t size) : FAT(size) {
    BIOS_ParameterBlock.BPB_RsvdSecCnt = 0100;
    BIOS_ParameterBlock.BPB_RootEntCnt = 0010;
    BIOS_ParameterBlock.BPB_TotSec16 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
    BIOS_ParameterBlock.BPB_TotSec32 = 0;
    BootSector.BS_FilSysType[4] = '2';

}

FAT16::FAT16(uint32_t size) : FAT(size) {
    BIOS_ParameterBlock.BPB_RsvdSecCnt = 0100;
    BIOS_ParameterBlock.BPB_RootEntCnt = 0200;
    BIOS_ParameterBlock.BPB_TotSec16 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
    BIOS_ParameterBlock.BPB_TotSec32 = 0;
    BootSector.BS_FilSysType[4] = '6';

}

FAT32::FAT32(uint32_t size) : FAT(size) {
    BIOS_ParameterBlock.BPB_RsvdSecCnt = 2000;
    BIOS_ParameterBlock.BPB_RootEntCnt = 0000;
    BIOS_ParameterBlock.BPB_TotSec16 = 0;
    BIOS_ParameterBlock.BPB_FATSz16 = 0;
    BIOS_ParameterBlock.BPB_TotSec32 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
    BootSector.BS_FilSysType[3] = '3';
    BootSector.BS_FilSysType[4] = '2';
}

void FAT::CreateFAT(const char *name) {
    int fd = open(name, O_CREAT | O_WRONLY, 0777);
    diskDescriptor = fd;
    write(fd, &BIOS_ParameterBlock, sizeof(BIOS_ParameterBlock));
    write(fd, &BootSector, sizeof(BootSector));
}

uint32_t FAT::ReadSectors(uint32_t logicalLBA, void *buffer, uint32_t count) {
    lseek(diskDescriptor, logicalLBA * 512, SEEK_SET);
    uint32_t size = read(diskDescriptor, buffer, count * 512);
    return size / 512;
}

uint32_t FAT::WriteSectors(uint32_t logicalLBA, void *buffer, uint32_t count) {
    lseek(diskDescriptor, logicalLBA * 512, SEEK_SET);
    uint32_t size = write(diskDescriptor, buffer, count * 512);
    return size / 512;
}

uint32_t FAT::ReadCluster(uint32_t cluster, void *buffer) {
    uint32_t logicalLBA = firstDataSector + (cluster - 2) * BIOS_ParameterBlock.BPB_SecPerClus;
    return ReadSectors(logicalLBA, buffer, BIOS_ParameterBlock.BPB_SecPerClus);
}

uint32_t FAT::WriteCluster(uint32_t cluster, void *buffer) {
    uint32_t logicalLBA = firstDataSector + (cluster - 2) * BIOS_ParameterBlock.BPB_SecPerClus;
    return WriteSectors(logicalLBA, buffer, BIOS_ParameterBlock.BPB_SecPerClus);
}

void FAT::ReadFat(uint32_t cluster, uint32_t *value) {
    *value = FATTable[cluster];
}

void FAT::WriteFat(uint32_t cluster, uint32_t value) {
    FATTable[cluster] = value;
}

uint32_t FAT::FindFirstAvailableCluster() {
    for (int i = 0; i < FATTable.size(); i++)
        if (FATTable[i] == 0) return i;
    return -1;
}

std::vector<uint32_t> FAT::GetClusterChain(uint32_t startCluster){
    std::vector<uint32_t> ans;
    for (int i = startCluster; i != 0x0FFFFFF7; i = FATTable[i])
        ans.push_back(FATTable[i]);
    return ans;
}