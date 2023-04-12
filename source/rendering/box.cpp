#include "box.h"

namespace BoxRenderer
{

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Box& box)
{
    return os << "[color=" << box.color() << "; bottomLeft=" << box.bottomLeft() << "; upperRight=" << box.upperRight() << "]";
}

} // namespace BoxRenderer