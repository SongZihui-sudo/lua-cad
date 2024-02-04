# 变换

- [变换](#变换)
  - [设置位置](#设置位置)
    - [用法](#用法)
    - [例子](#例子)
  - [缩放](#缩放)
    - [用法](#用法-1)
    - [例子](#例子-1)
  - [旋转](#旋转)
    - [用法](#用法-2)
    - [例子](#例子-2)
  - [镜像](#镜像)
    - [用法](#用法-3)
    - [例子](#例子-3)
  - [颜色](#颜色)
    - [用法](#用法-4)
    - [例子](#例子-4)
  - [offset](#offset)
    - [用法](#用法-5)
    - [例子](#例子-5)
  - [fill](#fill)
    - [用法](#用法-6)
    - [例子](#例子-6)
  - [minkowski](#minkowski)
    - [用法](#用法-7)
    - [例子](#例子-7)
  - [hull](#hull)
    - [用法](#用法-8)
    - [例子](#例子-8)

[English](./English/transform.md)

## 设置位置

> transform 库

### 用法

```lua
transform.postion(object, {x, y, z});
```

- 第一个参数
  - `d3object` 类型
    - 进行操作的对象。
- 第二个参数
  - `table` 类型
    - 对象的位置。

沿指定向量平移（移动）给定对象，与 openscad 中的 translate 一致。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {0, 0, 5});
```

## 缩放

> transform 库

### 用法

```lua
transform.scale(object, {n1, n2, n3});
```

- 第一个参数
  - `d3object` 类型
    - 进行操作的对象。
- 第二个参数
  - `table` 类型
    - 缩放倍数。

使用指定的向量缩放其子元素，与 openscad 中的 scale 一致。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.scale(cube1, {2, 2, 2});
```

## 旋转

> transform 库

### 用法

```lua
transform.rotate(object, deg_a, v);
-- or
transform.rotate(object, a);
-- or
transform.rotate(object, a, v);
```

- object
  - `d3object` 类型
    - 进行操作的对象。
- deg_a
  - `number` 类型
    - 指定的旋转度数。如果输入的 `deg_a`，则不在接受 `a` 的输入。
- a
  - `table` 类型
    - 指定在各个轴方向上的旋转，如果“a”指定多个轴，则按以下顺序应用旋转：x、y、z。 如果输入的 `a`，则不在接受 `deg_a` 的输入。
- v
  - `table` 类型
    - 设置对对象旋转的任意轴。

围绕坐标系的轴或围绕任意轴将其子级旋转“a”度。

### 例子

```lua
transform.rotate(cube1, {4, 5, 6});

-- or
transform.rotate(cube1, {1, 2, 3}, {4, 5, 6});

--or
transform.rotate(cube1, 1, {4, 5, 6});
```

## 镜像

> transform 库

### 用法

```lua
transform.mirror(object, {x, y, z});
```

- 第一个参数
  - `d3object` 类型
    - 进行操作的对象。
- 第二个参数
  - `table` 类型
    - 与原点相交的镜像平面的法线向量。

将子元素转换为原始元素的镜像，就好像它是通过与原点相交的平面看到的镜像一样。  
在 [OpenScad](https://en.wikibooks.org/wiki/OpenSCAD_User_Manual/Transformations#mirror)
中对 mirror 的介绍。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {0, 0, 5});
transform.mirror(cube1, {-20, -20, -25});
```

## 颜色

> transform 库

### 用法

```lua
transform.color(object, "colorname");

--or
transform.color(object, "colorname", alpha);

--or
transform.color(object, {r, g, b});

-- or
transform.color(object, {r, g, b}, alpha);

--or
transform.color(object, {r, g, b, a});

-- or
transform.color(object, {r, g, b, a}, alpha);
```

- 第一个参数
  - `d3object` 类型
    - 进行操作的对象。
- colorname
  - `string` 类型
    - 指定颜色名
- rgb
  - `table` 类型
    - 采用 rgb 来描述颜色，在这个 table 中指明其值。
- rgba
  - `table` 类型
    - 采用 rgba 来描述颜色，在这个 table 中指明其值。

使用指定的 RGB 颜色 + alpha 值显示对象。

### 例子

```lua
transform.color(cube1, "xxx");

-- or
transform.color(cube1, "xxx", 1);

--or
transform.color(cube1, {1,2,3}, 1);

-- or
transform.color(cube1, {1,2,3,4}, 1);

```

## offset

### 用法

```lua
transform.offset(objects, r);
```

- objects
  - `table` 类型
    - 操作的对象集合, 对象类型可为 d3object 或 user_define_obj (需要提交运行 user_obj.code(obj) )
- r
  - `number` 类型
    - 多边形的偏移量。 当为负值时，多边形向内偏移。 R 指定围绕轮廓（内部或外部）旋转的圆的半径。 此模式会产生圆角。

偏移从现有轮廓生成新的二维内部或外部轮廓。

### 例子

```lua
offset1 = transform.offset({cube1}, 1);
```

## fill

### 用法

```lua
transform.fill(objects);
```

- objects
  - `table` 类型
    - 操作的对象集合，对象类型可为 d3object 或 user_define_obj (需要提交运行 user_obj.code(obj) )

填充可删除多边形中的孔洞而不改变轮廓。 对于凸多边形，结果与 hull() 相同。  

### 例子

```lua
fill1 = transform.fill({cube1});
```

## minkowski

### 用法

```lua
transform.minkowski(objects);
```

- objects
  - `table` 类型
    - 操作的对象集合，对象类型可为 d3object 或 user_define_obj (需要提交运行 user_obj.code(obj) )

### 例子

```lua
minkowski1 = transform.minkowski({cube1, cube2});
```

## hull

### 用法

```lua
transform.hull(objects);
```

- objects
  - `table` 类型
    - 操作的对象集合，对象类型可为 d3object 或 user_define_obj (需要提交运行 user_obj.code(obj) )

### 例子
```lua
hull1 = transform.hull({cube1});
```
