#include "vec2.h"

namespace BoxRenderer
{

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Vec2& vertex)
{
    return os << "(" << vertex.x << ", " << vertex.y << ")";
}

} // namespace BoxRenderer