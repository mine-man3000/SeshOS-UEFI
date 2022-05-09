#pragma once
#include "renderer.h"
#include "cstr.h"
#include "fs/fat12.h"
#include "video/video.h"

class Shell
{
    public:
        void PrintPrompt();
        void TestCMD(char* input);
        bool shouldPrint;
};

extern Shell *newShell;