
#include "shader_program.h"
#include <glad/glad.h>

namespace BoxRenderer
{

ShaderProgram::ShaderProgram(
    const std::string& name_, // TODO maybe I do not need this!, check material container
    const DVertex& dvertex_,
    const UniformFieldsDescription& uniforms_,
    const std::string& vertexShaderCode,
    const std::string& fragmentShaderCode
):
    name(name_),
    dvertex(dvertex_),
    uniforms(uniforms_),
    shaderProgram(
        createShaderProgramFromCode({
            {GL_VERTEX_SHADER, vertexShaderCode.c_str()},
            {GL_FRAGMENT_SHADER, fragmentShaderCode.c_str()}
        })
    )
{
}

} // namespace BoxRenderer