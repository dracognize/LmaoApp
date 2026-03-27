#pragma once

class HomePage : public BasePage {
public:
	void Display() override {
			ImGui::Text("This is my home page");
	};
};
