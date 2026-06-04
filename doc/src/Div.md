## Div 容器类
### Div 容器类的主要职责

#### 公有属性与生命周期

* 继承自 `Widget`，拥有位置（x, y）、大小（width, height）、是否可见（visible）等基础控件属性
* 作为一个可视化容器，用于绘制带背景、边框和圆角的大盒子，并挂载其他子控件
* 使用 `WidgetStyle` 控制背景颜色、边框颜色、边框宽度、字体大小、圆角、外边距和内边距
* 保存样式字符串（className），用于声明式地批量设置控件样式与部分布局属性

#### 核心函数

* `Div(int w, int h)` – 创建容器，并初始化大小，位置由父控件布局自动管理
* `Div(int x, int y, int w, int h)` – 兼容旧的手动定位写法，挂载到父控件后坐标会由布局覆盖
* `Div(const std::string& className, int w, int h)` – 创建容器，并在初始化时解析样式字符串
* `Div(const std::string& className,int w, int h)` – 创建容器，并在初始化时解析样式字符串
* `Div(const std::string& className, const std::wstring& text, int w, int h)`  – 创建容器，并同时指定初始位置、大小、文本和样式字符串
* `draw()` – 绘制容器背景和边框
* `setClassName(const std::string& className)` – 设置并重新解析样式字符串
* `className()` – 获取当前样式字符串
* `applyClassName(const std::string& className)` – 解析样式字符串，并将结果写入当前控件样式与布局属性

#### 绘制行为

* 根据 `WidgetStyle::bgColor` 绘制容器背景
* 若通过 `bg-[filename.png]` 设置了背景图片且图片已加载，则在背景色之上拉伸绘制背景图
* 根据 `WidgetStyle::borderColor` 和 `WidgetStyle::borderWidth` 绘制边框
* 根据 `WidgetStyle::borderRadius` 绘制普通矩形或圆角矩形
* `Div` 自身不绘制文本，只负责提供可见的容器区域
* 子控件仍通过 `Widget::drawAll()` 递归绘制，因此可以在 `Div` 内继续嵌套其他控件

#### 样式字符串支持

* `font-N` – 设置 `fontSize`
* `w-N` – 设置宽度
* `h-N` – 设置高度
* `flex` – 设置 `flex` 为 `true`，让子控件按当前 `Widget` 逻辑横向排列
* `ml-N` – 设置 `margin.left`
* `my-N` – 同时设置 `margin.top` 和 `margin.bottom`
* `p-N` – 同时设置四个方向的 `padding`
* `bg-name` – 使用预定义颜色名设置背景色，当前支持 `black`、`white`、`red`、`green`、`blue`
* `bg-[r,g,b]` – 使用 `RGB(r, g, b)` 形式设置背景色
* `bg-[filename.png]` – 加载指定图片作为背景，图片会被拉伸至铺满整个容器区域（不含 margin），一个 Div 实例仅存储一张背景图，重复设置会覆盖前一张
* 未知 token、非法数字和格式错误的颜色参数会被忽略，不中断整个解析过程

### Div 容器类在库中的意义

* 提供基础容器能力：Div 是最直接的盒模型容器，可用于承载分组区域、卡片、面板等界面结构。
* 支持声明式样式：通过类似 Tailwind 的字符串快速配置尺寸、间距、背景和布局方向，减少重复的手动 `setStyle()` 调用。
* 复用 Widget 体系：Div 继承自 `Widget`，可以直接参与控件树管理、自动布局、统一绘制和事件分发。
* 便于扩展：后续如果继续增加更多原子样式 token，Div 可以作为声明式样式能力的主要承载组件。
