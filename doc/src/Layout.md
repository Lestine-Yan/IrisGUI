## Layout 布局层类
### Layout 布局层类的主要职责

#### 公有属性与生命周期

* 继承自 `Widget`，作为挂载在 `App` 上的独立布局层
* 通过 `App::layout(Layout*)` 挂载，不进入 `Widget` 的普通 children 列表
* 每个 `App` 同一时间只保存一个 `Layout`
* 位置固定为 `(0, 0)`，大小由所属 `App` 和 `Root` 的窗口范围同步

#### 挂载行为

* `Layout` 不通过 `addChild()` 挂载到父控件，因此不参与父类盒模型自动布局
* `App::layout(Layout*)` 会替换当前布局层，旧布局层由 `App` 释放
* 传入 `nullptr` 可以清空当前布局层
* `Layout` 自身仍然可以通过普通 `addChild()` 挂载子控件，子控件会使用 `Widget` 的自动布局规则

#### 核心函数

* `Layout()` – 创建布局层，初始位置为 `(0, 0)`，大小等待 `App` 管理
* `Layout(int w, int h)` – 创建布局层，并指定初始大小，挂载到 `App` 后会同步为 App 大小
* `setPos(int x, int y)` – 保持布局层位置为 `(0, 0)`
* `setGeometry(int x, int y, int w, int h)` – 忽略传入的 x、y，只更新宽高并保持 `(0, 0)`
* `draw()` – 布局层自身不绘制内容，只作为子控件的顶层容器

#### 渲染行为

* `Root::end()` 会先绘制 Root、App 和普通 children
* 普通控件绘制完成后，Root 会额外绘制可见 App 的 `Layout`
* 因此 `Layout` 总是在所属 App 的普通子控件之后渲染
* Root 会在普通内容事件分发前先检查可见 App 的 Layout 子控件，因此 Layout 内的 `Link` 可以捕获点击

### Layout 布局层类在库中的意义

* 提供页面级覆盖层：适合放置导航栏、状态栏、血条栏等需要覆盖在页面内容之上的 UI。
* 分离布局职责：普通 children 继续参与盒模型自动布局，Layout 独立存储并最后渲染。
* 复用 Widget 体系：Layout 继承自 `Widget`，可以继续嵌套 Div、Label 等普通控件。
