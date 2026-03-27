#pragma once

class SettingPage : public BasePage {
	public:
	void Display() override {
		ImGui::Text("This is my setting page");
	}
};