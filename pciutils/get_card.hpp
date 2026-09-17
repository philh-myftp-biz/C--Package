#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

extern "C" {
    #include "pci.h" 
}

namespace pcieutils {

    struct CardDetails {
        int slot_index = 0;
        std::string topology_address; // e.g., "01:00.0"
        std::string hardware_name = ""; // Clear text name resolved from pci.ids
        uint16_t vendor_id = 0;
        uint16_t device_id = 0;
        uint16_t class_code = 0;
    };

    inline CardDetails get_card(const int& index) {

        struct pci_access *pacc = pci_alloc();
        if (!pacc) return CardDetails{}; 
        
        pci_init(pacc);
        pci_scan_bus(pacc);

        CardDetails card = CardDetails{};

        for (struct pci_dev *dev = pacc->devices; dev; dev = dev->next) {

            pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_CLASS);

            // Match the Bus number, and prioritize Function 0 (the primary device on the card)
            if (dev->bus == index && dev->func == 0) {

                card.slot_index = index;
                card.vendor_id = dev->vendor_id;
                card.device_id = dev->device_id;
                card.class_code = dev->device_class;

                // Format the standard BDF hex string layout
                std::stringstream ss;
                ss << std::hex << std::setw(2) << std::setfill('0') << (int)dev->bus << ":"
                << std::setw(2) << std::setfill('0') << (int)dev->dev << "."
                << (int)dev->func;
                card.topology_address = ss.str();

                char namebuf[256] = {0};

                char* lookup_result = pci_lookup_name(
                    pacc, 
                    namebuf, 
                    sizeof(namebuf), 
                    PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE, 
                    dev->vendor_id, 
                    dev->device_id
                );

                if (lookup_result) card.hardware_name = lookup_result;

                break;
            }
        }

        pci_cleanup(pacc);
        return card; 
    }


}

