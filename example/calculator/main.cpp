#include"iris.h"
#include"Button.h"
#include"view.h"

#include<graphics.h>
#include<conio.h>

int main() {
	std::wstring s = L"0";
	IrisGUI::Root root(L"calculator");
	root.mount(new IrisGUI::App());
	root.app(0).addChild(new IrisGUI::View("w-320 h-160 bg-white",s));

	root.app(0).addChild(new IrisGUI::Div("w-320 h-40 bg-gray flex"));
	root.app(0)[1].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"a", s));
	root.app(0)[1].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"e", s));
	root.app(0)[1].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"d", s));
	root.app(0)[1].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"/", s));

	root.app(0).addChild(new IrisGUI::Div("w-320 h-40 bg-gray flex"));
	root.app(0)[2].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"7", s));
	root.app(0)[2].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"8", s));
	root.app(0)[2].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"9", s));
	root.app(0)[2].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"*", s));

	root.app(0).addChild(new IrisGUI::Div("w-320 h-40 bg-gray flex"));
	root.app(0)[3].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"4", s));
	root.app(0)[3].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"5", s));
	root.app(0)[3].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"6", s));
	root.app(0)[3].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"-", s));

	root.app(0).addChild(new IrisGUI::Div("w-320 h-40 bg-gray flex"));
	root.app(0)[4].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"1", s));
	root.app(0)[4].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"2", s));
	root.app(0)[4].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"3", s));
	root.app(0)[4].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"+", s));

	root.app(0).addChild(new IrisGUI::Div("w-320 h-40 bg-gray flex"));
	root.app(0)[5].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"00", s));
	root.app(0)[5].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"0", s));
	root.app(0)[5].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L".", s));
	root.app(0)[5].addChild(new IrisGUI::Button("w-80 h-40 border-black b-1 bg-gray", L"=", s));

	root.end();
	return 0;
}
