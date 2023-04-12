
#include "canvas.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "box_pipeline.h"
#include "performance_monitor.h"

namespace BoxRenderer
{

// Wrapper class forward declared in the .h to avoid including GLFW dependecies in the header file.
struct Canvas::Window
{
    GLFWwindow* glfwWindow;
};

Canvas::Canvas() : mWidth(DEFAULT_WIDTH), mHeight(DEFAULT_HEIGHT), mTitle(DEFAULT_TITLE) {};

Canvas::Canvas(unsigned int width, unsigned int height, std::string const& title) :
    mWidth(width),
    mHeight(height),
    mTitle(title),
    mContent{}
{
    // Initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Creating a glfw window    
    GLFWwindow* glfwWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);

    if (glfwWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }

    mWindow = std::make_unique<Window>(glfwWindow);
    //mWindow->glfwWindow = glfwWindow;

    glfwMakeContextCurrent(mWindow->glfwWindow);

    // Loading all OpenGL function pointers with glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw;
    }
}

void Canvas::setSize(unsigned int width, unsigned int height)
{
    mWidth = width;
    mHeight = height;
}

void Canvas::setBackgroundColor(Color const& color)
{
    mClearColor = color;
}

BoxId Canvas::addBox(const Box& box)
{
    const BoxId newId = mContent.size();
    mContent.push_back(box);
    return newId;
}

Mesh generateMesh(const Box& box)
{
    Mesh mesh(3);

    mesh.vertices.reserve(12);

    auto addVertex = [&mesh](Vec2 vertex)
    {
        mesh.vertices.push_back(vertex.x);
        mesh.vertices.push_back(vertex.y);
        mesh.vertices.push_back(0.0f);
    };
    
    addVertex(box.bottomLeft());  // vertex 0
    addVertex(box.bottomRight()); // vertex 1
    addVertex(box.upperRight());  // vertex 2
    addVertex(box.upperLeft());   // vertex 3

    mesh.indices.reserve(6);

    // Bottom Right Triangle
    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);

    // Upper Left Triangle
    mesh.indices.push_back(2);
    mesh.indices.push_back(3);
    mesh.indices.push_back(0);

    return mesh;
}

void Canvas::drawScene()
{
    auto dummyFunction = [](float dt){return;};
    ::Alice::Controller controller;
    drawScene(controller, dummyFunction);
}

// This function will be executed whenever a key is pressed or released
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    auto myUserPointer = glfwGetWindowUserPointer(window);
    ::Alice::Controller* controller = static_cast<::Alice::Controller*>(myUserPointer);

    ::Alice::Key aliceKey = ::Alice::KeyboardImplementation::toAliceKeyCode(key);
    controller->press(aliceKey);
}

void Canvas::drawScene(::Alice::Controller& controller, std::function<void(float deltaTime)> updateFunction)
{
    glfwSetWindowUserPointer(mWindow->glfwWindow, &controller);

    // Connecting the callback function 'key_callback' to handle keyboard events
    glfwSetKeyCallback(mWindow->glfwWindow, keyCallback);

    // Prepare GPU ---

    // Creating our shader program and telling OpenGL to use it
    ColorBoxShaderProgram pipeline;

    //TODO split static vs dynamic content
    std::vector<DMesh>  dContent;
    dContent.reserve(mContent.size());
    
    for (auto& box : mContent)
    {
        Mesh mesh = generateMesh(box);
        DMesh dMesh = toDevice(pipeline, mesh);
        dContent.push_back(dMesh);
    }
    
    glUseProgram(pipeline.shaderProgram);

    // Setting up the clear screen color
    glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

    // ---

    PerformanceMonitor performanceMonitor(glfwGetTime(), 0.5f);

    // Application loop
    while (!glfwWindowShouldClose(mWindow->glfwWindow))
    {
        // Using GLFW to check and process input events
        // internally, it stores all input events in the controller
        glfwPollEvents();

        controller.processInputs();

        performanceMonitor.update(glfwGetTime());
        float deltaTime = performanceMonitor.getMS();
        
        updateFunction(deltaTime);

        // Clearing the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: this should be way prettier. use an extended pair for mContent
        auto boxIt = mContent.begin();

        for (auto& dMesh : dContent)
        {
            auto& color = boxIt->color();
            auto& position = boxIt->position();
            boxIt++;
            glUniform3f(glGetUniformLocation(pipeline.shaderProgram, "color"), color.r, color.g, color.b);

            glm::mat4 modelTransform(1.0f);
            modelTransform = glm::translate(modelTransform, glm::vec3(position.x, position.y, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(pipeline.shaderProgram, "modelTransform"), 1, GL_FALSE, &modelTransform[0][0]);
            pipeline.drawCall(dMesh);
        }
    
        // Once the drawing is rendered, buffers are swap so an uncomplete drawing is never seen.
        glfwSwapBuffers(mWindow->glfwWindow);
    }
}

void Canvas::clear()
{
    mContent.clear();

    // Clearing the screen
    glClear(GL_COLOR_BUFFER_BIT);
}

Box& Canvas::getBox(BoxId boxId)
{
    return mContent.at(boxId);
}

Box const& Canvas::getBox(BoxId boxId) const
{
    return mContent.at(boxId);
}

std::vector<Box>& Canvas::getCanvasContent()
{
    return mContent;
}

std::vector<Box> const& Canvas::getCanvasContent() const
{
    return mContent;
}

Canvas::~Canvas()
{
    // freeing GPU memorygpuShape.clear();

    glfwTerminate();
}

void Canvas::close()
{
    glfwSetWindowShouldClose(mWindow->glfwWindow, true);
}

} // namespace BoxRenderer