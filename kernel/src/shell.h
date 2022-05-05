#pragma once
#include "renderer.h"

class Shell
{
    public:
        void PrintPrompt();
        void TestCMD(const char* input);
};

extern Shell *newShell;