
#include "shader_program_loader.h"
#include <string>

namespace BoxRenderer
{

ShaderProgram createColorShaderProgram()
{
    const std::string name = "Color";

    DVertex dvertex{{"position", VertexDataType::Vec3}};

    UniformFieldsDescription uniformFields;
    uniformFields.emplace_back("color", BoxRenderer::UniformDataType::Vec3);

    const std::string vertexShader = R"(
        #version 460 core

        in vec3 position;
        uniform mat4 modelTransform;

        void main()
        {
            gl_Position = modelTransform * vec4(position, 1.0f);
        }
        )";
    
    const std::string fragmentShader = R"(
        #version 460

        uniform vec3 color;
        out vec4 outColor;

        void main()                         
        {
            outColor = vec4(color, 1.0f);
        }
        )";
    
    return {name, dvertex, uniformFields, vertexShader, fragmentShader};
}

} // namespace BoxRenderer