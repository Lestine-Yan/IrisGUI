## Root 根控件类
### Root 根控件类的主要职责

#### 公有属性与生命周期

* 继承自 `Widget`，作为应用中所有控件的根节点
* 根控件位置固定从窗口左上角 `(0, 0)` 开始；未显式指定窗口大小时，窗口大小默认为 Root 的 `ax()` 和 `ay()`
* 使用 `WidgetStyle` 控制根区域背景颜色
* 挂载在 Root 下的 `App` 页面会被同步为根窗口大小
* 通过 `end()` 标记声明阶段结束，并开始渲染与事件循环

#### 控件挂载

* `mount(Widget*)` – 将控件挂载到 Root 子树下，不触发 `Widget::addChild()` 的自动布局，返回 Root 自身以支持链式声明
* `app(std::size_t index)` – 按 Root 直接子控件下标获取 `App` 引用，便于调用 `root.app(0).layout(new Layout())`
* `appCount()` – 获取当前挂载在 Root 下的 `App` 数量
* 第一个挂载到同一个 Root 下的 `App` 默认显示，后续挂载的 `App` 默认隐藏
* `end()` 调用后不再接受新的控件挂载，确保控件树在声明阶段只处理一次
* 挂载到 Root 下的控件会随控件树析构而释放，通常应使用 `new` 创建后交给 Root 管理

#### 核心函数

* `Root(const std::wstring& title)` – 创建根控件，窗口大小在 `end()` 时使用 Root 的 `ax()` 和 `ay()` 自动确定
* `Root(int w, int h, const std::wstring& title)` – 创建根控件，并显式指定窗口大小和标题
* `draw()` – 绘制根背景
* `mount(Widget* child)` – 声明并挂载一个子控件
* `app(std::size_t index)` – 获取指定下标的 App；`root[0]` 的静态类型是 `Widget&`，需要使用 `root.app(0)` 才能直接访问 App 专属接口
* `appCount()` – 获取 Root 下的 App 数量
* `end()` – 结束声明阶段，初始化 EasyX 窗口并进入主循环
* `isEnded()` – 判断声明阶段是否已经结束

#### 渲染行为

* `end()` 会从 Root 开始处理事件、更新状态并渲染控件树
* 渲染循环使用 EasyX 批量绘制，在后台缓冲区完成清屏和绘制后再统一刷新，减少画面闪烁
* 事件分发复用 `Widget::dispatchEvent(msg)`，从根节点向命中的子控件传递
* 普通内容事件分发前，Root 会先将事件分发给可见 App 的 Layout 子控件，使 Layout 内的 `Link` 可以优先响应
* 状态更新复用 `Widget::updateAll()`，从根节点向下遍历所有子控件
* 绘制复用 `Widget::drawAll()`，先绘制 Root 背景，再递归绘制所有子控件
* 普通控件绘制完成后，`Root::end()` 会最后绘制可见 App 上独立挂载的 `Layout`

### Root 根控件类在库中的意义

* 提供统一入口：用户只需要创建 Root、声明控件并调用 `end()`，即可启动界面渲染。
* 支持声明式组织：控件集中挂载在 Root 下，接近 HTML 中由根节点承载页面结构的方式。
* 复用 Widget 体系：Root 不重复实现控件树遍历，而是使用 `Widget` 已有的更新、绘制和事件分发能力。
* 便于扩展：后续布局容器、样式声明和更接近 CSS 的属性系统都可以建立在 Root 控件树之上。
