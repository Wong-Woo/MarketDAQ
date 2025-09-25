#include <cmath>
#include "imgui.h"
#include "implot.h"
#include "layout.h"

#ifdef _WIN32
    // Windows - DirectX 백엔드 사용
#else
    // Linux - GLFW 백엔드 사용
    #include <GLFW/glfw3.h>
#endif

void layout() {
    ImGuiIO& io = ImGui::GetIO();
    float screen_width = io.DisplaySize.x;
    float screen_height = io.DisplaySize.y;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(screen_width*2/3, screen_height), ImGuiCond_Always);
    plot_window();

    ImGui::SetNextWindowPos(ImVec2(screen_width*2/3, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(screen_width*2/3, screen_height/2), ImGuiCond_Always);
    select_window();

    ImGui::SetNextWindowPos(ImVec2(screen_width*2/3, screen_height/2), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(screen_width*2/3, screen_height/2), ImGuiCond_Always);
    news_window();
}

void plot_window() {
    ImGui::Begin("Plot");
    ImPlot::CreateContext();

    ImPlot::DestroyContext();
    ImGui::End();
}

void select_window() {
    ImGui::Begin("Select");

    ImGui::End();
}

void news_window() {
    ImGui::Begin("News");

    ImGui::End();
}