#pragma once
#include <bits/stdc++.h>

#include <fmt/color.h>

#include "GLFW/glfw3.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "lib/BasePage.hpp"
#include "lib/HomePage.hpp"
#include "lib/SettingPage.hpp"

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

		struct PageEntry {
			std::string               pageNavName;
			std::unique_ptr<BasePage> page;
		};
		std::vector<PageEntry> pages;
		pages.emplace_back("Home Page", std::make_unique<HomePage>());
		pages.emplace_back("Settings", std::make_unique<SettingPage>());
		int currentPage = 0;
		while (!glfwWindowShouldClose(this->window)) {
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::PushFont(myFont);
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(this->io->DisplaySize);
			if (ImGui::Begin("MainWindow", nullptr,
							 ImGuiWindowFlags_NoTitleBar
							 | ImGuiWindowFlags_NoResize
							 | ImGuiWindowFlags_NoMove
							 | ImGuiWindowFlags_NoCollapse)) {
				// LEFT: Navigator
				ImGui::BeginChild("Navigator",
								  ImVec2(this->io->DisplaySize.x / 8, 0),
								  true);

				for (int i = 0; i < pages.size(); i++) {
					if (ImGui::Selectable(pages[i].pageNavName.c_str(), currentPage == i)) {
						currentPage = i;
					}
				}

				ImGui::EndChild();

				ImGui::SameLine();

				// RIGHT: Content
				ImGui::BeginChild("Content", ImVec2(0, 0), true);

				pages[currentPage].page->Display();

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

	void SetModernGrayTheme() {
		ImGuiStyle& style = ImGui::GetStyle();

		// 🎯 Layout
		style.WindowRounding    = 6.0f;
		style.FrameRounding     = 6.0f;
		style.PopupRounding     = 6.0f;
		style.ScrollbarRounding = 6.0f;
		style.GrabRounding      = 6.0f;

		style.WindowPadding = ImVec2(10, 10);
		style.FramePadding  = ImVec2(10, 6);
		style.ItemSpacing   = ImVec2(8, 6);

		// 🎨 Colors
		ImVec4* colors = style.Colors;

		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_ChildBg]  = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);
		colors[ImGuiCol_PopupBg]  = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);

		colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);

		// Text
		colors[ImGuiCol_Text]         = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		// Buttons
		colors[ImGuiCol_Button]        = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
		colors[ImGuiCol_ButtonActive]  = ImVec4(0.40f, 0.40f, 0.42f, 1.00f);

		// Headers (Selectable, Tree, etc.)
		colors[ImGuiCol_Header]        = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
		colors[ImGuiCol_HeaderActive]  = ImVec4(0.40f, 0.40f, 0.42f, 1.00f);

		// Frame (input, checkbox, etc.)
		colors[ImGuiCol_FrameBg]        = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.24f, 1.00f);
		colors[ImGuiCol_FrameBgActive]  = ImVec4(0.28f, 0.28f, 0.30f, 1.00f);

		// Tabs
		colors[ImGuiCol_Tab]        = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.38f, 0.40f, 1.00f);
		colors[ImGuiCol_TabActive]  = ImVec4(0.28f, 0.28f, 0.30f, 1.00f);

		// Title
		colors[ImGuiCol_TitleBg]       = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.42f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);
	}

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
		SetModernGrayTheme();
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
