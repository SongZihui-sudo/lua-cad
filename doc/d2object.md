# 2D 对象

- [2D 对象](#2d-对象)
  - [正方形](#正方形)
    - [用法](#用法)
    - [例子](#例子)
  - [圆](#圆)
    - [用法](#用法-1)
    - [例子](#例子-1)
  - [多边形](#多边形)
    - [用法](#用法-2)
    - [例子](#例子-2)
  - [linear\_extrude](#linear_extrude)
    - [用法](#用法-3)
    - [例子](#例子-3)
  - [rotate\_extrude](#rotate_extrude)
    - [用法](#用法-4)
    - [例子](#例子-4)

[English](./English/d2object.md)

## 正方形

> d2object

### 用法

```lua
d2object.square({w, l}, true/false);
```

- 第一个参数
  - `table` 类型
    - 正方形的长与宽
- 第二个参数
  - `boolean` 类型
    - 如果为 true，那么正方形的的中心在原点(0, 0).
    - 如果为 false, 那么正方形在第一象限的一角.

### 例子

```lua
local square1 = d2object.square({10, 10}, false);
```

## 圆

> d2object

### 用法

```lua
d2object.circle({d = number | r = number});
```

- 第一个参数
  - `table` 类型
    - `r` 指定圆的半径
    - `d` 指定圆的直径

### 例子

```lua
local circle1 = d2object.circle({d = 10});

-- or
local circle2 = d2object.circle({r = 10});
```

## 多边形

> d2object

### 用法

```lua
d2object.polygon( points = {{x1, y1}, {x2, y2}, .........}, paths = {{p1, p2, p3}, {p1, p2, p4}, .............});
```

- points
  - `table` 类型
    - 指定多边形的点坐标，{x, y}
- paths
  - `table` 类型
    - 指定 path 所经过的点，类型的 `int`

### 例子

```lua
local polygon1 = d2object.polygon({{0, 0}, {100, 0}, {130, 50}, {30, 50}}, {{0, 1, 2, 3}, {2, 3}, {1}});
```

## linear_extrude

> d2object

### 用法

```lua
d2object.linear_extrude(circle2, {
    height = number,
    center = boolean,
    convexity = number,
    twist = number,
    slices = number,
    scale = number
});
```

线性拉伸是一种将 2D 对象作为输入并生成 3D 对象作为结果的操作。

### 例子

```lua
d2object.linear_extrude(circle2, {
    height = 10,
    center = true,
    convexity = 10,
    twist = 2,
    slices = 20,
    scale = 1.0
});

print(code(circle2))
```

## rotate_extrude

> d2object

### 用法

```lua
d2object.rotate_extrude(circle2, {
    angle = number,
    convexity = number
});
```

旋转挤压围绕 Z 轴旋转 2D 形状，形成具有旋转对称性的实体。

### 例子

```lua
d2object.rotate_extrude(circle2, {
    angle = 360,
    convexity = 2
});

print(code(circle2))
```

关于 rotate_extrude 和 linear_extrude 的 [openscad 文档](https://en.wikibooks.org/wiki/OpenSCAD_User_Manual/Using_the_2D_Subsystem#linear_extrude)。
