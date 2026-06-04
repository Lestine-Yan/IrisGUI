## Link 跳转控件类
### Link 跳转控件类的主要职责

#### 公有属性与生命周期

* 继承自 `Div`，拥有 Div 的容器绘制、className 样式解析和 Widget 基础控件属性
* 保存目标 App 索引，用于点击后切换当前显示的页面
* 可以作为普通 App 子控件挂载，也可以放在 `App::layout()` 的布局层内

#### 核心函数

* `Link(std::size_t appIndex, int w, int h)` – 创建跳转控件，并指定目标 App 索引和初始大小
* `Link(const std::string& className, std::size_t appIndex, int w, int h)` – 创建跳转控件，并通过 className 初始化样式和尺寸，例如 `new Link("w-100 h-100", 1)`
* `Link(const std::string& className, const std::wstring& text, std::size_t appIndex, int w, int h)`创建跳转控件，设置文本，通过 className 初始化样式和尺寸
* `onMouseDown(const ExMessage& msg)` – 捕获左键点击并执行 App 切换

#### 点击行为

* Link 的点击范围由 `Widget::containsPoint()` 判定，即控件自身渲染区域的宽高范围
* 当收到鼠标左键按下事件时，Link 会查找当前所属 App 和 Root
* 如果目标索引有效且对应的是 App，当前 App 会隐藏，目标 App 会显示
* 如果目标索引无效、目标不是 App、或目标就是当前 App，则不执行切换

#### Layout 内点击

* 当 Link 位于 `App::layout()` 内时，Root 会先把事件分发给可见 App 的 Layout 子控件
* 因此 Layout 内的 Link 可以在普通 App 内容之前捕获点击，适合导航栏、状态栏等覆盖层场景

### Link 跳转控件类在库中的意义

* 提供页面切换能力：用户可以用声明式控件完成 App 之间的显示切换。
* 复用 Div 样式体系：Link 可以直接使用 `w-N`、`h-N`、`bg-*`、`round-N` 等 className token。
* 适配布局层：Link 可以放入普通 App 内容，也可以放入最后渲染的 Layout 中作为导航入口。
