#include <GLFW/glfw3.h> // OpenGL과 GLFW 포함
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <stdio.h>
#include "single_include/nlohmann/json.hpp"

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    // GLFW 윈도우와 OpenGL 컨텍스트 생성
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Demo", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // OpenGL 함수 로딩 (GLEW 없이 수동으로 로딩할 수 있습니다. 그러나 최신 OpenGL 기능을 사용하려면 수동 로딩이 필요합니다.)

    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // 스타일 설정
    ImGui::StyleColorsDark();

    // ImGui와 GLFW, OpenGL 연동 설정
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 메인 루프
    bool running = true;
    while (running) {
        // 이벤트 처리
        glfwPollEvents();

        // ImGui 프레임 시작
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui 데모 창 표시
        ImGui::ShowDemoWindow();

        // 렌더링
        ImGui::Render();
        glClearColor(0.40f, 0.50f, 0.55f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 화면 업데이트
        glfwSwapBuffers(window);
    }

    // 종료 및 리소스 정리
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
