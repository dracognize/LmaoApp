#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <print>

int main() {
	// Init GLFW
	glfwInit();
	GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode    = glfwGetVideoMode(monitor);
	const int          width   = mode->width / 2;
	const int          height  = mode->height * 3 / 4;
	GLFWwindow*        window  = glfwCreateWindow(width, height, "Lmao App", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImFont* smallFont = io.Fonts->AddFontFromFileTTF(
	"assets/BeVietnamPro-Regular.ttf",
	24.0f,
	nullptr,
	io.Fonts->GetGlyphRangesVietnamese()
	);

	ImFont* bigFont = io.Fonts->AddFontFromFileTTF(
	"assets/BeVietnamPro-Regular.ttf",
	36.0f,
	nullptr,
	io.Fonts->GetGlyphRangesVietnamese()
	);

	int cnt = 0;

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Start frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// UI
		ImGui::SetNextWindowSize({static_cast<float>(width), static_cast<float>(height)});
		ImGui::SetNextWindowPos({0, 0});
		ImGui::Begin("Hello", nullptr,
					 ImGuiWindowFlags_NoTitleBar
					 | ImGuiWindowFlags_NoCollapse
					 | ImGuiWindowFlags_NoResize
					 | ImGuiWindowFlags_NoMove);
		ImGui::PushFont(bigFont);
		ImGui::Text("Counter: %d", cnt);
		ImGui::PopFont();
		ImGui::PushFont(smallFont);
		if (ImGui::Button("Increase")) {
			cnt++;
		}
		ImGui::PopFont();
		ImGui::End();

		// Render
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
