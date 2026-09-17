#pragma once

#ifdef _WIN32

    #pragma comment(lib, __FILE__ "\\..\\pci.lib")

    #pragma comment(lib, "cfgmgr32.lib")
    #pragma comment(lib, "advapi32.lib")

#endif

#include "pciutils/get_card.hpp"

