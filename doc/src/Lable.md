## Label 文本标签类
### Label 文本标签类的主要职责

#### 公有属性与生命周期

* 继承自 `Div`，拥有 `Div` 的容器属性、样式字符串能力和 `Widget` 基础控件属性
* 保存标签文本内容（text），用于在控件区域内显示静态文本
* 使用 `WidgetStyle` 控制背景颜色、边框颜色、边框宽度、文字颜色、字体大小、圆角、外边距和内边距
* 支持通过 `Div` 的 className 写法声明宽高、边距、内边距、背景、边框、圆角和 flex 等样式

#### 核心函数

* `Label(const std::wstring& text, int w, int h)` – 创建文本标签，并初始化大小和文本内容，位置由父控件布局自动管理
* `Label(const std::string& className, const std::wstring& text, int w, int h)` – 创建文本标签，并通过 className 初始化样式和尺寸，例如 `new Label("w-100 h-100", L"hello,world")`
* `Label(int x, int y, int w, int h, const std::wstring& text)` – 兼容旧的手动定位写法，挂载到父控件后坐标会由布局覆盖
* `Label(int x, int y, int w, int h, const std::wstring& text, const std::string& className)` – 创建带初始位置、大小、文本和 className 的标签
* `draw()` – 先复用 `Div::draw()` 绘制背景、边框和圆角，再绘制文本内容
* `setText(const std::wstring& text)` – 设置标签显示的文本
* `text()` – 获取当前标签文本

#### 继承自 Div 的样式能力

* `setClassName(const std::string& className)` – 设置并重新解析样式字符串
* `className()` – 获取当前样式字符串
* `applyClassName(const std::string& className)` – 解析样式字符串，并将结果写入当前控件样式与布局属性
* 支持 `w-N`、`h-N`、`m-N`、`p-N`、`bg-*`、`border-*`、`b-N`、`round-N`、`font-N`、`flex` 等 Div className token

#### 绘制行为

* 背景、边框和圆角由 `Div::draw()` 统一绘制
* 文本绘制在 `Div` 背景之上
* 根据 `WidgetStyle::padding` 计算文本绘制区域，使文本与边框保持内边距
* 根据 `WidgetStyle::textColor` 和 `WidgetStyle::fontSize` 设置文本颜色和字号
* 默认使用黑体绘制中文文本，并启用抗锯齿以提升显示效果

### Label 文本标签类在库中的意义

* 提供基础文本显示能力：Label 是最简单的可视化控件之一，用于显示说明文字、标题、状态文本等内容。
* 复用 Div 体系：Label 继承自 `Div`，可以直接使用 Div 的盒模型绘制、className 样式解析和容器能力。
* 保留文本接口：Label 仍提供 `setText()` 和 `text()`，原有文本显示用法保持可用。
* 便于扩展：后续可以在 Label 基础上继续增加文本对齐、自动换行、省略号截断等文本显示能力。
