#include "Timer.h"

// Constructor
Timer::Timer()
{
    lastFrame = steady_clock::now(); // Store the current time as the last frame
    deltaTime = 0.0f;                // Initialize deltaTime to 0
}

// Tick: update the last frame time and calculate delta
void Timer::Tick()
{
    auto now = steady_clock::now();                     // Get current time
    deltaTime = duration<float>(now - lastFrame).count(); // Time elapsed in seconds
    lastFrame = now;                                   // Update last frame time
}

// GetDeltaTime: return the time between last frame and now
float Timer::GetDeltaTime()
{
    return deltaTime;
}
