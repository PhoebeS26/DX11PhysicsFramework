#include <string>
#include <Windows.h>
#include <cstdio>

class Debug
{
public:

    // Regular string
    static void Print(const std::string& message)
    {
        OutputDebugStringA(message.c_str());
    }

    // String with int
    static void Print(const std::string& label, int value)
    {
        char buffer[128];
        sprintf_s(buffer, "%s: %d\n", label.c_str(), value);
        OutputDebugStringA(buffer);
    }

    // String with float
    static void Print(const std::string& label, float value)
    {
        char buffer[128];
        sprintf_s(buffer, "%s: %f\n", label.c_str(), value);
        OutputDebugStringA(buffer);
    }

};
