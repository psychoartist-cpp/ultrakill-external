#include "GuiWindow.h"

GuiWindow::GuiWindow() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Remove window decorations
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Enable transparency
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // Always on top
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable resizing


	m_bIsInit = true;
}
GuiWindow::~GuiWindow() {
	glfwTerminate();
	glfwDestroyWindow(m_window);
}

static ImVec2 SubtractVectors2(ImVec2 source, ImVec2 other) {
    ImVec2 result(source.x - other.x, source.y - other.y);
    return result;
}

void GuiWindow::Run() {
    if (!m_bIsInit) return;

    m_window = glfwCreateWindow(800, 600, "imgui window", NULL, NULL);

    if (!m_window) {
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int screenWidth, screenHeight;
        glfwGetWindowSize(m_window, &screenWidth, &screenHeight);

        ImGui::SetNextWindowPos(m_windowPos, ImGuiCond_FirstUseEver);
        ImGui::Begin("Cheat Menu", nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                ImVec2 delta = ImGui::GetIO().MouseDelta;
                m_windowPos.x += delta.x;
                m_windowPos.y += delta.y;

                m_windowPos.x = std::max(0.0f, std::min(m_windowPos.x, (float)screenWidth - ImGui::GetWindowWidth()));
                m_windowPos.y = std::max(0.0f, std::min(m_windowPos.y, (float)screenHeight - ImGui::GetWindowHeight()));

                ImGui::SetWindowPos(m_windowPos);
            }
        }
        else {
            m_isDragging = false;
        }

        this->PollRender();

        if (ImGui::SliderInt("HP", &m_Hp, 1, 10000)) {
            this->PollHpSlider(m_Hp);
        }
        if (ImGui::SliderInt("Walkspeed", &m_Walkspeed, 1, 10000)) {
            this->PollWalkspeedSlider(m_Walkspeed);
        }
        if (ImGui::SliderInt("Jumpspeed", &m_Jumpspeed, 1, 10000)) {
            this->PollJumpspeedSlider(m_Jumpspeed);
        }

        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }
}