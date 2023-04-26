
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

    void setupVAO(DMesh& dMesh) const;

    void drawCall(const DMesh& dMesh) const;
};


} // namespace BoxRenderer