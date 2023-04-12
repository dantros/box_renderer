
function(MakeThirdPartyDemo TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER samples)
    target_link_libraries(${TARGETNAME} PRIVATE ${THIRD_PARTY_LIBRARIES})
    target_include_directories(${TARGETNAME} PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES})
endfunction(MakeThirdPartyDemo)

MakeThirdPartyDemo(test_opengl test_opengl.cpp)
MakeThirdPartyDemo(test_cpp test_cpp.cpp)

function(MakeBoxRendererDemo TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER samples)
    target_link_libraries(${TARGETNAME} PRIVATE ${BOX_RENDERER_LIBRARY})
    target_include_directories(${TARGETNAME} PRIVATE ${BOX_RENDERER_INCLUDE_DIRECTORIES})
endfunction(MakeBoxRendererDemo)

MakeBoxRendererDemo(hello_box_renderer hello_box_renderer.cpp)