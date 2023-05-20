
add_library(box_renderer STATIC
	rendering/vec2.h
    rendering/vec2.cpp
    rendering/color.h
    rendering/color.cpp
    rendering/box.h
    rendering/box.cpp
    rendering/mesh.h
    rendering/mesh.cpp
    rendering/dvertex.h
    rendering/dvertex.cpp
    rendering/duniform.h
    rendering/duniform.cpp
    rendering/dmesh.h
    rendering/dmesh.cpp
    rendering/canvas.h
    rendering/canvas.cpp
    rendering/performance_monitor.h
    rendering/performance_monitor.cpp
    rendering/shaders_core.h
    rendering/shaders_core.cpp
    rendering/shader_program.h
    rendering/shader_program.cpp
    rendering/shader_program_loader.h
    rendering/shader_program_loader.cpp
    inputs/keyboard.h
    inputs/keyboard.cpp
    inputs/controller.h
    inputs/controller.cpp)

set_property(TARGET box_renderer PROPERTY CXX_STANDARD 20)
target_link_libraries(box_renderer PRIVATE ${THIRD_PARTY_LIBRARIES})
target_include_directories(box_renderer PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES})
