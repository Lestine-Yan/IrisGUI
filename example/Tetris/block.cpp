#include "block.h"

namespace IrisGUI {

Block::Block(BlockType type)
    : Div(classNameForType(type))
    , m_type(type)
{
}

std::string Block::classNameForType(BlockType type)
{
    switch (type) {
    case BlockType::I: return "w-48 h-48 bg-[blue.png]";
    case BlockType::O: return "w-48 h-48 bg-[yellow.png]";
    case BlockType::T: return "w-48 h-48 bg-[purple.png]";
    case BlockType::S: return "w-48 h-48 bg-[green.png]";
    case BlockType::Z: return "w-48 h-48 bg-[red.png]";
    }
    return "w-48 h-48";
}

// ─────────────────────────────────────────────────────────
//  Piece shape data  — 4 (row, col) offsets per rotation
// ─────────────────────────────────────────────────────────

namespace {

// 5 types × 4 rotations × 4 blocks × 2 coords
static const int kShapes[5][4][4][2] =
{
    // I
    {
        {{0,0}, {0,1}, {0,2}, {0,3}},
        {{0,0}, {1,0}, {2,0}, {3,0}},
        {{0,0}, {0,1}, {0,2}, {0,3}},
        {{0,0}, {1,0}, {2,0}, {3,0}},
    },
    // O
    {
        {{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}},
    },
    // T
    {
        {{0,1}, {1,0}, {1,1}, {1,2}},
        {{0,0}, {1,0}, {2,0}, {1,1}},
        {{0,0}, {0,1}, {0,2}, {1,1}},
        {{0,1}, {1,0}, {1,1}, {2,1}},
    },
    // S
    {
        {{0,1}, {0,2}, {1,0}, {1,1}},
        {{0,0}, {1,0}, {1,1}, {2,1}},
        {{0,1}, {0,2}, {1,0}, {1,1}},
        {{0,0}, {1,0}, {1,1}, {2,1}},
    },
    // Z
    {
        {{0,0}, {0,1}, {1,1}, {1,2}},
        {{0,1}, {1,0}, {1,1}, {2,0}},
        {{0,0}, {0,1}, {1,1}, {1,2}},
        {{0,1}, {1,0}, {1,1}, {2,0}},
    },
};

// Lazily-built PieceRotations cache
static PieceRotations g_cache[5];
static bool           g_cacheReady = false;

void buildCache()
{
    if (g_cacheReady) return;
    for (int t = 0; t < 5; ++t) {
        for (int r = 0; r < 4; ++r) {
            for (int b = 0; b < 4; ++b) {
                g_cache[t][r][b].first  = kShapes[t][r][b][0];
                g_cache[t][r][b].second = kShapes[t][r][b][1];
            }
        }
    }
    g_cacheReady = true;
}

} // namespace

const PieceRotations& getPieceRotations(BlockType type)
{
    buildCache();
    return g_cache[static_cast<int>(type)];
}

} // namespace IrisGUI
