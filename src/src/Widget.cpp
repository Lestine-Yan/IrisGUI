#include "pch.h"
#include "../include/Widget.h"

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace IrisGUI {

Widget::Widget(int w, int h)
    : m_width(w), m_height(h) {}

Widget::Widget(int x, int y, int w, int h)
    : m_x(x), m_y(y), m_width(w), m_height(h) {}

Widget::~Widget()
{
    if (m_parent)
        m_parent->removeChild(this);

    for (auto* child : m_children)
        delete child;
    m_children.clear();
}

// ── Position & size ──────────────────────────────────────────────────

void Widget::setPos(int x, int y) { m_x = x; m_y = y; }
void Widget::setSize(int w, int h) { m_width = w; m_height = h; }
void Widget::setGeometry(int x, int y, int w, int h)
{
    m_x = x; m_y = y;
    m_width = w; m_height = h;
}

int Widget::ax() const
{
    return m_x + m_width
        + m_style.padding.left + m_style.padding.right
        + m_style.margin.left + m_style.margin.right
        + m_style.borderWidth * 2;
}

int Widget::ay() const
{
    return m_y + m_height
        + m_style.padding.top + m_style.padding.bottom
        + m_style.margin.top + m_style.margin.bottom
        + m_style.borderWidth * 2;
}

int Widget::absX() const
{
    int ax = m_x;
    for (const Widget* p = m_parent; p; p = p->m_parent)
        ax += p->m_x;
    return ax;
}//弃用

int Widget::absY() const
{
    int ay = m_y;
    for (const Widget* p = m_parent; p; p = p->m_parent)
        ay += p->m_y;
    return ay;
}//弃用

// ── Visibility ───────────────────────────────────────────────────────

void Widget::show()  { m_visible = true; }
void Widget::hide()  { m_visible = false; }
void Widget::setVisible(bool v) { m_visible = v; }

// ── Widget tree ──────────────────────────────────────────────────────

void Widget::attachChild(Widget* child)
{
    if (!child) return;
    if (child->m_parent)
        child->m_parent->removeChild(child);

    child->m_parent = this;
    m_children.push_back(child);
}

void Widget::addChild(Widget* child)
{
    if (!child) return;
    if (child->m_parent)
        child->m_parent->removeChild(child);

    if (m_flex) {
        if(m_children.empty()) {
            child->m_x = m_style.margin.left + m_style.padding.left + m_style.borderWidth;
        } else {
            auto it = m_children.end() - 1;
            child->m_x = std::max((*it)->ax(), (m_style.margin.left + m_style.padding.left + m_style.borderWidth));
        }
        child->m_y = m_y + m_style.margin.top + m_style.padding.top + m_style.borderWidth;
    }
    else {
        if(m_children.empty()) {
            child->m_y = m_style.margin.top + m_style.padding.top + m_style.borderWidth;
        } else {
            auto it = m_children.end() - 1;
            child->m_y = std::max((*it)->ay(), (m_style.margin.top + m_style.padding.top + m_style.borderWidth));
        }
        child->m_x = m_x + m_style.margin.left + m_style.padding.left + m_style.borderWidth;
    }

    attachChild(child);

    Widget* current = child;
    for (Widget* parent = this; parent; parent = parent->m_parent) {
        parent->m_width = std::max(
            parent->m_width,
            current->ax() - parent->m_x - parent->m_style.margin.left - parent->m_style.padding.left - parent->m_style.borderWidth);
        parent->m_height = std::max(
            parent->m_height,
            current->ay() - parent->m_y - parent->m_style.margin.top - parent->m_style.padding.top - parent->m_style.borderWidth);
        current = parent;
    }
}

void Widget::removeChild(Widget* child)
{
    if (!child) return;
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        child->m_parent = nullptr;
    }
}//不建议使用，将在未来版本中删除，会导致容器内元素位置混乱

void Widget::setParent(Widget* parent)
{
    if (parent)
        parent->addChild(this);
    else if (m_parent)
        m_parent->removeChild(this);
}//建议在构造函数中直接指定父组件，或使用addChild方法添加到父组件中，不建议直接调用setParent方法，会导致容器内元素位置混乱

// ── Hit testing ──────────────────────────────────────────────────────

bool Widget::containsPoint(int px, int py) const
{
    return px > m_x + m_style.margin.left && px < ax() - m_style.margin.right &&
           py > m_y + m_style.margin.top && py < ay() - m_style.margin.bottom;
}

// ── Event handling ───────────────────────────────────────────────────

void Widget::handleEvent(const ExMessage& msg)
{
    if (!m_visible) return;

    switch (msg.message) {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        onMouseDown(msg);
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        onMouseUp(msg);
        break;
    case WM_MOUSEMOVE:
        onMouseMove(msg);
        break;
    }
}

// ── Dispatch ─────────────────────────────────────────────────────────

void Widget::drawAll()
{
    if (!m_visible) return;
    draw();
    for (auto* child : m_children)
        child->drawAll();
}

void Widget::updateAll()
{
    if (!m_visible) return;
    update();
    for (auto* child : m_children)
        child->updateAll();
}

bool Widget::dispatchEventToChild(const ExMessage& msg)
{
    if (!m_visible) return false;

    bool isMouseEvent = (msg.message == WM_LBUTTONDOWN ||
                         msg.message == WM_LBUTTONUP   ||
                         msg.message == WM_RBUTTONDOWN ||
                         msg.message == WM_RBUTTONUP   ||
                         msg.message == WM_MBUTTONDOWN ||
                         msg.message == WM_MBUTTONUP   ||
                         msg.message == WM_MOUSEMOVE   ||
                         msg.message == WM_MOUSEWHEEL);

    if (isMouseEvent) {
        for (auto it = m_children.rbegin();
             it != m_children.rend(); ++it) {
            if ((*it)->containsPoint(msg.x, msg.y)) {
                (*it)->dispatchEvent(msg);
                return true;
            }
        }
    }

    return false;
}

void Widget::dispatchEvent(const ExMessage& msg)
{
    if (!m_visible) return;
    if (dispatchEventToChild(msg)) return;

    handleEvent(msg);
}

} // namespace IrisGUI
