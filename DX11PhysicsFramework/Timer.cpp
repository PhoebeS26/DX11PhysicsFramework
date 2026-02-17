#include "Timer.h"

Timer::Timer()
{
    lastFrame = steady_clock::now(); // Store the current time as the last frame
    deltaTime = 0.0f;                // Initialize deltaTime to 0
}

void Timer::Tick()
{
    auto now = steady_clock::now();                     // Get current time
    deltaTime = duration<float>(now - lastFrame).count(); // Time elapsed in seconds
    lastFrame = now;                                   // Update last frame time
}

float Timer::GetDeltaTime()
{
    return deltaTime;
}
