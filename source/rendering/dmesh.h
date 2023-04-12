#pragma once

#include <iostream>
#include "mesh.h"

namespace BoxRenderer{

/* We will use 32 bits data, so floats and integers have 4 bytes.
 * 1 byte = 8 bits
 */
constexpr unsigned int SIZE_IN_BYTES = 4;

using GPUID = unsigned int;

struct DMesh
{
    GPUID vao, vbo, ebo, texture;
    std::size_t size;

    /*
    Convenience function for initialization of OpenGL buffers.
    It returns itself to enable the convenience call:
    gpuShape = GPUShape().initBuffers()

    Note: this is not the default constructor as you may want
    to use some already existing buffers.
    */
    void initBuffers();

    void fillBuffers(const Mesh& mesh, GPUID usage);

    /* Freeing GPU memory */
    void clear();
};

std::ostream& operator<<(std::ostream& os, const DMesh& dMesh);

} // namespace BoxRenderer