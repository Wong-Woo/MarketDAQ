#ifndef IMGUI_BACKEND_H
#define IMGUI_BACKEND_H

#include <memory>

class iImGUIBackend {
public:
    virtual ~iImGUIBackend() = default;

    // Initialize the backend
    virtual void initialize() = 0;

    // Render the ImGui UI
    virtual void renderUI() = 0;

    // Cleanup resources
    virtual void cleanup() = 0;
};

std::unique_ptr<iImGUIBackend> CreateBackend();

#endif