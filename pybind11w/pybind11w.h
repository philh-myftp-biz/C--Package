#include <pybind11/pybind11.h>
#include <stdexcept>
#include <sstream>

#ifdef _WIN32
    #include <pybind11w/win.h>
#else
    #include <pybind11w/nix.h>
#endif

inline auto verbose_translator = [](std::exception_ptr p) {
    if (!p) return;
    
    std::stringstream ss;
    ss << "\n--- C++ Native Stack Trace ---";

    try {
        std::rethrow_exception(p);
    } catch (const std::exception& e) {
        ss << e.what() << "\n";
    } catch (...) {
        ss << "Unknown Exception Type\n";
    }

    capture_stack_trace(ss);
    PyErr_SetString(PyExc_Exception, ss.str().c_str());
};

struct PybindVerboseRegistration {
    PybindVerboseRegistration() {
        pybind11::register_exception_translator(verbose_translator);
        #ifdef _WIN32
            AddVectoredExceptionHandler(1, NativeCrashVectoredHandler);
        #endif
    }
};

static PybindVerboseRegistration g_auto_verbose_registration;

