# 全局函数

- [全局函数](#全局函数)
  - [Code](#code)
    - [用法](#用法)
    - [例子](#例子)
  - [export](#export)
    - [用法](#用法-1)
    - [例子](#例子-1)
  - [include](#include)
    - [用法](#用法-2)
    - [例子](#例子-2)
  - [import](#import)
    - [用法](#用法-3)
    - [例子](#例子-3)
  - [lua-cad 的附加库路径](#lua-cad-的附加库路径)
  - [全局变量](#全局变量)

[English](./English/gloal_function.md)

## Code

### 用法

```lua
code(object)
```

- object
  - `d3object` 类型
    - 要查看的对象

返回给定对象的 openscad 代码。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {10, 10, 10});
print(code(cube1));
```

## export

### 用法

```lua
export("filepath", object);

-- or
export("filepath", "code");

```

- filepath
  - `string` 类型
    - 指明导出文件的路径
- object
  - `d3object` 类型
    - 指明要导出的对象，指定了 object，则不在接受 object。
- code
  - `string` 类型
    - 指明要导出的字符串，指定了 code 则不在接受 object。

导出指定的对象或字符串到指定的 openscad 代码文件。

### 例子

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {10, 10, 10});
export("export.scad", cube1);

-- or
export("export.scad", code(cube1));
```

## include

### 用法

```lua
include("include_path")
```

- include_path
  - `string` 类型
    - 指明要包含的 openscad 文件的路径

包含指定的 openscad 文件，返回一个字符串。

### 例子

```lus
include_hole = include("hole.scad");
```

## import

### 用法

```lua
import("import_path")
```
- import_path
  - `string` 类型
    - 指明要包含的 stl 文件的路径

导入指定的 stl 文件，返回一个字符串。

### 例子

```lus
import_obj = include("obj.stl");
```

## lua-cad 的附加库路径

./ = lua-cad 所处路径
- ./lua-cad/
- /usr/local/lua-cad/

## 全局变量

```lua
output_mode = string
```
这个变量，设置当前程序的输出格式，可选参数为 `openscad` 等。  

可选参数:  
| output_mode |
| ----- |
| openscad |
| .... |
