#pragma once

#include <string>
#include <vector>

namespace BoxRenderer
{

enum class UniformDataType{Float, Vec2, Vec3, Vec4, Mat4};

struct UniformField
{
    std::string name;
    UniformDataType type;
};

using UniformFieldsDescription = std::vector<UniformField>;

} // namespace BoxRenderer