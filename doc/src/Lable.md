## Label 文本标签类
### Label 文本标签类的主要职责

#### 公有属性与生命周期

* 继承自 `Widget`，拥有位置（x, y）、大小（width, height）、是否可见（visible）等基础控件属性
* 保存标签文本内容（text），用于在控件区域内显示静态文本
* 使用 `WidgetStyle` 控制背景颜色、边框颜色、边框宽度、文字颜色、字体大小、圆角、外边距和内边距

#### 核心函数

* `Label(int x, int y, int w, int h, const std::wstring& text)` – 创建文本标签，并初始化位置、大小和文本内容
* `draw()` – 绘制标签背景、边框和文本内容
* `setText(const std::wstring& text)` – 设置标签显示的文本
* `text()` – 获取当前标签文本

#### 绘制行为

* 根据 `WidgetStyle::bgColor` 绘制标签背景
* 根据 `WidgetStyle::borderColor` 和 `WidgetStyle::borderWidth` 绘制边框
* 根据 `WidgetStyle::borderRadius` 绘制普通矩形或圆角矩形
* 根据 `WidgetStyle::padding` 计算文本绘制区域，使文本与边框保持内边距
* 默认使用黑体绘制中文文本，并启用抗锯齿以提升显示效果

#### 样式支持

* `textColor` – 控制文本颜色
* `fontSize` – 控制文本字号
* `padding` – 控制文本与标签边缘之间的距离
* `margin` – 作为布局系统使用的外边距属性，标签自身绘制时不直接消耗
* `borderRadius` – 控制标签背景和边框的圆角大小

### Label 文本标签类在库中的意义

* 提供基础文本显示能力：Label 是最简单的可视化控件之一，用于显示说明文字、标题、状态文本等内容。
* 复用 Widget 体系：Label 继承自 `Widget`，可以参与控件树管理，并通过根控件的 `drawAll()` 统一绘制。
* 验证样式能力：Label 使用文字颜色、字体大小、内边距、边框和圆角等样式属性，是 `WidgetStyle` 在具体控件中的基础应用示例。
* 便于扩展：后续可以在 Label 基础上继续增加文本对齐、自动换行、省略号截断等文本显示能力。
