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

    // String with Vector3
    static void Print(const std::string& label, const Vector3& vec)
    {
        char buffer[128];
        sprintf_s(buffer, "%s: (%.3f, %.3f, %.3f)\n", label.c_str(), vec.x, vec.y, vec.z);
        OutputDebugStringA(buffer);
    }

    static int VDebugPrintF(const char* format, va_list args) 
    {
        const UINT32 MAX_CHARS = 1024;
        static char s_buffer[MAX_CHARS];

        int charsWritten = vsnprintf(s_buffer, MAX_CHARS, format, args);
        OutputDebugStringA(s_buffer);

        return charsWritten;
    }

    static int DebugPrintF(const char* format, ...) 
    {
        va_list argList;
        va_start(argList, format);

        int charsWritten = VDebugPrintF(format, argList);
        va_end(argList);

        return charsWritten;
    }

};
