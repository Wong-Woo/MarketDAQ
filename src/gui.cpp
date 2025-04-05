#include <cmath>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"
#include "implot.h"

void plot_window() {
    ImPlot::CreateContext();
    ImGui::Begin("Plot");

    ImGui::End();
    ImPlot::DestroyContext();
}

void select_window() {
    ImGui::Begin("Select");

    ImGui::End();
}

void news_window() {
    ImGui::Begin("News");

    ImGui::End();
}