#pragma once

// 1. Tell Visual Studio to link your custom static library relative to this header file
#pragma comment(lib, __FILE__ "\\..\\pci.lib")

// 2. Force link the missing Windows OS modules needed by pciutils 
#pragma comment(lib, "cfgmgr32.lib")
#pragma comment(lib, "advapi32.lib")

// 3. Include the clean namespaced implementation file
#include "pciutils/get_card.hpp"
