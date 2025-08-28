#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <functional>
#include <vector>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

#include <GLFW/glfw3.h>
#include <GL/GL.h>

#pragma comment(lib, "opengl32.lib")

// We will have three float sliders (hp,walkspeed,jump speed)
// If the user is in the menu, a red text should appear: "Failed to get player! Are you in a level?"
class GuiWindow {
private:
	typedef std::function<void()>    ButtonCallback;
	typedef std::function<void(int)> IntSliderCallback;
	typedef std::function<void()>    OnRenderCallback;

	std::atomic<bool> m_bIsInit = false;

	int m_Hp = 0, m_Walkspeed = 0, m_Jumpspeed = 0;

	// In the main file, set those callbacks and write to memory in them
	IntSliderCallback m_hpCallback, m_walkspeedCallback, m_jumpspeedCallback;
	OnRenderCallback m_renderCallback;

	GLFWwindow* m_window;
	ButtonCallback m_btnCallback;

	ImVec2 m_windowPos = ImVec2(100, 100);
	bool m_isDragging = false;
	ImVec2 m_dragOffset;
	ImVec2 m_initialMousePos;
private:
	void PollHpSlider(int value) {
		if (this->m_hpCallback) this->m_hpCallback(value);
	} 
	void PollWalkspeedSlider(int value) {
		if (this->m_walkspeedCallback) this->m_walkspeedCallback(value);
	}
	void PollJumpspeedSlider(int value) {
		if (this->m_jumpspeedCallback) this->m_jumpspeedCallback(value);
	}
	void PollRender() {
		if (this->m_renderCallback) this->m_renderCallback();
	}
	void SetupTransparentStyle() {
		ImGuiStyle& style = ImGui::GetStyle();

		// Make window completely transparent
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // Semi-transparent
		style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // No border
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

		// Remove window padding and rounding
		style.WindowPadding = ImVec2(0.0f, 0.0f);
		style.WindowRounding = 0.0f;
		style.FramePadding = ImVec2(8.0f, 4.0f);

		// Make child windows and frames transparent too
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.6f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	}
public:
	GuiWindow();
	~GuiWindow();

	void Run();
	void OnHpSlider(IntSliderCallback callback)        { this->m_hpCallback = callback; }
	void OnWalkspeedSlider(IntSliderCallback callback) { this->m_walkspeedCallback = callback; }
	void OnJumpspeedSlider(IntSliderCallback callback) { this->m_jumpspeedCallback = callback; }
	void OnImguiRender(OnRenderCallback callback)      { this->m_renderCallback = callback; }
};