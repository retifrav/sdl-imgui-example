// Based on https://github.com/ocornut/imgui/blob/master/examples/example_sdl_opengl2/main.cpp

// don't listen to MS complains, we want cross-platform code
#define _CRT_SECURE_NO_DEPRECATE

// C++
//#include <filesystem>
#include <vector>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// Dear ImGui
#include "imgui-style.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"

#include "functions.h"

int main(int argc, char *argv[])
{
    std::cout << "[" << currentTime(std::chrono::system_clock::now()) << "] " << "Start\n- - -\n\n";

    // std::vector<std::string> files;
    // auto currentPath = std::filesystem::current_path();
    // //std::cout << currentPath.string();
    // for (const auto &entry : std::filesystem::directory_iterator(currentPath))
    // {
    //     files.push_back(entry.path().filename().string().data());
    //     //std::cout << entry.path().filename() << std::endl;
    // }

    // initiate SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_version compiled;
    SDL_VERSION(&compiled);
    std::ostringstream compiledVal;
    compiledVal << "Compiled with "
                << std::to_string(compiled.major)
                << "." << std::to_string(compiled.minor)
                << "." << std::to_string(compiled.patch);
    //std::cout << compiledVal.str() << std::endl;

    SDL_version linked;
    SDL_GetVersion(&linked);
    std::ostringstream linkedVal;
    linkedVal << "Linked with "
              << std::to_string(linked.major)
              << "." << std::to_string(linked.minor)
              << "." << std::to_string(linked.patch);
    //std::cout << linkedVal.str() << std::endl;

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_SetWindowMinimumSize(window, 500, 300);
    
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    // enable VSync
    SDL_GL_SetSwapInterval(1);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("verdana.ttf", 18.0f, NULL, NULL);

    // setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    setImGuiStyle();

    // setup platform/renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    bool show_demo_window = false;
    bool show_another_window = false;
    // colors are set in RGBA, but as float
    ImVec4 background = ImVec4(35/255.0f, 35/255.0f, 35/255.0f, 1.00f);

    bool loop = true;
    while (loop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                loop = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    loop = false;
                    break;
                }
                break;
            }
        }

        // start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // standard demo window
        if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window); }

        // a window is defined by Begin/End pair
        {
            static int counter = 0;

            int sdl_width = 0, sdl_height = 0, controls_width = 0;
            // get the window size as a base for calculating widgets geometry
            SDL_GetWindowSize(window, &sdl_width, &sdl_height);
            controls_width = sdl_width;
            // make controls widget width to be 1/3 of the main window width
            if ((controls_width /= 3) < 300) { controls_width = 300; }

            // position the controls widget in the top-right corner with some margin
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
            // here we set the calculated width and also make the height to be
            // be the height of the main window also with some margin
            ImGui::SetNextWindowSize(
                ImVec2(static_cast<float>(controls_width), static_cast<float>(sdl_height - 20)),
                ImGuiCond_Always
                );
            // create a window and append into it
            ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoResize);

            ImGui::Dummy(ImVec2(0.0f, 1.0f));
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Time");
            ImGui::Text("%s", currentTime(std::chrono::system_clock::now()).c_str());

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform");
            ImGui::Text("%s", SDL_GetPlatform());
            ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
            ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Application");
            ImGui::Text("Main window width: %d", sdl_width);
            ImGui::Text("Main window height: %d", sdl_height);

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "SDL");
            ImGui::Text("%s", compiledVal.str().c_str());
            ImGui::Text("%s", linkedVal.str().c_str());

            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            
            // buttons and most other widgets return true when clicked/edited/activated
            if (ImGui::Button("Counter button"))
            {
                std::cout << "counter button clicked\n";
                counter++;
                if (counter == 9) { ImGui::OpenPopup("Easter egg"); }
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            if (ImGui::BeginPopupModal("Easter egg", NULL))
            {
                ImGui::Text("Ho-ho, you found me!");
                if (ImGui::Button("Buy Ultimate Orb")) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }

            ImGui::Dummy(ImVec2(0.0f, 15.0f));
            if (!show_demo_window)
            {
                if (ImGui::Button("Open standard demo"))
                {
                    show_demo_window = true;
                }
            }

            ImGui::Checkbox("show a custom window", &show_another_window);
            if (show_another_window)
            {
                ImGui::SetNextWindowSize(
                    ImVec2(400.0f, 350.0f),
                    ImGuiCond_FirstUseEver // after first launch it will use values from imgui.ini
                    );
                // the window will have a closing button that will clear the bool variable
                ImGui::Begin("A custom window", &show_another_window);
                
                ImGui::Dummy(ImVec2(0.0f, 1.0f));
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Files in the current folder");
                                
                //ImGui::TextColored(ImVec4(128 / 255.0f, 128 / 255.0f, 128 / 255.0f, 1.0f), "%s", currentPath.string().data());
                ImGui::Dummy(ImVec2(0.0f, 0.5f));

                // static int currentFile = 0;
                // ImVec2 windowSize = ImGui::GetWindowSize();
                // ImGui::PushItemWidth(windowSize.x - 15);
                // ImGui::ListBox(
                //     "",
                //     &currentFile,
                //     vector_getter,
                //     &files,
                //     static_cast<int>(files.size())
                //     );

                ImGui::Dummy(ImVec2(0.0f, 1.0f));
                if (ImGui::Button("Close"))
                {
                    std::cout << "close button clicked\n";
                    show_another_window = false;
                }

                ImGui::End();
            }

            ImGui::End();
        }

        // rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(
            background.x,
            background.y,
            background.z,
            background.w
            );
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // you may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "\n- - -\n" << "[" << currentTime(std::chrono::system_clock::now()) << "] " << "Quit\n";
    
    return 0;
}
