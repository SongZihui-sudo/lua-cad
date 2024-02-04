# 基准

- [基准](#基准)
  - [方法](#方法)
    - [d3object.datum](#d3objectdatum)
      - [用法](#用法)
      - [例子](#例子)
    - [relative](#relative)
      - [用法](#用法-1)
      - [例子](#例子-1)
    - [distance](#distance)
      - [用法](#用法-2)
      - [例子](#例子-2)
    - [angle](#angle)
      - [用法](#用法-3)
      - [例子](#例子-3)
    - [to\_table](#to_table)
      - [用法](#用法-4)
      - [例子](#例子-4)


[English](./English/datym.md)   

## 方法

### d3object.datum

#### 用法

```lua
d3object.datum(object, index);
```

- object
  - `d3object` 类型
    - 要获取基准面的对象。
- index
  - `int` 类型，基准面索引
    - 返回指定的基准面。

返回给定对象的基准面向量。

#### 例子

```lua
print("-------------- cylinder --------------")
cylinder1 = d3object.cylinder({h = 10, r = 5}, false);
datum1 = d3object.datum(cylinder1, 1);
print("x: " .. datum.to_table(datum1).x);
print("y: " .. datum.to_table(datum1).y);
print("z: " .. datum.to_table(datum1).z);
print(code(cylinder1));

print("-------------- polyhedron --------------")
polyhedron1 = d3object.polyhedron({{10, 10, 0}, {10, -10, 0}, {-10, -10, 0}, {-10, 10, 0}},
{{0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, {1, 0, 3}, {2, 1, 3}})
datum2 = d3object.datum(polyhedron1, 1);
print("x: " .. datum.to_table(datum2).x);
print("y: " .. datum.to_table(datum2).y);
print("z: " .. datum.to_table(datum2).z);
print(code(polyhedron1));

print("-------------- cube --------------")
cube1 = d3object.cube({10, 10, 10}, false);
datum3 = d3object.datum(cube1, 1);
print("x: " .. datum.to_table(datum3).x);
print("y: " .. datum.to_table(datum3).y);
print("z: " .. datum.to_table(datum3).z);
print(code(cube1));

print("-------------- sphere --------------")
sphere1 = d3object.sphere({r = 10});
datum4 = d3object.datum(sphere1, 3);
print("x: " .. datum.to_table(datum4).x);
print("y: " .. datum.to_table(datum4).y);
print("z: " .. datum.to_table(datum4).z);
print(code(sphere1));
```

### relative

#### 用法

```lua
datum.relative(darum_obj, "direction", distance);
```

- darum_obj
  - `datum` 类型
    - 给出当前相对的基准
- direction
  - `string` 类型
    - 指出方向
- distance
  - `number` 类型
    - 指出距离

返回一个在给定方向上与该基准距离指定大小的基准。

#### 例子
```lua
datum5 = datum.relative(datum4, "x", 10);
print("x: " .. datum.to_table(datum5).x);
print("y: " .. datum.to_table(datum5).y);
print("z: " .. datum.to_table(datum5).z);
```

### distance

#### 用法

```lua
datum.distance(darum_obj, {x, y, z});
```

- darum_obj
  - `datum` 类型
    - 给出当前相对的基准
- {x, y, z}
  - `table` 类型
    - 给出要计算距离的向量

计算当前基准与给定向量间的距离。

#### 例子
```lua
dis = datum.distance(datum4, {1, 2, 3});
print("distance: " .. dis);
```

### angle

#### 用法

```lua
datum.angle(datum4, {x, y, z});
```

- darum_obj
  - `datum` 类型
    - 给出当前相对的基准
- {x, y, z}
  - `table` 类型
    - 给出要计算角度的向量

计算当前基准与给定向量，这里两个向量间的夹角。

#### 例子

```lua
angle = datum.angle(datum4, {1, 2, 3});
print("angle: " .. angle);
```

### to_table

#### 用法

```lua
datum.to_table(datum_obj)
```

- datum_obj
  - `datum` 对象
    - 要转换的对象。

将 datum 转换为一个 table。

#### 例子

```lua
cylinder1 = d3object.cylinder({h = 10, r = 5}, false);
datum1 = d3object.datum(cylinder1, 1);
print("x: " .. datum.to_table(datum1).x);
print("y: " .. datum.to_table(datum1).y);
print("z: " .. datum.to_table(datum1).z);
```
