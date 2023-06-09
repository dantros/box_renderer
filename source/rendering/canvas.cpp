
#include "canvas.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "performance_monitor.h"
#include "uniforms_description.h"
#include "uniform_values.h"
#include "shader_program_loader.h"
#include "mesh.h"
#include "dmesh.h"
#include "shaders_core.h"
#include "shader_program_container.h"

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
    mWorld()
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
    const BoxId newId = mWorld.boxes.size();
    mWorld.boxes.push_back(box);
    return newId;
}

Mesh generateMesh(const Box& box)
{
    Mesh mesh;

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

void setupVAO(DMesh& dMesh, GPUID shaderProgram)
{
    // Binding VAO to setup
    glBindVertexArray(dMesh.vao);

    // Binding buffers to the current VAO
    glBindBuffer(GL_ARRAY_BUFFER, dMesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dMesh.ebo);

    unsigned int offset = 0;

    for (auto& vertexDataAttribute : dMesh.dvertex)
    {
        const auto& attributeName = vertexDataAttribute.attributeName.c_str();
        const auto attributeLocation = glGetAttribLocation(shaderProgram, attributeName);

        const unsigned int numberOfFloats = vertexDataAttribute.arity();

        glVertexAttribPointer(attributeLocation, numberOfFloats, GL_FLOAT, GL_FALSE, numberOfFloats * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(attributeLocation);

        offset += numberOfFloats;
    }

    // Unbinding current VAO
    glBindVertexArray(0);
}

void Canvas::drawScene(::Alice::Controller& controller, std::function<void(float deltaTime)> updateFunction)
{
    glfwSetWindowUserPointer(mWindow->glfwWindow, &controller);

    // Connecting the callback function 'key_callback' to handle keyboard events
    glfwSetKeyCallback(mWindow->glfwWindow, keyCallback);

    // Prepare GPU ---

    // Creating our shader programs
    mWorld.shaderPrograms.emplace_back(createColorShaderProgram());

    ShaderProgramId shaderProgramId = 0;

    //TODO split static vs dynamic content
    std::vector<DMesh>  dContent;
    dContent.reserve(mWorld.boxes.size());
    
    for (auto& box : mWorld.boxes)
    {
        auto& pipeline = mWorld.shaderPrograms.at(shaderProgramId);

        DVertex dvertex{{"position", VertexDataType::Vec3}};

        Mesh mesh = generateMesh(box);
        mesh.dvertex = dvertex;

        DMesh dMesh;
        dMesh.dvertex = dvertex;
        dMesh.initBuffers();
        setupVAO(dMesh, pipeline.shaderProgram);
        dMesh.fillBuffers(mesh, GL_STATIC_DRAW);

        dContent.push_back(dMesh);
    }

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
        auto boxIt = mWorld.boxes.begin();

        for (auto& dMesh : dContent)
        {
            auto& pipeline = mWorld.shaderPrograms.at(shaderProgramId);
            glUseProgram(pipeline.shaderProgram);

            auto& color = boxIt->color();
            auto& position = boxIt->position();
            boxIt++;

            UniformValues uniformValues;

            uniformValues.push_back(std::make_shared<Vec3UniformValue>(pipeline.shaderProgram, "color", glm::vec3(color.r, color.g, color.b)));

            glm::mat4 modelTransform(1.0f);
            modelTransform = glm::translate(modelTransform, glm::vec3(position.x, position.y, 0.0f));
            uniformValues.push_back(std::make_shared<Mat4UniformValue>(pipeline.shaderProgram, "modelTransform", modelTransform));

            setupUniforms(uniformValues);

            dMesh.drawCall();
        }
    
        // Once the drawing is rendered, buffers are swap so an uncomplete drawing is never seen.
        glfwSwapBuffers(mWindow->glfwWindow);
    }
}

void Canvas::clear()
{
    mWorld.boxes.clear();

    // Clearing the screen
    glClear(GL_COLOR_BUFFER_BIT);
}

Box& Canvas::getBox(BoxId boxId)
{
    return mWorld.boxes.at(boxId);
}

Box const& Canvas::getBox(BoxId boxId) const
{
    return mWorld.boxes.at(boxId);
}

std::vector<Box>& Canvas::getCanvasContent()
{
    return mWorld.boxes;
}

std::vector<Box> const& Canvas::getCanvasContent() const
{
    return mWorld.boxes;
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