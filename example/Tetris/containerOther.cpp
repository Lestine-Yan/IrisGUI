#include "containerOther.h"

#include <Windows.h>

namespace IrisGUI {

ContainerOther::ContainerOther(const std::string& className, std::wstring& scoreText)
    : Container(className, scoreText)
{
}

void ContainerOther::update()
{
    Div::update();
    if (m_gameOver) return;

    ++m_tick;

    // ── Input ────────────────────────────────────────────
    // Cooldown tick
    if (m_moveCooldown > 0)
        --m_moveCooldown;

    // A = left / D = right (with cooldown)
    if (m_moveCooldown == 0) {
        if (GetAsyncKeyState('A') & 0x8000) {
            movePiece(-1, 0);
            m_moveCooldown = 6;
        } else if (GetAsyncKeyState('D') & 0x8000) {
            movePiece(1, 0);
            m_moveCooldown = 6;
        }
    }

    // S = soft drop (no cooldown)
    if (GetAsyncKeyState('S') & 0x8000)
        movePiece(0, 1);

    // W = rotate (rising-edge / single press)
    {
        bool pressed = (GetAsyncKeyState('W') & 0x8000) != 0;
        if (pressed && !m_rotatePressed)
            rotatePiece();
        m_rotatePressed = pressed;
    }

    // Space = hard drop (rising-edge)
    {
        bool pressed = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
        if (pressed && !m_dropPressed)
            hardDrop();
        m_dropPressed = pressed;
    }

    // ── Gravity ──────────────────────────────────────────
    if (m_gameOver) return;

    if (m_tick % DROP_INTERVAL == 0) {
        if (!movePiece(0, 1)) {
            lockPiece();
            if (m_gameOver) return;
            clearLines();
            spawnPiece();
            m_tick = 0;
        }
    }
}

} // namespace IrisGUI
