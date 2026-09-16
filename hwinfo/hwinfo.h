#pragma once

#define HWINFO_STATIC 1

#ifdef _WIN32
    #define STRINGIFY(x) #x
    #define TOSTRING(x) STRINGIFY(x)

    #pragma comment(lib, __FILE__ "\\..\\hwinfo_cpu.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_ram.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_disk.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_os.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_gpu.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_mainboard.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_network.lib")
    #pragma comment(lib, __FILE__ "\\..\\hwinfo_battery.lib")
#else
    #include <dlfcn.h>
    inline auto _flags = RTLD_NOW | RTLD_GLOBAL;
    void* cpu = dlopen("hwinfo/libhwinfo_cpu.so", _flags);
    void* ram = dlopen("hwinfo/libhwinfo_ram.so", _flags);
    void* dsk = dlopen("hwinfo/libhwinfo_disk.so", _flags);
    void* os  = dlopen("hwinfo/libhwinfo_os.so", _flags);
    void* gpu = dlopen("hwinfo/libhwinfo_gpu.so", _flags);
    void* mb  = dlopen("hwinfo/libhwinfo_mainboard.so", _flags);
    void* net = dlopen("hwinfo/libhwinfo_network.so", _flags);
    void* bat = dlopen("hwinfo/libhwinfo_battery.so", _flags);
#endif

#include "hwinfo/battery.h"
#include "hwinfo/cpu.h"
#include "hwinfo/disk.h"
#include "hwinfo/gpu.h"
#include "hwinfo/mainboard.h"
#include "hwinfo/network.h"
#include "hwinfo/os.h"
#include "hwinfo/ram.h"

#ifdef _WIN32
    #include "hwinfo/utils/wmi_wrapper.h"
#endif
