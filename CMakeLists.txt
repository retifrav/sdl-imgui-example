cmake_minimum_required(VERSION 3.22)

project(sdl-imgui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# your sources
set(sources
    main.cpp
    # Dear ImGui should also be resolved with a package manager instead of vendoring
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
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_opengl3.h
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_sdl.h
)

set(resource_files verdana.ttf)

if(WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32)
else()
    add_executable(${CMAKE_PROJECT_NAME})
endif()

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${sources}
)

# seems to be redundant, as CMake 3.22 is explicitly required
#cmake_policy(PUSH)
#if(POLICY CMP0072)
#    cmake_policy(SET CMP0072 NEW) # prefer GLVND
#endif()
find_package(OpenGL REQUIRED)
#cmake_policy(POP)

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        glad::glad
        SDL2::SDL2
        SDL2::SDL2main
        ${OPENGL_gl_LIBRARY}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
            ${CMAKE_DL_LIBS}
    )
endif()

# --- installation

include(GNUInstallDirs)

install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_PROJECT_NAME}
)
install(FILES
    ${resource_files}
    DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_PROJECT_NAME}
)
