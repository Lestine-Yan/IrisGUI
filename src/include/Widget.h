#pragma once

#include <vector>
#include <algorithm>
#include <graphics.h>

namespace IrisGUI {

struct WidgetSpacing {
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
};

struct WidgetStyle {
    COLORREF bgColor   = RGB(240, 240, 240);
    COLORREF borderColor = RGB(200, 200, 200);
    int borderWidth    = 1;
    COLORREF textColor = RGB(0, 0, 0);
    int fontSize       = 16;
    int borderRadius   = 0;
    WidgetSpacing margin;
    WidgetSpacing padding;
};

class Widget {
public:
    Widget(int x = 0, int y = 0, int w = 100, int h = 30);
    virtual ~Widget();

    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    // ── Position & size ──────────────────────────────────────────
    void setPos(int x, int y);
    void setSize(int w, int h);
    void setGeometry(int x, int y, int w, int h);

    int x()      const { return m_x; }
    int y()      const { return m_y; }
    int width()  const { return m_width; }
    int height() const { return m_height; }

    int absX() const;
    int absY() const;

    // ── Visibility ───────────────────────────────────────────────
    void show();
    void hide();
    void setVisible(bool v);
    bool isVisible() const { return m_visible; }

    // ── Style ────────────────────────────────────────────────────
    void setStyle(const WidgetStyle& s) { m_style = s; }
    const WidgetStyle& style() const    { return m_style; }

    // ── Widget tree (composite pattern) ──────────────────────────
    void addChild(Widget* child);
    void removeChild(Widget* child);
    void setParent(Widget* parent);

    Widget*       parent()             { return m_parent; }
    const Widget* parent()       const { return m_parent; }
    const std::vector<Widget*>& children() const { return m_children; }

    // ── Hit testing ──────────────────────────────────────────────
    bool containsPoint(int px, int py) const;

    // ── Virtual interface ────────────────────────────────────────
    virtual void draw() = 0;
    virtual void handleEvent(const ExMessage& msg);
    virtual void onMouseDown(const ExMessage& msg) {}
    virtual void onMouseUp(const ExMessage& msg)   {}
    virtual void onMouseMove(const ExMessage& msg) {}
    virtual void update() {}

    // ── Dispatch helpers ─────────────────────────────────────────
    void drawAll();
    void updateAll();
    void dispatchEvent(const ExMessage& msg);

protected:
    int  m_x = 0, m_y = 0;
    int  m_width = 100, m_height = 30;
    bool m_visible = true;
    Widget*              m_parent = nullptr;
    std::vector<Widget*> m_children;
    WidgetStyle          m_style;
};

} // namespace IrisGUI
