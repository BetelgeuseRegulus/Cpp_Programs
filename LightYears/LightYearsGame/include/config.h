#pragma once
#include <string>

std::string GetResoureDir()
{
#ifdef NOBUG // release build
    return "assets/";
#else
    return "E:/c_plus_plus/C++/cpp_lightYear/LightYearsGame/assets/";
#endif
}
