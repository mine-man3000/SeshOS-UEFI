#pragma once
#include "renderer.h"
#include "cstr.h"

class Shell
{
    public:
        void PrintPrompt();
        void TestCMD(char* input);
};

extern Shell *newShell;