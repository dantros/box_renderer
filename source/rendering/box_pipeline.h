
#pragma once

#include <iostream>
#include "mesh.h"
#include "dmesh.h"

namespace BoxRenderer
{

struct ColorBoxShaderProgram
{
    GPUID shaderProgram;

    ColorBoxShaderProgram();
};


} // namespace BoxRenderer