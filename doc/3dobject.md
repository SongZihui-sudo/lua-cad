# 3d 对象
- [3d 对象](#3d-对象)
  - [立方体](#立方体)
    - [用法](#用法)
    - [例子](#例子)
  - [圆柱体](#圆柱体)
    - [用法](#用法-1)
    - [例子](#例子-1)
  - [球体](#球体)
    - [用法](#用法-2)
    - [例子](#例子-2)
  - [多面体](#多面体)
    - [用法](#用法-3)
    - [例子](#例子-3)

[English](./English/3dobject.md)

## 立方体

> d3object 库  

### 用法

```lua
d3object.cube( { x, y, z }, true/false );
```
- 第一个参数
  - `table` 类型
    - 立方体的长宽高。
- 第二个参数
  - `boolean` 类型
    - true  立方体在 (0, 0, 0) 的中心，如果通过 `transform.postion` 指明了对象的 `3d 对象` 所处位置，那么它在这个点的中心。
    - false (默认) 立方体底面 ( xoy 平面第一象限 (0, 0) ) 一个角在 (0, 0, 0), 如果通过 `transform.postion` 指明了对象的 `3d 对象` 所处位置，那么它底面一角这个点。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
-- or
cube2 = d3object.cube({20, 20, 20}, false);
```

## 圆柱体

> d3object 库  

### 用法

```lua
d3object.cylinder({ h = number, r = number, r1 = number, r2 = number, d = number, d1 = number, d2 = number }, true/false );
```

- h
  - `number` 类型
    - 指明圆柱体的高
- r
  - `number` 类型
    - 指明圆柱体的半径，如果输入了参数 `r` ，则不再接受参数 `r1, r2, d1, d2`。
- d
  - `number` 类型
    - 指明圆柱体的直径，如果输入了参数 `d` ，则不再接受参数 `r1, r2, d1, d2`。
- r1
  - `number` 类型
    - 指明圆柱体的顶面半径。如何输入了参数 `r1`，会接着去读 `r2`, 不在接受参数 `r, d, d1, d2`。
- r2
  - `number` 类型
    - 指明圆柱体的底面半径。如果输入了参数 `r2`， 不在接受参数 `r, d, d1, d2`。
- d1
  - `number` 类型
    - 指明圆柱体的顶面直径。如何输入了参数 `d1`，会接着去读 `d2`, 不在接受参数 `r, d, r1, r2`。
- d2
  - `number` 类型
    - 指明圆柱体的底面直径。如何输入了参数 `d2`， 不在接受参数 `r, d, r1, r2`。
- 最后一个参数
  - `boolean` 类型
    - true  圆柱体在 (0, 0, 0) 的中心，如果通过 `transform.postion` 指明了对象的 `3d 对象` 所处位置，那么它在这个点的中心。
    - false (默认) 圆柱体底面 ( xoy 平面第一象限 (0, 0) ) 一个角在 (0, 0, 0), 如果通过 `transform.postion` 指明了对象的 `3d 对象` 所处位置，那么它底面一角这个点。

### 例子

```lua
local cylinder1 = d3object.cylinder({h = 1,  r = 10}, true );
-- or
local cylinder2 = d3object.cylinder({h = 1,  d = 20}, false );
-- or
local cylinder3 = d3object.cylinder({h = 1,  r1 = 10, r2 = 20}, true );
-- or
local cylinder4 = d3object.cylinder({h = 1,  d1 = 20, d2 = 40}, false );
```

## 球体

> d3object 库  

### 用法

```lua
d3object.sphere({r = number, d = number});
```

- r
  - `number` 类型
    - 指明球体的半径，输入了 `r`， 就不在接受参数 `d`。
- d
  - `number` 类型
    - 指明球体的直径，输入了 `d`，就不再接收参数 `r`。

### 例子

```lua
sphere1 = d3object.sphere({ r = 10 });
-- or
sphere2 = d3object.sphere({ d = 20 });
```

## 多面体

> d3object 库  

### 用法

```lua
d3object.polyhedron({{x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3},........},
    {{index1, index2, index3}, {index1, index3, index4, index2} ............});
```

- 第一个参数 points
  - `table` 类型
    - 这个表是一个二维数组，每一个 `{x, y, z}` 表示一个点的坐标。
- 第二个参数 faces
  - `table` 类型
    - 这个表是一个二维数组，每一个 `{index1, index2, index3}` 中的 `index` 是前面 `points` 表中点的下标，这样的一个 `table` 表示一个面包含的点的集合。

### 例子
```lua
--[[
@description: arg1 points, arg2 faces
@return {*}
--]]
polyhedron1 = d3object.polyhedron({{10, 10, 0}, {10, -10, 0}, {-10, -10, 0}, {-10, 10, 0}}, {{0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, {1, 0, 3}, {2, 1, 3}});
```
