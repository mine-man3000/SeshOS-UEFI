#pragma once
#include "../ahci/ahci.h"
#include "../renderer.h"

extern AHCI::Port newPort;

#define regionResevered 0
#define FATRegion 1
#define RootDirRegion 2 //doesn't exist on FAT32
#define DataRegion 3

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
    const char* OEMName[8];     // offset of 3 bytes with a size of 8 bytes
    int BytesPerSec;            // offset of 11 bytes with a size of 2 bytes
    int SecPerClus;             // offset of 13 bytes with a size of 1 byte
    int ResSecCount;            // offset of 14 bytes with a size of 2 bytes
    int NumFats;                // offset of 16 bytes with a size of 1 byte
    int RootEntryCount;         // offset of 17 bytes with a size of 2 bytes
    int TotalSecs16;            // offset of 19 bytes with a size of 2 bytes
    int Media;                  // offset of 21 bytes with a size of 1 byte 
    int FATSize16;              // offset of 22 bytes with a size of 2 bytes
    int SecPerTrack;            // offset of 24 bytes with a size of 2 bytes
    int NumHeads;               // offset of 26 bytes with a size of 2 bytes
    int HiddenSecs;             // offset of 28 bytes with a size of 4 bytes
    int TotalSec32;             // offset of 32 bytes with a size of 4 bytes
    int DrvNum;                 // offset of 36 bytes with a size of 1 byte
    int Reserved1;              // offset of 37 bytes with a size of 1 byte
    int BootSig;                // offset of 38 bytes with a size of 1 byte
    int VolID;                  // offset of 39 bytes with a size of 4 bytes
    const char* VolLab[11];     // offset of 43 bytes with a size of 11 bytes
    const char* FilSysType[8];  // offset of 53 bytes with a size of 8 bytes
    int SigWord;                // offset of 510 bytes with a size of 2 bytes
};

void FillBPB();