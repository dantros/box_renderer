#pragma once

#include <iostream>

namespace BoxRenderer
{

using GPUID = unsigned int;

struct ShaderCode
{
    GPUID const type;
    std::string const sourceCode;
};

GPUID createShaderProgramFromCode(std::initializer_list<ShaderCode> shaderCodes);

} // namespace BoxRenderer