# Boolean operations

- [Boolean Operation] (#布尔操作)
  - [or] (#或)
    - [Grammar](#语法)
    - [Example](#例子)
  - [NOT] (#与非)
    - [Grammar](#语法-1)
    - [Example](#例子-1)
  - [AND] (#与)
    - [Grammar] (#语法-2)
    - [Example] (#例子-2)

[English] (./English/boolean.md)

## or

> boolean library

### Syntax

```lua
boolean.union({obj1, obj2, obj3,...........});
```

- The first parameter
  - 'table' type
    - Represents the object of the Boolean operation with the parameters.

The object inside the 'table' can be 'd3object' or 'user_define_obj'.

### Examples

```lua
shoulder_screw1 = $shoulder_screw( "english", 1/2, length = 20 )$;
test.code(shoulder_screw1);
cube1 = d3object.cube({10, 10, 10}, true);
union1 = boolean.union({cube1, shoulder_screw11});
```

## & Non

> boolean library

### Syntax

```lua
boolean.difference({obj1, obj2, obj3,...........});
```

- The first parameter
  - 'table' type
    - Represents the object of the Boolean operation with the parameters.

The object inside the 'table' can be 'd3object' or 'user_define_obj'.

### Examples

```lua
shoulder_screw1 = $shoulder_screw( "english", 1/2, length = 20 )$;
shoulder_screw1.code(shoulder_screw1);
cylinder1 = d3object.cylinder({h = 10, r = 5}, true);
difference1 = boolean.difference({cylinder1, shoulder_screw1});
```

## with

> boolean library

### Syntax

```lua
boolean.intersection({obj1, obj2, obj3,...........});
```

- The first parameter
  - 'table' type
    - Represents the object of the Boolean operation with the parameters.

The object inside the 'table' can be 'd3object' or 'user_define_obj'.

### Examples

```lua
sphere1 = d3object.sphere({h = 10, d = 5});
intersection1 = boolean.intersection({sphere1, shoulder_screw1});
print(code(intersection1));
```