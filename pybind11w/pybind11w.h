#include <pybind11/pybind11.h>
#include <pybind11/native_enum.h>
#include <stdexcept>
#include <sstream>

#include <magic_enum/magic_enum.hpp>

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

namespace pybind11 {

    template <typename T>
    object str_enum(handle m, const char* name) {

        // Construct "enum.Enum" base class
        native_enum<T> _enum_obj = {m, name, "enum.Enum"};
        
        // Register Enum Members
        for (const auto& [value, name_view] : magic_enum::enum_entries<T>()) {
            _enum_obj.value(name_view.data(), value);
        }
        _enum_obj.finalize();

        // Retrieve the generated Python Enum object
        object _cls = m.attr(name);

        // Register Member Values
        for (handle member : _cls.attr("__members__").attr("values")()) {
            member.attr("_value_") = to_string(member.cast<T>());
        }

        return _cls;
    }

}

