#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    Timer();               // Constructor
    float GetDeltaTime();  // Returns time since last frame
    void Tick();           // Updates last frame time

private:
    steady_clock::time_point lastFrame; // Time point of last frame
    float deltaTime;                    // Stores delta time between frames
};
