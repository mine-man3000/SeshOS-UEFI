#pragma once
#include "../ahci/ahci.h"
#include "../renderer.h"

extern uint8_t* myBuffer;

#define ReadOnly        0x01
#define HiddenFile      0x02
#define SysFile         0x04
#define VolLabel        0x08
#define LongFileName    0x0f
#define Dir             0x10
#define Archive         0x20

// if(CountofClusters < 4085) 
// { 
//     /* Volume is FAT12 */
// }
// else if(CountofClusters < 65525)
// {
//     /* Volume is FAT16 */
// }
// else
// {
//     /* Volume is FAT32 */ 
// }

//fat12 can't have more then 4084 clusters
//fat16 can't have less then 4085 clusters and more then 65524 clusters

struct BiosParamBlock
{
    char OEMName[8];            // offset of 3 bytes with a size of 8 bytes
    uint64_t BytesPerSec;       // offset of 11 bytes with a size of 2 bytes
    uint64_t SecPerClus;        // offset of 13 bytes with a size of 1 byte
    uint64_t ResSecCount;       // offset of 14 bytes with a size of 2 bytes
    uint64_t NumFats;           // offset of 16 bytes with a size of 1 byte
    uint64_t RootEntryCount;    // offset of 17 bytes with a size of 2 bytes
    uint64_t TotalSecs16;       // offset of 19 bytes with a size of 2 bytes
    uint64_t Media;             // offset of 21 bytes with a size of 1 byte 
    uint64_t FATSize16;         // offset of 22 bytes with a size of 2 bytes
    uint64_t SecPerTrack;       // offset of 24 bytes with a size of 2 bytes
    uint64_t NumHeads;          // offset of 26 bytes with a size of 2 bytes
    uint64_t HiddenSecs;        // offset of 28 bytes with a size of 4 bytes
    uint64_t TotalSec32;        // offset of 32 bytes with a size of 4 bytes
    uint64_t DrvNum;            // offset of 36 bytes with a size of 1 byte
    uint64_t Reserved1;         // offset of 37 bytes with a size of 1 byte
    uint64_t BootSig;           // offset of 38 bytes with a size of 1 byte
    char VolID[4];              // offset of 39 bytes with a size of 4 bytes
    char VolLab[11];            // offset of 43 bytes with a size of 11 bytes
    char FilSysType[8];         // offset of 53 bytes with a size of 8 bytes
    char SigWord[2];            // offset of 510 bytes with a size of 2 bytes
};

struct FatFile
{
    char FileName[13];
    uint64_t Flags;
    uint64_t FileCreationTime[1]; //tenths of seconds
    uint64_t CreationTime[2];     //H,M,S
    uint64_t CreationDate[2];
    uint64_t AccessDate[2];
    uint64_t ModifiedTime[2];
    uint64_t ModifiedDate[2];
    uint64_t FileSize[4];
    bool skip;
};

void ls();
void volInfo();

extern BiosParamBlock BPB;
extern FatFile Files[224];
extern int fileCount;

int FillFiles(AHCI::Port *port);
void FillBPB(AHCI::Port *port);
void ConvertFileNames();
