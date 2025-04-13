#include <iostream>
#include "imgui_backend/imgui_backend.h"
#include "single_include/nlohmann/json.hpp"

int main() {
    ImGUIBackend_Interface* imgui_backend = CreateBackend();
    if (!imgui_backend) {
        std::cerr << "백엔드 생성 실패!\n";
        return -1;
    }

    imgui_backend->initialize();

    // 메인 루프
    while (true) {
        imgui_backend->renderUI();
    }

    imgui_backend->cleanup();
    delete imgui_backend;
    return 0;
}