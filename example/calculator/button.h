#pragma once
#include"Div.h"

namespace IrisGUI {

	class Button : public Div {
	public:
		Button(const std::string& , std::wstring c , std::wstring& s);

		void onMouseDown(const ExMessage& msg)override;
	private:
		std::wstring m_c;
		std::wstring& m_s;
	};
}