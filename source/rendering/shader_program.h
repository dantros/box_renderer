#pragma once

#include <string>
#include "dvertex.h"
#include "uniforms_description.h"
#include "shaders_core.h"

namespace BoxRenderer
{

struct ShaderProgram
{
    ShaderProgram(
        const std::string& name, // TODO maybe I do not need this!, check material container
        const DVertex& dvertex,
        const UniformFieldsDescription& uniformFields,
        const std::string& vertexShaderCode,
        const std::string& fragmentShaderCode
    );

    std::string name;
    DVertex dvertex;
    UniformFieldsDescription uniforms;
    GPUID shaderProgram;
};

} // namespace BoxRenderer