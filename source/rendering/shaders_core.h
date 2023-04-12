#pragma once

#include <iostream>
#include "mesh.h"
#include "dmesh.h"

namespace BoxRenderer{

struct ShaderCode
{
    GPUID const type;
    std::string const sourceCode;
};

GPUID createShaderProgramFromCode(std::initializer_list<ShaderCode> shaderCodes);

} // namespace BoxRenderer