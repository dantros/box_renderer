
#include "uniform_values.h"
#include <glad/glad.h>

namespace BoxRenderer
{

UniformValueBase::UniformValueBase(GPUID shaderProgram, const std::string& fieldName) :
    uniformLocation(glGetUniformLocation(shaderProgram, fieldName.c_str()))
{
}

FloatUniformValue::FloatUniformValue(GPUID shaderProgram, const std::string& fieldName, float value_) :
    UniformValueBase(shaderProgram, fieldName),
    value(value_)
{}

void FloatUniformValue::toGPU()
{
    glUniform1f(uniformLocation, value);
}

Vec2UniformValue::Vec2UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec2& value_) :
    UniformValueBase(shaderProgram, fieldName),
    value(value_)
{}

void Vec2UniformValue::toGPU()
{
    glUniform2f(uniformLocation, value.x, value.y);
}

Vec3UniformValue::Vec3UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec3& value_) :
    UniformValueBase(shaderProgram, fieldName),
    value(value_)
{}

void Vec3UniformValue::toGPU()
{
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

Vec4UniformValue::Vec4UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec4& value_) :
    UniformValueBase(shaderProgram, fieldName),
    value(value_)
{}

void Vec4UniformValue::toGPU()
{
    glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

Mat4UniformValue::Mat4UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::mat4& value_) :
    UniformValueBase(shaderProgram, fieldName),
    value(value_)
{}

void Mat4UniformValue::toGPU()
{
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void setupUniforms(const UniformValues& values)
{
    for (auto& valuePtr : values)
    {
        if (valuePtr == nullptr)
            throw;
            
        auto& uniformValue = *valuePtr;
        uniformValue.toGPU();
    }
}

} // namespace BoxRenderer