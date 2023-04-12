#include "color.h"

namespace BoxRenderer
{

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Color& color)
{
    return os << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
}

} // namespace BoxRenderer