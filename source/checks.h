#pragma once

#include <string>
#include <iostream>

inline void debugCheck(const bool supposedValidCondition, const std::string& errorMessage = "")
{
    if (!supposedValidCondition)
    {
        std::cerr << errorMessage << std::endl;
        throw;
    }
}