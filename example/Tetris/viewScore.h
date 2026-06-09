#pragma once
#include"Div.h"

namespace IrisGUI {

	class ViewScore : public Div {

	public:
		ViewScore(const std::string& className, std::wstring& text);
		void update()override;


	private:
		std::wstring& m_text;
	};

}
