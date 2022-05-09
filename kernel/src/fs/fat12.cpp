#include "fat12.h"
#include "../memory/heap.h"

BiosParamBlock BPB;
FatFile Files[224];
int fileCount;
int realFileCount;
void fixFilename(char *filename, int index);

void volInfo()
{
    GlobalRenderer->Print("OEM Name:              \"");
    GlobalRenderer->Print(BPB.OEMName);
    GlobalRenderer->Print("\"\nBytes per Sector:      \"");
    
    GlobalRenderer->Print(to_string((uint64_t)BPB.BytesPerSec));
    GlobalRenderer->Print("\"\nSectors per Cluster:   \"");

    GlobalRenderer->Print(to_string((uint64_t)BPB.SecPerClus));
    GlobalRenderer->Print("\"\nReserved Sector Count: \"");

    GlobalRenderer->Print(to_string((uint64_t)BPB.ResSecCount));
    GlobalRenderer->Print("\"\nNumber of FATs:        \"");    

    GlobalRenderer->Print(to_string((uint64_t)BPB.NumFats));
    GlobalRenderer->Print("\"\nRoot Entry Count:      \"");
    
    GlobalRenderer->Print(to_string((uint64_t)BPB.RootEntryCount));
    GlobalRenderer->Print("\"\nTotal Sectors 16:      \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.TotalSecs16));
    GlobalRenderer->Print("\"\nMedia:                 \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.Media));
    GlobalRenderer->Print("\"\nFAT Size 16:           \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.FATSize16));
    GlobalRenderer->Print("\"\nSectors Per Track:     \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.SecPerTrack));
    GlobalRenderer->Print("\"\nNumber of Heads:       \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.TotalSecs16));
    GlobalRenderer->Print("\"\nNum Hidden Sectors:    \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.HiddenSecs));
    GlobalRenderer->Print("\"\nTotal Sectors 32:      \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.TotalSec32));
    GlobalRenderer->Print("\"\nDrive Number:          \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.DrvNum));
    GlobalRenderer->Print("\"\nReserved 1:            \""); 

    GlobalRenderer->Print(to_string((uint64_t)BPB.Reserved1));
    GlobalRenderer->Print("\"\nBoot Signature:        \"0x"); 

    GlobalRenderer->Print(to_hstring((uint64_t)BPB.BootSig));
    GlobalRenderer->Print("\"\nVolume ID:             \"0x"); 

    GlobalRenderer->Print(to_hstring((uint64_t)BPB.VolID));
    GlobalRenderer->Print("\"\nVolume Label:          \""); 

    GlobalRenderer->Print(BPB.VolLab);
    GlobalRenderer->Print("\"\nFile System Type:      \"");

    GlobalRenderer->Print(BPB.FilSysType);
    GlobalRenderer->Print("\"\nSignature Word:        \"0x");

    GlobalRenderer->Print(to_string((uint64_t)BPB.SigWord));
    GlobalRenderer->Print("\"\n"); 

}


//if (Files[i].FileName[0] == 'b' && Files[i].FileName[2] == NULL)
//{
//    i += 2;
//}

void ls()
{
    int hiddenFileCount = 0;

    for (int i = 0; i < fileCount; i++)
    {
        if (Files[i].Flags == LongFileName)
        {
            hiddenFileCount++;
            Files[i].skip = true;
        }
    }

    realFileCount = fileCount - hiddenFileCount;
    GlobalRenderer->Print("File count: ");
    GlobalRenderer->Print(to_string((uint64_t)realFileCount));
    GlobalRenderer->Print("\n");
    for (int i = 0; i < fileCount; i++)
    {
        if(!Files[i].skip)
        {
            if (Files[i].Flags == Dir)
            {
                GlobalRenderer->Color = 0x000000ff;
                GlobalRenderer->Print(Files[i].FileName);
                GlobalRenderer->Print("/  ");
                GlobalRenderer->Color = 0xffffffff;
                GlobalRenderer->Print("\n");
            }
            else
            {
                GlobalRenderer->Color = 0xffffffff;
                GlobalRenderer->Print(Files[i].FileName);
                GlobalRenderer->Print("  ");
                GlobalRenderer->Print("\n");
            }
        }
    }
}

void cat();

void FillBPB(AHCI::Port *port)
{
    int j = 0;
    for (int t = 3; t != 11; t++)
    {
        BPB.OEMName[j] = port->buffer[t];
        j++;
    }
    BPB.OEMName[8] = '\0';
    j = 0;
    
    if (port->buffer[11] == 0 && port->buffer[12] == 2)
    {
        BPB.BytesPerSec = 512;
    }

    if (port->buffer[11] == 0 && port->buffer[12] == 4)
    {
        BPB.BytesPerSec = 1024;
    }

    if (port->buffer[11] == 0 && port->buffer[12] == 8)
    {
        BPB.BytesPerSec = 2048;
    }

    if (port->buffer[11] == 0 && port->buffer[12] == 10)
    {
        BPB.BytesPerSec = 4096;
    }


    BPB.SecPerClus = port->buffer[13];
    BPB.ResSecCount = port->buffer[14];
    BPB.ResSecCount += port->buffer[15];
    BPB.NumFats = port->buffer[16];
    BPB.RootEntryCount = port->buffer[17];
    BPB.TotalSecs16 = port->buffer[19];
    BPB.Media = port->buffer[21];

    BPB.FATSize16 = port->buffer[22];
    BPB.SecPerTrack = port->buffer[24];
    BPB.NumHeads = port->buffer[26];
    BPB.HiddenSecs = port->buffer[28];
    BPB.TotalSec32 = port->buffer[32];
    BPB.DrvNum = port->buffer[36];
    BPB.Reserved1 = port->buffer[37];
    BPB.BootSig = port->buffer[38];

    for (int t = 39; t != 42; t++)
    {
        BPB.VolID[j] = port->buffer[t];
    }    

    for (int t = 43; t < 52; t++)
    {
        BPB.VolLab[j] = port->buffer[t];
        j++;
    }

    j = 0;
    for (int t = 54; t != 61; t++)
    {
        BPB.FilSysType[j] = port->buffer[t];
        j++;
    }

    j = 0;
    BPB.SigWord[0] = port->buffer[511];
    BPB.SigWord[1] = port->buffer[512];
}

int FillFiles(AHCI::Port *port)
{
    for (int t = 64; t != 512; t+=32)
    {
        if (port->buffer[t] == NULL)
        {
            break;
        }
        for (int i = 0; i < 11; i++)
        {
            Files[fileCount].FileName[i] = port->buffer[i+t];
        }
        Files[fileCount].Flags               = port->buffer[t + 11];
        Files[fileCount].FileCreationTime[1] = port->buffer[t + 12];  //tenths of seconds
        Files[fileCount].CreationTime[2]     = port->buffer[t + 14];  //H,M,S
        Files[fileCount].CreationDate[2]     = port->buffer[t + 15];
        Files[fileCount].AccessDate[2]       = port->buffer[t + 17];
        Files[fileCount].ModifiedTime[2]     = port->buffer[t + 19];
        Files[fileCount].ModifiedDate[2]     = port->buffer[t + 21];
        Files[fileCount].FileSize[4]         = port->buffer[t + 22];
        fileCount++;    
    }
    ConvertFileNames();
}   

/*
    3. remove the long file name crap entirely from the struct
        by taking the info from the next entry and replace info
        in current entry
    4. change fileCount to reflect this change                 
*/

void ConvertFileNames()
{
    for (int i = 0; i < fileCount; i++)
    {
        //1. convert name to lowercase
        for (int t = 0; t < 12; t++)
        {
            if(Files[i].FileName[t] >= 65 && Files[i].FileName[t] <= 90)
            {
                Files[i].FileName[t] = Files[i].FileName[t] + 32;
            }
        }
        //2. remove spaces between name and extension if they exist and add a dot in between
        fixFilename(Files[i].FileName, i);

        // if (Files[i].Flags == LongFileName)
        // {
        //     Files[i].skip = true;
        //     Files[i + 1].skip = true;
        // }
    }
}

// written by https://github.com/notvelleda
void fixFilename(char *filename, int index) {

    char fixedFilename[13]; // stores the result
    int outPos = 0; // position in output array
    int numSpaces = 0;
    bool printedExtension = false;
    
    for (int i = 0; i < 11; i ++) {
        char current = filename[i]; // char we're at

        if (current == ' ') { // skip printing if we've hit a space
            numSpaces ++;
            continue;
        } else if (numSpaces > 0 && i < 8) { // do we have spaces we skipped and should we insert them?
            for (int j = 0; j < numSpaces; j ++)
                fixedFilename[outPos ++] = ' ';
            numSpaces = 0;
        }
        
        if (i >= 8 && !printedExtension) { // reached where the dot should be, insert it before inserting first char of extension
            fixedFilename[outPos ++] = '.';
            printedExtension = true;
        }

        if (current >= 'A' && current <= 'Z') // convert to lowercase
            current += 32;

        fixedFilename[outPos ++] = current;
    }
    
    fixedFilename[outPos] = 0; // add terminating null byte to end of string

    for (int t = 0; t < 12; t++)
    {
      Files[index].FileName[t] = fixedFilename[t];
    }

}