#include "pit.h"
#include "../kernelUtil.h"

namespace PIT
{
    double TimeSinceBoot = 0;

    uint16_t Divisor = 65535;

    void Sleepd(double seconds)
    {
        double startTime = TimeSinceBoot;
        uint32_t end = startTime + seconds * GetFrequency();
        while (TimeSinceBoot < end)
        {
            Tick();
            GlobalRenderer->CursorPosition = {0,0};
            GlobalRenderer->Print(" ");
            //asm("hlt");
        }
    }

    void Sleep(uint64_t milliseconds)
    {
        double startTime = TimeSinceBoot;
        while (TimeSinceBoot < startTime + (milliseconds * 1000))
        {
            /* code */
        }
        
        //Sleepd((double)milliseconds / 1000);
    }

    void SetDivisor(uint16_t divisor)
    {
        if (divisor < 100)
            divisor = 100;
        Divisor = divisor;
        outb(0x40, (uint8_t)(divisor & 0x00ff));
        io_wait();
        outb(0x40, (uint8_t)((divisor & 0xff00) >> 8));
    }

    uint64_t GetFrequency()
    {
        return BaseFrequency / Divisor;
    }

    void SetFrequency(uint64_t frequency)
    {
        SetDivisor(BaseFrequency / frequency);
    }

    void Tick()
    {
        TimeSinceBoot += 1 / (double)GetFrequency();
    }
}