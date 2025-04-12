#ifndef IMGUI_BACKEND_H
#define IMGUI_BACKEND_H

class ImGUIBackend_Interface {
public:
    virtual ~ImGUIBackend_Interface() = default;

    // Initialize the backend
    virtual void initialize() = 0;

    // Render the ImGui UI
    virtual void renderUI() = 0;

    // Cleanup resources
    virtual void cleanup() = 0;
};

ImGUIBackend_Interface* CreateBackend();

#endif