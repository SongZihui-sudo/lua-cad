# 布尔操作

- [布尔操作](#布尔操作)
  - [或](#或)
    - [用法](#用法)
    - [例子](#例子)
  - [与非](#与非)
    - [用法](#用法-1)
    - [例子](#例子-1)
  - [与](#与)
    - [用法](#用法-2)
    - [例子](#例子-2)

[English](./English/boolean.md)

## 或

> boolean 库

### 用法

```lua
boolean.union({obj1, obj2, obj3,...........});
```

- 第一个参数
  - `table` 类型
    - 表示参数该布尔运算的对象。

`table` 内的对象可以为 `d3object` 也可为 `user_define_obj`。

### 例子

```lua
shoulder_screw1 = $shoulder_screw( "english", 1/2, length = 20 )$;
test.code(shoulder_screw1);
cube1 = d3object.cube({10, 10, 10}, true);
union1 = boolean.union({cube1, shoulder_screw11});
```

## 与非

> boolean 库

### 用法

```lua
boolean.difference({obj1, obj2, obj3,...........});
```

- 第一个参数
  - `table` 类型
    - 表示参数该布尔运算的对象。

`table` 内的对象可以为 `d3object` 也可为 `user_define_obj`。

### 例子

```lua
shoulder_screw1 = $shoulder_screw( "english", 1/2, length = 20 )$;
shoulder_screw1.code(shoulder_screw1);
cylinder1 = d3object.cylinder({h = 10, r = 5}, true);
difference1 = boolean.difference({cylinder1, shoulder_screw1});
```

## 与

> boolean 库

### 用法

```lua
boolean.intersection({obj1, obj2, obj3,...........});
```

- 第一个参数
  - `table` 类型
    - 表示参数该布尔运算的对象。

`table` 内的对象可以为 `d3object` 也可为 `user_define_obj`。

### 例子

```lua
sphere1 = d3object.sphere({h = 10, d = 5});
intersection1 = boolean.intersection({sphere1, shoulder_screw1});
print(code(intersection1));
```
