#include <cmath>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "implot.h"

void get_window_config() {
    ImGuiIO& io = ImGui::GetIO();
    float screen_width = io.DisplaySize.x;
    float screen_height = io.DisplaySize.y;
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