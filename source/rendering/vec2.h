#pragma once

#include <iostream>

namespace BoxRenderer
{

struct Vec2
{
    float x, y;
};

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Vec2& vertex);

} // namespace BoxRenderer