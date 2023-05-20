#pragma once

#include <string>
#include <vector>

namespace BoxRenderer
{

enum class VertexDataType{Float, Vec2, Vec3, Vec4, Tex2, Tex3, iTex2, iTex3};

struct VertexDataAttribute
{
    std::string attributeName;
    VertexDataType vertexDataType;

    /* Number of floats to represent this vertex data attribute */
    int arity();
};

using DVertex = std::vector<VertexDataAttribute>;

} // namespace BoxRenderer