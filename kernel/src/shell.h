#pragma once
#include "renderer.h"
#include "cstr.h"
#include "fs/fat12.h"


class Shell
{
    public:
        void PrintPrompt();
        void TestCMD(char* input);
};

extern Shell *newShell;