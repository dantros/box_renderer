

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

void ColorBoxShaderProgram::setupVAO(DMesh& dMesh) const
{
    // Binding VAO to setup
    glBindVertexArray(dMesh.vao);

    // Binding buffers to the current VAO
    glBindBuffer(GL_ARRAY_BUFFER, dMesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dMesh.ebo);

    // position attribute
    auto position = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(position);

    // Unbinding current VAO
    glBindVertexArray(0);
}

void ColorBoxShaderProgram::drawCall(const DMesh& dMesh) const
{
    // Binding the VAO and executing the draw call
    glBindVertexArray(dMesh.vao);
    glDrawElements(GL_TRIANGLES, dMesh.size, GL_UNSIGNED_INT, nullptr);

    // Unbind the current VAO
    glBindVertexArray(0);
}

} // namespace BoxRenderer