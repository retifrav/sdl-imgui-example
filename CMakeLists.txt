cmake_minimum_required(VERSION 3.10)

project(sdl-imgui)

# for filesystem functionality from C++17
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

if (WIN32)
    set(WHERE-IS-SDL "e:/tools/sdl/lib/x64")
    set(WHERE-IS-SDL-HEADERS "e:/tools/sdl/include")
endif()

if (APPLE)
    set(WHERE-IS-SDL "${CMAKE_SOURCE_DIR}/lib")
    set(WHERE-IS-SDL-HEADERS "${CMAKE_SOURCE_DIR}/lib/SDL2.framework/Versions/Current/Headers")
endif()

if(UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

#message(${WHERE-IS-SDL})
#message(${WHERE-IS-SDL-HEADERS})

if (WIN32 OR APPLE)
    find_library(SDL SDL2 PATHS ${WHERE-IS-SDL})
    if (WIN32)
        find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    endif()

    include_directories(
        "${WHERE-IS-SDL-HEADERS}"
    )
endif()

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

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL} ${SDLmain} ${OPENGL_gl_LIBRARY})
else()
    add_executable(${CMAKE_PROJECT_NAME} ${sources})
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL} ${OPENGL_gl_LIBRARY})
    endif()
    if (UNIX AND NOT APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY})
    endif()
endif()

# copy font file to the build directory
add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/verdana.ttf
                ${CMAKE_CURRENT_BINARY_DIR}/verdana.ttf
                )
