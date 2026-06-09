#include "iris.h"
#include "container.h"
#include "containerOther.h"
#include "viewScore.h"

#include <string>

int main()
{
    IrisGUI::Root root(L"Tetris");

    root.mount(new IrisGUI::App());//开始界面
	root.app(0).addChild(new IrisGUI::Div("w-1200 h-960 bg-[124,62,247]"));
	root.app(0)[0].addChild(new IrisGUI::Div("w-1200 h-350 bg-[bg.png]"));
    root.app(0)[0].addChild(new IrisGUI::Link("w-1200 h-305 bg-[button2.png]",2));
    root.app(0)[0].addChild(new IrisGUI::Link("w-1200 h-305 bg-[button1.png]",1));

    root.mount(new IrisGUI::App());//单人模式
	std::wstring score = L"分数: 0";
    root.app(1).addChild(new IrisGUI::Div("w-1200 h-960 bg-[0,0,0] flex"));
    root.app(1)[0].addChild(new IrisGUI::Div("w-240 h-960 bg-[117,50,250]"));
    root.app(1)[0].addChild(new IrisGUI::Container("w-480 h-960 bg-[126,154,172]",score));
    root.app(1)[0].addChild(new IrisGUI::Div("w-240 h-960 bg-[117,50,250]"));
    root.app(1)[0][2].addChild(new IrisGUI::ViewScore("mx-60 my-80 w-120 h-60 bg-white round-16", score));
	root.app(1)[0][2].addChild(new IrisGUI::Div("mx-60 mt-240 mb-20 w-120 h-60 bg-white round-4", L"按↑旋转"));
	root.app(1)[0][2].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"按←左移"));
	root.app(1)[0][2].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"按→右移"));
	root.app(1)[0][2].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"按↓加速"));
	root.app(1)[0].addChild(new IrisGUI::Div("w-240 h-960 bg-[117,50,250]"));
    
	root.mount(new IrisGUI::App());//多人模式
	std::wstring scoreA = L"分数: 0";
	std::wstring scoreB = L"分数: 0";
    root.app(2).addChild(new IrisGUI::Div("w-1200 h-960 bg-[0,0,0] flex"));
	root.app(2)[0].addChild(new IrisGUI::ContainerOther("w-480 h-960 bg-[126,154,172]", scoreA));
	root.app(2)[0].addChild(new IrisGUI::Div("w-240 h-960 bg-[117,50,250]"));
	root.app(2)[0].addChild(new IrisGUI::Container("w-480 h-960 bg-[126,154,172]", scoreB));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 my-20 mb-20 w-120 h-60 bg-white round-8", L"玩家A(左)"));
	root.app(2)[0][1].addChild(new IrisGUI::ViewScore("mx-60 mt-10 mb-80 w-120 h-60 bg-white round-16", scoreA));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 my-20 mb-20 w-120 h-60 bg-white round-4", L"右W/左↑旋转"));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"右A/左←左移"));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"右D/左→右移"));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 my-20 w-120 h-60 bg-white round-4", L"右S/左↓加速"));
	root.app(2)[0][1].addChild(new IrisGUI::Div("mx-60 mt-80 mb-20 w-120 h-60 bg-white round-8", L"玩家B(右)"));
	root.app(2)[0][1].addChild(new IrisGUI::ViewScore("mx-60 mt-10 w-120 h-60 bg-white round-16", scoreB));

    root.end();
    return 0;
}
