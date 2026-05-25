## App 页面类
### App 页面类的主要职责

#### 公有属性与生命周期

* 继承自 `Widget`，作为挂载在 `Root` 下的页面容器
* 默认位置为窗口左上角 `(0, 0)`
* 挂载到 `Root` 后，大小由 `Root` 管理，并同步为根窗口大小
* 通过 `Widget` 的可见性接口参与页面显示与隐藏
* 可以通过 `layout(Layout*)` 挂载一个独立于普通 children 的布局层

#### 页面挂载

* 第一个挂载到同一个 `Root` 下的 `App` 默认显示
* 后续挂载到同一个 `Root` 下的 `App` 默认隐藏
* `Root::mount()` 只负责挂载页面，不触发普通 `Widget::addChild()` 的自动布局
* `App` 下的子控件仍使用普通 `Widget::addChild()` 参与子树布局
* `layout(Layout*)` 挂载的布局层单独存储，不进入普通 children，也不参与父类盒模型自动布局

#### 核心函数

* `App()` – 创建页面容器，初始位置为 `(0, 0)`，大小等待 `Root` 管理
* `App(int w, int h)` – 创建页面容器，并指定初始大小，挂载到 `Root` 后会同步为根窗口大小
* `draw()` – 页面自身不绘制内容，只作为子控件的页面容器
* `layout(Layout* layout)` – 设置当前页面的布局层；每个 App 只保存一个布局层，重复设置会替换旧布局层
* `layout()` – 获取当前页面的布局层
* 从 Root 访问已挂载 App 时应使用 `root.app(0).layout(new Layout())`，因为 `root[0]` 返回的是 `Widget&`

#### 渲染行为

* `App` 的可见性由 `Widget::drawAll()` 和 `Widget::dispatchEvent()` 统一控制
* 隐藏的 `App` 不会绘制自身子树，也不会接收事件
* 挂载在同一个 `Root` 下的所有 `App` 都使用相同的根窗口渲染范围

### App 页面类在库中的意义

* 提供页面级组织能力：Root 可以承载多个 App 页面，并默认只显示第一个页面。
* 分离根挂载与普通布局：Root 的 `mount()` 不再改变页面位置，页面始终从窗口左上角开始。
* 复用 Widget 体系：App 继承自 `Widget`，可以继续嵌套 Div、Label 等普通控件。
