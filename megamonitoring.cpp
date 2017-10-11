#include "megamonitoring.h"
#ifdef WIN32
#include "Windows.h"
#endif

MegaMonitoring::MegaMonitoring()
{

}


int MegaMonitoring::getTotalRAM()
{
    int ret = 0;
#ifdef WIN32
    DWORD v = GetVersion();
    DWORD major =  (DWORD)(LOBYTE(LOWORD(v)));
    DWORD minor =  (DWORD)(HIBYTE(LOWORD(v)));
    DWORD build;

    //avoid warnings
    major = major;
    minor = minor;
    if (v < 0x80000000) build = (DWORD)(HIWORD(v));
    else build = 0;

    // because compiler static links the function...
    BOOL (__stdcall*GMSEx)(LPMEMORYSTATUSEX) = 0;

    HINSTANCE hIL = LoadLibrary(L"kernel32.dll");
    GMSEx = (BOOL(__stdcall*)(LPMEMORYSTATUSEX))GetProcAddress(hIL, "GlobalMemoryStatusEx");

    if(GMSEx)
    {
        MEMORYSTATUSEX m;
        m.dwLength = sizeof(m);
        if(GMSEx(&m))
        {
            ret = (int)(m.ullTotalPhys>>20);
        }
    }
    else
    {
        MEMORYSTATUS m;
        m.dwLength = sizeof(m);
        GlobalMemoryStatus(&m);
        ret = (int)(m.dwTotalPhys>>20);
    }
#endif
    return ret;
}


int MegaMonitoring::getAvailRAM()
{
    int ret = 0;
#ifdef WIN32
    DWORD v = GetVersion();
    DWORD major =  (DWORD)(LOBYTE(LOWORD(v)));
    DWORD minor =  (DWORD)(HIBYTE(LOWORD(v)));
    DWORD build;
    if (v < 0x80000000) build = (DWORD)(HIWORD(v));
    else build = 0;

    major = major;
    minor = minor;
    // because compiler static links the function...
    BOOL (__stdcall*GMSEx)(LPMEMORYSTATUSEX) = 0;

    HINSTANCE hIL = LoadLibrary(L"kernel32.dll");
    GMSEx = (BOOL(__stdcall*)(LPMEMORYSTATUSEX))GetProcAddress(hIL, "GlobalMemoryStatusEx");

    if(GMSEx)
    {
        MEMORYSTATUSEX m;
        m.dwLength = sizeof(m);
        if(GMSEx(&m))
        {
            ret = (int)(m.ullAvailPhys>>20);
        }
    }
    else
    {
        MEMORYSTATUS m;
        m.dwLength = sizeof(m);
        GlobalMemoryStatus(&m);
        ret = (int)(m.dwAvailPhys>>20);
    }
#endif
    return ret;
}


double MegaMonitoring::getUsedPercentRAM()
{
    double total = static_cast<double>(getTotalRAM());
    double avail = static_cast<double>(getAvailRAM());

    double used = total - avail;

    return (used/total)*100;
}
