#include"Div.h"

namespace IrisGUI {

class View : public Div {

public:
	View(const std::string& className,std::wstring& text);
	void update()override;


private:
	std::wstring& m_text;
};

}