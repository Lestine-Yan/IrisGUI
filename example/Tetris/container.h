#pragma once

#include "Div.h"
#include "block.h"

namespace IrisGUI {

class Container : public Div {
public:
    Container(const std::string& className, std::wstring& scoreText);

    void draw() override;
    void update() override;

protected:
    // ── Board constants ──────────────────────────────────────────
    static constexpr int COLS = 10;
    static constexpr int ROWS = 20;
    static constexpr int CELL = 48;
    static constexpr int DROP_INTERVAL = 30;  

    // ── Board state ──────────────────────────────────────────────
    Block* m_board[ROWS][COLS] = {};

    // ── Active (falling) piece ───────────────────────────────────
    Block*  m_activeBlocks[4] = {};  
    BlockType m_activeType = BlockType::I;
    int     m_rotation = 0;         
    int     m_pieceCol = 0;          
    int     m_pieceRow = 0;          

    // ── Timing ───────────────────────────────────────────────────
    int m_tick = 0;

    // ── Input state (cooldowns / edge detection) ─────────────────
    int  m_moveCooldown  = 0;
    bool m_rotatePressed  = false;
    bool m_dropPressed    = false;

    // ── Game state ───────────────────────────────────────────────
    bool           m_gameOver  = false;
    int            m_score     = 0;
    std::wstring&  m_scoreText;        

    // ── Internal helpers ─────────────────────────────────────────
    void   spawnPiece();
    bool   checkCollision(BlockType type, int rot, int col, int row) const;
    bool   movePiece(int dcol, int drow);
    bool   rotatePiece();
    void   lockPiece();
    void   clearLines();
    void   hardDrop();
    void   updateActiveBlockPositions();

    int    boardLeft() const;
    int    boardTop()  const;
};

} // namespace IrisGUI
