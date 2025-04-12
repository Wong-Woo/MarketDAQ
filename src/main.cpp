#include <iostream>
#include "imgui_backend/imgui_backend.h"
#include "single_include/nlohmann/json.hpp"

int main() {
    ImGUIBackend_Interface* backend = CreateBackend();
    if (!backend) {
        std::cerr << "백엔드 생성 실패!\n";
        return -1;
    }

    backend->initialize();

    // 메인 루프
    while (true) {
        backend->renderUI();
    }

    backend->cleanup();
    delete backend;
    return 0;
}