## Widget 基类
### Widget 基类的主要职责

#### 公有属性与生命周期

* 位置（x, y）、大小（width, height）、是否可见（visible）
* 盒模型外边界（ax, ay），由位置、大小、padding、border 和 margin 计算得到
* 父控件指针（parent）、子控件列表（children）
* 控件样式（Style 结构体，包含颜色、边框、字体等）
* `flex` 布局方向属性，默认纵向排列子控件，启用后横向排列子控件

#### 核心虚函数（多态接口）

* `draw()` – 绘制控件自身（由具体子类重写）
* `handleEvent(ExMessage &msg)` – 处理鼠标/键盘事件（点击、移动、输入等）
* `onMouseDown`, `onMouseUp`, `onMouseMove` – 可选的事件回调虚函数
* `update()` – 更新逻辑（如动画状态、输入框光标闪烁）

#### 控件树管理

* `addChild(Widget*)`, `removeChild(Widget*)` – 添加/移除子控件
* `addChild(Widget*)` 会根据父控件布局方向自动设置子控件位置，并扩大父控件和祖先控件以容纳子控件
* `Layout` 通过 `App::layout()` 独立挂载，不属于普通 children，因此不参与父控件的盒模型自动布局
* `getParent()` – 获取父控件
* `setParent(Widget*)` – 设置父控件（自动更新全局绘制顺序）

#### 工具方法

* `setPos(int x, int y)`, `setSize(int w, int h)`
* `ax()`, `ay()` – 获取控件盒模型在父坐标系中的右/下外边界
* `containsPoint(int px, int py)` – 判断坐标是否在控件区域内
* `setVisible(bool)` – 隐藏/显示控件
* `setStyle(const Style&)` – 应用样式配置
* `setFlex(bool)` – 控制子控件纵向或横向排列

### Widget 基类在库中的意义

* 统一接口：所有控件均继承自 Widget，外部代码可以通过基类指针统一管理多种控件，实现多态绘制与事件传递。
* 简化布局与事件：子控件加入父控件时会自动排列并扩大父控件，主循环只需调用根控件的 `drawAll()` 和 `dispatchEvent(msg)` 即可递归处理所有控件的绘制与交互。
* 易于扩展：新增控件只需继承 `Widget`，并重写 `draw()` 和 `handleEvent()` 等必要虚函数，即可无缝集成到现有框架中。