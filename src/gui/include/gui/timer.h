#pragma once

#include "aliases.h"

#include <chrono>

struct Timer
{
    Timer() {
        SetStartTime();
        Tick(); 
    }

    void Tick() {current_time = std::chrono::high_resolution_clock::now();}

    bool TimeDurationPassed(int miliseconds) {
        if (std::chrono::duration<double, std::milli>(current_time - start_time) > std::chrono::duration<double, std::milli>(miliseconds)) {
            SetStartTime();
            return true;
        }
        return false;
    }

private:
    void SetStartTime() {start_time = std::chrono::high_resolution_clock::now();}
    TimePoint start_time;
    TimePoint current_time;
};