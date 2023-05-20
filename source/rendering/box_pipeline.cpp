

#include "box_pipeline.h"
#include "shaders_core.h"
#include <glad/glad.h>

namespace BoxRenderer{

ColorBoxShaderProgram::ColorBoxShaderProgram()
{
    const std::string vertexShaderCode = R"(
        #version 460 core

        in vec3 position;
        uniform mat4 modelTransform;

        void main()
        {
            gl_Position = modelTransform * vec4(position, 1.0f);
        }
    )";

    const std::string fragmentShaderCode = R"(
        #version 460

        uniform vec3 color;
        out vec4 outColor;

        void main()                         
        {
            outColor = vec4(color, 1.0f);
        }
    )";

    shaderProgram = createShaderProgramFromCode({
        {GL_VERTEX_SHADER, vertexShaderCode.c_str()},
        {GL_FRAGMENT_SHADER, fragmentShaderCode.c_str()}
    });
}

} // namespace BoxRenderer