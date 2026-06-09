#pragma once

#include "container.h"

namespace IrisGUI {

/// Same as Container but uses W/A/S/D keys instead of arrow keys.
/// W = rotate, A = left, S = down, D = right, Space = hard drop
class ContainerOther : public Container {
public:
    ContainerOther(const std::string& className, std::wstring& scoreText);

    void update() override;
};

} // namespace IrisGUI
