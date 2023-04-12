#pragma once

#include <iostream>
#include "vec2.h"
#include "color.h"

namespace BoxRenderer
{

class Box
{
public:

    Box(const Vec2& position, const Color& color, const Vec2& size) :
        mPosition(position), mColor(color), mSize(size)
    {}

    Vec2& position()
    {
        return mPosition;
    }

    const Vec2& position() const
    {
        return mPosition;
    }

    Color& color()
    {
        return mColor;
    }

    const Color& color() const
    {
        return mColor;
    }

    Vec2 bottomLeft() const
    {
        return { mSize.x / -2.0f, mSize.y / -2.0f };
    }

    Vec2 bottomRight() const
    {
        return { mSize.x / 2.0f, mSize.y / -2.0f };
    }

    Vec2 upperLeft() const
    {
        return { mSize.x / -2.0f, mSize.y / 2.0f };
    }

    Vec2 upperRight() const
    {
        return { mSize.x / 2.0f, mSize.y / 2.0f };
    }

private:
    Vec2 mPosition;
    Color mColor;
    Vec2 mSize;
};

std::ostream& operator<<(std::ostream& os, const BoxRenderer::Box& box);


} // namespace BoxRenderer