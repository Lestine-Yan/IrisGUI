#include"view.h"

namespace IrisGUI {
	View::View(const std::string& className, std::wstring& text) : 
		Div(className,text), m_text(text) {
	}
	void View::update() {
		this->setText(m_text);
	}
}