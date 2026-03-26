#pragma once
#include <functional>
#include <string>

#include <fmt/core.h>
#include <fmt/color.h>

#include "GLFW/glfw3.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Application {
public:
	Application(const Application&) = delete;

	Application& operator=(const Application&) = delete;

	Application(Application&&) = delete;

	Application& operator=(Application&&) = delete;

	static auto getInstance() -> Application& {
		static Application instance;
		return instance;
	}

	ImGuiIO*    io;
	GLFWwindow* window;

	void Start() {
		ImFont* myFont = this->io->Fonts->AddFontFromFileTTF("assets/BeVietnamPro-Regular.ttf",
															 36.0f);
		if (!myFont) fmt::print(fg(fmt::color::red), "Failed to load font!\n");

		int page_selected = 0;
		bool enable_feature = false;
		while (!glfwWindowShouldClose(this->window)) {
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::PushFont(myFont);
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
			if (ImGui::Begin("MainWindow", nullptr,
							 ImGuiWindowFlags_NoTitleBar
							 | ImGuiWindowFlags_NoResize
							 | ImGuiWindowFlags_NoMove
							 | ImGuiWindowFlags_NoCollapse)) {
				// Get full window size
				ImVec2 size = ImGui::GetContentRegionAvail();

				// Left panel width
				float left_width = 150.0f;

				// LEFT: Navigator
				ImGui::BeginChild("Navigator", ImVec2(left_width, 0), true);

				if (ImGui::Selectable("Home", page_selected == 0)) page_selected = 0;
				if (ImGui::Selectable("Settings", page_selected == 1)) page_selected = 1;
				if (ImGui::Selectable("Profile", page_selected == 2)) page_selected = 2;

				ImGui::EndChild();

				ImGui::SameLine();

				// RIGHT: Content
				ImGui::BeginChild("Content", ImVec2(0, 0), true);

				if (page_selected == 0) {
					ImGui::Text("Home Page");
					ImGui::Separator();
					ImGui::Text("Welcome to the home screen!");
				}
				else if (page_selected == 1) {
					ImGui::Text("Settings");
					ImGui::Separator();
					ImGui::Checkbox("Enable feature", &enable_feature);
				}
				else if (page_selected == 2) {
					ImGui::Text("Profile");
					ImGui::Separator();
					ImGui::Text("User info goes here.");
				}

				ImGui::EndChild();
			}
			ImGui::End();
			ImGui::PopFont();

			ImGui::Render();

			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(this->window);
		};
		this->_message = {
			fg(fmt::color::light_green),
			"Application running and exiting normally"
		};
	}

private:
	struct {
		fmt::text_style style;
		std::string     value;
	} _message = {fg(fmt::color::yellow), "Application exited."};

	Application() {
		glfwInit();

		GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode    = glfwGetVideoMode(monitor);
		this->window               = glfwCreateWindow(mode->width * 3 / 4, mode->height * 3 / 4,
										"Lmao App", nullptr, nullptr);

		if (!window) {
			fmt::print(fg(fmt::color::red), "Failed to create GLFW window\n");
			glfwTerminate();
			std::exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		this->io = &ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	~Application() {
		fmt::print(this->_message.style, "{}", this->_message.value);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
};
