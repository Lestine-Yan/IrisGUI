#include "pch.h"
#include "../include/Link.h"
#include "../include/App.h"
#include "../include/Layout.h"
#include "../include/Root.h"

namespace IrisGUI {

Link::Link(std::size_t appIndex, int w, int h)
    : Div(w, h), m_appIndex(appIndex) {}

Link::Link(const std::string& className, std::size_t appIndex, int w, int h)
    : Div(className, w, h), m_appIndex(appIndex) {}

void Link::onMouseDown(const ExMessage& msg)
{
    if (msg.message != WM_LBUTTONDOWN)
        return;

    App* currentApp = nullptr;
    Root* root = nullptr;

    for (Widget* current = this; current; current = current->parent()) {
        if (!currentApp) {
            if (auto* app = dynamic_cast<App*>(current))
                currentApp = app;
            else if (auto* layout = dynamic_cast<Layout*>(current))
                currentApp = layout->app();
        }

        if (!root) {
            if (auto* foundRoot = dynamic_cast<Root*>(current))
                root = foundRoot;
        }
    }

    if (currentApp && !root) {
        for (Widget* current = currentApp; current; current = current->parent()) {
            if (auto* foundRoot = dynamic_cast<Root*>(current)) {
                root = foundRoot;
                break;
            }
        }
    }

    if (!currentApp || !root)
        return;

    const auto& rootChildren = root->children();
    if (m_appIndex >= rootChildren.size())
        return;

    auto* targetApp = dynamic_cast<App*>(rootChildren[m_appIndex]);
    if (!targetApp || targetApp == currentApp)
        return;

    currentApp->hide();
    targetApp->show();
}

} // namespace IrisGUI
