#include <fcntl.h>
#include <zconf.h>
#include "FAT.h"

FAT::FAT(FAT_Type type, uint32_t size){
    if (type == FAT12) {
        BIOS_ParameterBlock.BPB_RsvdSecCnt = 0100;
        BIOS_ParameterBlock.BPB_RootEntCnt = 0010;
        BIOS_ParameterBlock.BPB_BytsPerSec = 512;
        BIOS_ParameterBlock.BPB_SecPerClus = 4;
        uint16_t clustersAmount = size / 512;
        BIOS_ParameterBlock.BPB_TotSec16 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
        BIOS_ParameterBlock.BPB_TotSec32 = 0;
        BIOS_ParameterBlock.BPB_NumFATs = 2;
        BootSector.BS_FilSysType[0] = 'F';
        BootSector.BS_FilSysType[1] = 'A';
        BootSector.BS_FilSysType[2] = 'T';
        BootSector.BS_FilSysType[3] = '1';
        BootSector.BS_FilSysType[4] = '2';
        BootSector.BS_FilSysType[5] = ' ';
        BootSector.BS_FilSysType[6] = ' ';
        BootSector.BS_FilSysType[7] = ' ';
    }
    else if (type == FAT16) {
        BIOS_ParameterBlock.BPB_RsvdSecCnt = 0100;
        BIOS_ParameterBlock.BPB_RootEntCnt = 0200;
        BIOS_ParameterBlock.BPB_SecPerClus = 4;
        uint16_t clustersAmount = size / 512;
        BIOS_ParameterBlock.BPB_TotSec16 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
        BIOS_ParameterBlock.BPB_TotSec32 = 0;
        BIOS_ParameterBlock.BPB_BytsPerSec = 512;
        BIOS_ParameterBlock.BPB_NumFATs = 2;
        BootSector.BS_FilSysType[0] = 'F';
        BootSector.BS_FilSysType[1] = 'A';
        BootSector.BS_FilSysType[2] = 'T';
        BootSector.BS_FilSysType[3] = '1';
        BootSector.BS_FilSysType[4] = '6';
        BootSector.BS_FilSysType[5] = ' ';
        BootSector.BS_FilSysType[6] = ' ';
        BootSector.BS_FilSysType[7] = ' ';
    } else if (type == FAT32) {
        BIOS_ParameterBlock.BPB_RsvdSecCnt = 2000;
        BIOS_ParameterBlock.BPB_RootEntCnt = 0000;
        BIOS_ParameterBlock.BPB_TotSec16 = 0;
        BIOS_ParameterBlock.BPB_FATSz16 = 0;
        BIOS_ParameterBlock.BPB_BytsPerSec = 512;
        BIOS_ParameterBlock.BPB_SecPerClus = 4;
        uint16_t clustersAmount = size / 512;
        BIOS_ParameterBlock.BPB_TotSec32 = BIOS_ParameterBlock.BPB_SecPerClus * clustersAmount;
        BIOS_ParameterBlock.BPB_NumFATs = 2;
        BootSector.BS_FilSysType[0] = 'F';
        BootSector.BS_FilSysType[1] = 'A';
        BootSector.BS_FilSysType[2] = 'T';
        BootSector.BS_FilSysType[3] = '3';
        BootSector.BS_FilSysType[4] = '2';
        BootSector.BS_FilSysType[5] = ' ';
        BootSector.BS_FilSysType[6] = ' ';
        BootSector.BS_FilSysType[7] = ' ';
    }

}

void FAT::CreateFAT(const char * name) {
    int fd = open(name, O_CREAT | O_WRONLY, 0777);
    write(fd, &BIOS_ParameterBlock, sizeof(BIOS_ParameterBlock));
    write(fd, &BootSector, sizeof(BootSector));
}