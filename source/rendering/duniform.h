#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "shaders_core.h"

namespace BoxRenderer
{

enum class UniformDataType{Float, Vec2, Vec3, Vec4, Mat4};

struct UniformField
{
    std::string name;
    UniformDataType type;
};

using UniformFieldsDescription = std::vector<UniformField>;


struct UniformValueBase
{
    GPUID uniformLocation;

    UniformValueBase(GPUID shaderProgram, const std::string& fieldName);

    virtual void toGPU(){};
};

struct FloatUniformValue : public UniformValueBase
{
    using type = float;
    float value;

    FloatUniformValue(GPUID shaderProgram, const std::string& fieldName, float value_);

    virtual void toGPU() override;
};

struct Vec2UniformValue  : public UniformValueBase
{
    using type = glm::vec2;
    glm::vec2 value;

    Vec2UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec2& value_);

    virtual void toGPU() override;
};

struct Vec3UniformValue  : public UniformValueBase
{
    using type = glm::vec3;
    glm::vec3 value;

    Vec3UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec3& value_);

    virtual void toGPU() override;
};

struct Vec4UniformValue  : public UniformValueBase
{
    using type = glm::vec4;
    glm::vec4 value;

    Vec4UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::vec4& value_);

    virtual void toGPU() override;
};

struct Mat4UniformValue  : public UniformValueBase
{
    using type = glm::mat4;
    glm::mat4 value;

    Mat4UniformValue(GPUID shaderProgram, const std::string& fieldName, const glm::mat4& value_);

    virtual void toGPU() override;
};

using UniformValues = std::vector<std::shared_ptr<UniformValueBase>>;

void setupUniforms(const UniformValues& values);

} // namespace BoxRenderer