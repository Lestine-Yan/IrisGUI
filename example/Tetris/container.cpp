#include "container.h"

#include <cstdlib>
#include <ctime>
#include <Windows.h>

namespace IrisGUI {

Container::Container(const std::string& className, std::wstring& scoreText)
    : Div(className)
    , m_scoreText(scoreText)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    m_scoreText = L"分数: 0";
    spawnPiece();
}

// ─────────────────────────────────────────────────────────
//  Coordinate helpers
// ─────────────────────────────────────────────────────────

int Container::boardLeft() const
{
    return m_x + m_style.margin.left + m_style.padding.left + m_style.borderWidth;
}

int Container::boardTop() const
{
    return m_y + m_style.margin.top + m_style.padding.top + m_style.borderWidth;
}

// ─────────────────────────────────────────────────────────
//  Drawing
// ─────────────────────────────────────────────────────────

void Container::draw()
{
    Div::draw();  

    setlinecolor(RGB(215, 238, 253));
    const int bl = boardLeft();
    const int bt = boardTop();

    for (int r = 0; r <= ROWS; ++r)
        line(bl, bt + r * CELL, bl + COLS * CELL, bt + r * CELL);

    for (int c = 0; c <= COLS; ++c)
        line(bl + c * CELL, bt, bl + c * CELL, bt + ROWS * CELL);
}

// ─────────────────────────────────────────────────────────
//  Active piece position sync
// ─────────────────────────────────────────────────────────

void Container::updateActiveBlockPositions()
{
    const auto& shape = getPieceRotations(m_activeType)[m_rotation];
    const int bl = boardLeft();
    const int bt = boardTop();

    for (int i = 0; i < 4; ++i) {
        if (!m_activeBlocks[i]) continue;
        const auto& [dr, dc] = shape[i];
        m_activeBlocks[i]->setPos(
            bl + (m_pieceCol + dc) * CELL,
            bt + (m_pieceRow + dr) * CELL);
    }
}

// ─────────────────────────────────────────────────────────
//  Collision detection
// ─────────────────────────────────────────────────────────

bool Container::checkCollision(BlockType type, int rot, int col, int row) const
{
    const auto& shape = getPieceRotations(type)[rot];
    for (const auto& [dr, dc] : shape) {
        const int r = row + dr;
        const int c = col + dc;
        if (c < 0 || c >= COLS || r >= ROWS)
            return true;                       
        if (r < 0)
            continue;                           
        if (m_board[r][c] != nullptr)
            return true;                      
    }
    return false;
}

// ─────────────────────────────────────────────────────────
//  Movement  /  Rotation
// ─────────────────────────────────────────────────────────

bool Container::movePiece(int dcol, int drow)
{
    if (checkCollision(m_activeType, m_rotation, m_pieceCol + dcol, m_pieceRow + drow))
        return false;

    m_pieceCol += dcol;
    m_pieceRow += drow;
    updateActiveBlockPositions();
    return true;
}

bool Container::rotatePiece()
{
    const int newRot = (m_rotation + 1) % 4;

    if (!checkCollision(m_activeType, newRot, m_pieceCol, m_pieceRow)) {
        m_rotation = newRot;
        updateActiveBlockPositions();
        return true;
    }

    if (!checkCollision(m_activeType, newRot, m_pieceCol - 1, m_pieceRow)) {
        m_rotation = newRot;
        --m_pieceCol;
        updateActiveBlockPositions();
        return true;
    }
    if (!checkCollision(m_activeType, newRot, m_pieceCol + 1, m_pieceRow)) {
        m_rotation = newRot;
        ++m_pieceCol;
        updateActiveBlockPositions();
        return true;
    }

    return false;
}

// ─────────────────────────────────────────────────────────
//  Piece lifecycle
// ─────────────────────────────────────────────────────────

void Container::spawnPiece()
{
    m_activeType = static_cast<BlockType>(std::rand() % 5);
    m_rotation   = 0;

    const auto& shape = getPieceRotations(m_activeType)[0];
    int maxCol = 0;
    for (const auto& [dr, dc] : shape)
        if (dc > maxCol) maxCol = dc;
    m_pieceCol = (COLS - maxCol - 1) / 2;
    m_pieceRow = 0;

    for (int i = 0; i < 4; ++i) {
        m_activeBlocks[i] = new Block(m_activeType);
        attachChild(m_activeBlocks[i]);
    }

    if (checkCollision(m_activeType, m_rotation, m_pieceCol, m_pieceRow))
        m_gameOver = true;

    updateActiveBlockPositions();
}

void Container::lockPiece()
{
    const auto& shape = getPieceRotations(m_activeType)[m_rotation];

    for (int i = 0; i < 4; ++i) {
        const auto& [dr, dc] = shape[i];
        const int r = m_pieceRow + dr;
        const int c = m_pieceCol + dc;

        if (r < 0) {
            m_gameOver = true;
            delete m_activeBlocks[i];
        } else {
            m_board[r][c] = m_activeBlocks[i];
        }
        m_activeBlocks[i] = nullptr;
    }
}

void Container::hardDrop()
{
    while (!checkCollision(m_activeType, m_rotation, m_pieceCol, m_pieceRow + 1))
        ++m_pieceRow;
    updateActiveBlockPositions();

    lockPiece();
    if (!m_gameOver) {
        clearLines();
        spawnPiece();
        m_tick = 0;
    }
}

// ─────────────────────────────────────────────────────────
//  Line clearing
// ─────────────────────────────────────────────────────────

void Container::clearLines()
{
    int cleared = 0;

    for (int row = ROWS - 1; row >= 0; --row) {

        bool full = true;
        for (int col = 0; col < COLS; ++col) {
            if (m_board[row][col] == nullptr) {
                full = false;
                break;
            }
        }
        if (!full) continue;

        for (int col = 0; col < COLS; ++col) {
            delete m_board[row][col];
            m_board[row][col] = nullptr;
        }
        ++cleared;

        for (int above = row - 1; above >= 0; --above) {
            for (int col = 0; col < COLS; ++col) {
                m_board[above + 1][col] = m_board[above][col];
                if (m_board[above + 1][col]) {
                    m_board[above + 1][col]->setPos(
                        boardLeft() + col * CELL,
                        boardTop() + (above + 1) * CELL);
                }
                m_board[above][col] = nullptr;
            }
        }

        ++row;
    }

    m_score += cleared * 100;
    m_scoreText = L"分数: " + std::to_wstring(m_score);
    SetWindowTextW(GetHWnd(), m_scoreText.c_str());
}

// ─────────────────────────────────────────────────────────
//  Per-frame update (game loop)
// ─────────────────────────────────────────────────────────

void Container::update()
{
    Div::update();
    if (m_gameOver) return;

    ++m_tick;

    // ── Input ────────────────────────────────────────────
    if (m_moveCooldown > 0)
        --m_moveCooldown;

    // Left / Right (with cooldown for controllable auto-repeat)
    if (m_moveCooldown == 0) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            movePiece(-1, 0);
            m_moveCooldown = 6;
        } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            movePiece(1, 0);
            m_moveCooldown = 6;
        }
    }

    // Down arrow — soft drop (no cooldown, gets faster fall)
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        movePiece(0, 1);

    // Up arrow — rotate (rising-edge / single press)
    {
        bool pressed = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
        if (pressed && !m_rotatePressed)
            rotatePiece();
        m_rotatePressed = pressed;
    }

    // Space — hard drop (rising-edge)
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
