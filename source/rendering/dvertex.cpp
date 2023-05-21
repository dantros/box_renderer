
#include "dvertex.h"

namespace BoxRenderer
{

unsigned int VertexDataAttribute::arity() const
{
    switch (vertexDataType)
    {
    case VertexDataType::Float:
        return 1;
    case VertexDataType::Vec2:
        return 2;
    case VertexDataType::Vec3:
        return 3;
    case VertexDataType::Vec4:
        return 4;
    case VertexDataType::Tex2:
        return 2;
    case VertexDataType::Tex3:
        return 3;
    /*case VertexDataType::iTex2:
        return 2;
    case VertexDataType::iTex3:
        return 3;*/
    default:
        throw;
        return 0;
    }
}

unsigned int arity(const DVertex &dvertex)
{
    unsigned int totalArity = 0;

    for (auto& vertexAttribute : dvertex)
        totalArity += vertexAttribute.arity();

    return totalArity;
}

} // namespace BoxRenderer