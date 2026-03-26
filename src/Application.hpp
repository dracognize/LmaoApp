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

	int width, height;

	ImGuiIO*    io;
	GLFWwindow* window;

	void Start() {
		ImFont* myFont = this->io->Fonts->AddFontFromFileTTF("assets/BeVietnamPro-Regular.ttf",
															 36.0f);
		if (!myFont) fmt::print(fg(fmt::color::red), "Failed to load font!\n");
		while (!glfwWindowShouldClose(this->window)) {
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::PushFont(myFont);
			ImGui::SetNextWindowSize({static_cast<float>(this->width), static_cast<float>(this->height)});
			ImGui::SetNextWindowPos({0, 0});
			if (ImGui::Begin("MainWindow", nullptr,
							 ImGuiWindowFlags_NoTitleBar
							 | ImGuiWindowFlags_NoResize
							 | ImGuiWindowFlags_NoMove
							 | ImGuiWindowFlags_NoCollapse)) {
				if (ImGui::Button("Quit")) {
					glfwSetWindowShouldClose(this->window, GLFW_TRUE);
				}
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
		this->width                = mode->width * 3 / 4;
		this->height               = mode->height * 3 / 4;
		this->window               = glfwCreateWindow(width, height, "Lmao App",
													  nullptr, nullptr);

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
