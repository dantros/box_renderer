#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "dvertex.h"

namespace BoxRenderer
{

using Coord = float;
using Index = unsigned int;

using Vertices = std::vector<Coord>;
using Indices = std::vector<Index>;

struct Mesh
{
    Vertices vertices;
    Indices indices;
    DVertex dvertex;
};

Mesh join(const Mesh& rhs, const Mesh& lhs);

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Vertices& vertices);

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Indices& indices);

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Mesh& shape);

} // BoxRenderer
