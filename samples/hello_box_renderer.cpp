
#include <iostream>
#include <string>
#include <vector>
#include <ciso646>
#include <box_renderer.h>

int main()
{
    // settings
    constexpr unsigned int SCR_WIDTH = 600;
    constexpr unsigned int SCR_HEIGHT = 600;

    BoxRenderer::Canvas canvas(SCR_WIDTH, SCR_HEIGHT, "Hello Box Renderer!");

    canvas.setBackgroundColor(BoxRenderer::Color::White());
    
    BoxRenderer::BoxId boxId1 = canvas.addBox({ {0.0f, 0.0f}, BoxRenderer::Color::Gray(), { 2.0f, 1.5f } }); 
    BoxRenderer::BoxId boxId2 = canvas.addBox({ {0.0f, 0.75f}, BoxRenderer::Color::Blue(), { 0.5f, 0.5f } });
    BoxRenderer::BoxId boxId3 = canvas.addBox({ {-0.5f, -0.5f}, BoxRenderer::Color::Red(), { 0.75f, 0.75f } });
    BoxRenderer::BoxId boxId4 = canvas.addBox({ {0.0f, 0.0f}, BoxRenderer::Color::Yellow(), { 1.0f, 1.0f } });

    bool movingRight = true;
    float speed = 0.0001;

    auto update = [&](float dt)
    {
        BoxRenderer::Box& box = canvas.getBox(boxId2);

        if (movingRight)
            box.position().x += speed * dt;
        else
            box.position().x -= speed * dt;

        if (box.position().x > 0.5)
            movingRight = false;
        else if (box.position().x < -0.5)
            movingRight = true;
    };

    Alice::Controller controller;
    controller.onKeyPress(Alice::Key::W, [&]() { speed *= 2.0f; });
    controller.onKeyPress(Alice::Key::S, [&]() { speed /= 2.0f; });
    controller.onKeyPress(Alice::Key::ESCAPE, [&]() { canvas.close(); });

    canvas.drawScene(controller, update); //runScene
    
    return 0;
}