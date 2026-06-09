#include"viewScore.h"

namespace IrisGUI {
	ViewScore::ViewScore(const std::string& className, std::wstring& text) :
		Div(className, text), m_text(text) {
	}
	void ViewScore::update() {
		this->setText(m_text);
	}
}