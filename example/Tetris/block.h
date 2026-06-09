#pragma once

#include "Div.h"
#include <array>
#include <string>
#include <utility>

namespace IrisGUI {

enum class BlockType {
    I,      // blue   - 4 in a row
    O,      // yellow - 2×2 square
    T,      // purple - T-shaped
    S,      // green  - S-shaped
    Z       // red    - Z-shaped
};

class Block : public Div {
public:
    Block(BlockType type);

    BlockType type() const { return m_type; }

    static std::string classNameForType(BlockType type);

private:
    BlockType m_type;
};

using PieceBlocks = std::array<std::pair<int, int>, 4>;

using PieceRotations = std::array<PieceBlocks, 4>;

const PieceRotations& getPieceRotations(BlockType type);

} // namespace IrisGUI
