#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_backend.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../imgui_frontend/gui.h"

class LinuxBackend : public ImGUIBackend_Interface {
public:
    void initialize() override {
        // GLFW 초기화
        if (!glfwInit()) {
            std::cerr << "GLFW 초기화 실패\n";
            return;
        }

        // OpenGL 설정
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1280, 720, "MarketDAQ", nullptr, nullptr);
        if (!window) {
            std::cerr << "윈도우 생성 실패\n";
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);  // vsync

        // ImGui 컨텍스트 초기화
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        // ImGui 백엔드 초기화
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void renderUI() override {
        if (!window || glfwWindowShouldClose(window))
            return;

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window_layout(); // Front-end

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    void cleanup() override {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (window)
            glfwDestroyWindow(window);

        glfwTerminate();
    }

private:
    GLFWwindow* window = nullptr;
};

ImGUIBackend_Interface* CreateBackend() {
    return new LinuxBackend();
}