#pragma once

#include <vector>
#include "../inputs/controller.h"
#include "box.h"

namespace BoxRenderer
{

using BoxId = std::size_t;

class Canvas
{
public:
    constexpr static unsigned int DEFAULT_WIDTH = 600;
    constexpr static unsigned int DEFAULT_HEIGHT = 600;
    inline const static std::string DEFAULT_TITLE = "box_renderer";
    inline const static Color DEFAULT_CLEAR_COLOR = Color::Black();

    Canvas();

    Canvas(unsigned int width, unsigned int height, std::string const& title);

    ~Canvas();

    void setSize(unsigned int width, unsigned int height);

    void setBackgroundColor(Color const& color);

    BoxId addBox(const Box& box);

    void drawScene();

    void drawScene(::Alice::Controller& controller, std::function<void(float deltaTime)> updateFunction);

    void clear();

    Box& getBox(BoxId boxId);

    Box const& getBox(BoxId boxId) const;

    std::vector<Box>& getCanvasContent();

    std::vector<Box> const& getCanvasContent() const;

    void close();

private:
    unsigned int mWidth, mHeight;
    std::string mTitle;
    Color mClearColor;
    std::vector<Box> mContent;

    // Forward declaration to interface with third party libs
    struct Window;
    std::unique_ptr<Window> mWindow;
};

} // namespace BoxRenderer