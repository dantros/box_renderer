#pragma once


#include <vector>
#include "shader_program.h"

namespace BoxRenderer
{

using ShaderProgramContainer = std::vector<ShaderProgram>;
using ShaderProgramId  = std::size_t;

} // namespace BoxRenderer