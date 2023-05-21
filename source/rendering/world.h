#pragma once

#include <vector>
#include "box.h"
#include "shader_program_container.h"

namespace BoxRenderer
{

struct World
{
    std::vector<Box> boxes;
    ShaderProgramContainer shaderPrograms;
};

} // namespace BoxRenderer