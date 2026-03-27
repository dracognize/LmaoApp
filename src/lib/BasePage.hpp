#pragma once

class BasePage {
public:
	virtual ~BasePage() = default;

	virtual void Display() = 0;
};