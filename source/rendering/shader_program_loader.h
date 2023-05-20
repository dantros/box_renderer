#pragma once

#include "shader_program.h"

namespace BoxRenderer
{

/* \brief This is meant to generate on runtime all the materials availables for the renderer.
 * This is a substitue code, in the future this will gather the information from external files.
 * */
ShaderProgram createColorShaderProgram();

//Material createBitTextureMaterial();

//Material createTextMaterial();

} // namespace BoxRenderer