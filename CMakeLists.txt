cmake_minimum_required(VERSION 3.10)

project(sdl-imgui)

find_library(SDL SDL2 PATHS ${CMAKE_SOURCE_DIR}/lib)
#find_library(SDLmain SDL2main PATHS ${CMAKE_SOURCE_DIR}/lib)

find_package(OpenGL)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/SDL2.framework/Versions/Current/Headers
    )

# your sources
set(sources
    main.cpp
    imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui_impl_opengl2.cpp
    imgui/imgui_impl_opengl2.h
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_sdl.h
)

# for filesystem functionality from C++17
set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME} ${sources})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL} ${OPENGL_gl_LIBRARY})
