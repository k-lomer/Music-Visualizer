#pragma once

#include <string>

namespace version {
    const int major = 0;
    const int minor = 1;
    const int revision = 0;

    inline std::string get_version()
    {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
    }
} // End namespace version.