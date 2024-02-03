# Transform

- [Transform](#transform)
  - [Postion](#postion)
    - [Syntax](#syntax)
    - [Example](#example)
  - [Scale](#scale)
    - [Syntax](#syntax-1)
    - [Example](#example-1)
  - [Rotate](#rotate)
    - [Syntax](#syntax-2)
    - [Example](#example-2)
  - [Mirror](#mirror)
    - [Syntax](#syntax-3)
    - [Example](#example-3)
  - [color](#color)
    - [Syntax](#syntax-4)
    - [Example](#example-4)
  - [offset](#offset)
    - [Syntax](#syntax-5)
    - [Example](#example-5)
  - [fill](#fill)
    - [Syntax](#syntax-6)
    - [Example](#example-6)
  - [minkowski](#minkowski)
    - [Syntax](#syntax-7)
    - [Example](#example-7)
  - [hull](#hull)
    - [Syntax](#syntax-8)
    - [Example](#example-8)

[English](./English/transform.md)

## Postion

> transform library

### Syntax

```lua
transform.postion(object, {x, y, z});
```

- first parameter
   - `d3object` type
     - The object on which the operation is performed.
- second parameter
   - `table` type
     - The location of the object.

Translates (moves) the given object along the specified vector, consistent with translate in openscad.

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {0, 0, 5});
```

## Scale

> transform library

### Syntax

```lua
transform.scale(object, {n1, n2, n3});
```

- first parameter
   - `d3object` type
     - The object on which the operation is performed.
- second parameter
   - `table` type
     - Zoom factor.

Scales its child elements using the specified vector, consistent with scale in openscad.

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.scale(cube1, {2, 2, 2});
```

## Rotate

> transform library

### Syntax

```lua
transform.rotate(object, deg_a, v);
-- or
transform.rotate(object, a);
-- or
transform.rotate(object, a, v);
```

- object
   - `d3object` type
     - The object on which the operation is performed.
- deg_a
   - `number` type
     - The specified degree of rotation. If the input is `deg_a`, the input of `a` is no longer accepted.
-a
   - `table` type
     - Specifies rotation in each axis direction, if "a" specifies multiple axes, the rotations are applied in the following order: x, y, z. If `a` is entered, input of `deg_a` is no longer accepted.
-v
   - `table` type
     - Set any axis for rotation of the object.

Rotates its children by "a" degrees about the axis of the coordinate system or about any axis.

### Example

```lua
transform.rotate(cube1, {4, 5, 6});

-- or
transform.rotate(cube1, {1, 2, 3}, {4, 5, 6});

--or
transform.rotate(cube1, 1, {4, 5, 6});
```

## Mirror

> transform library

### Syntax

```lua
transform.mirror(object, {x, y, z});
```

- first parameter
   - `d3object` type
     - The object on which the operation is performed.
- second parameter
   - `table` type
     - The normal vector of the mirror plane intersecting the origin.

Converts a child element to a mirror image of the original element, as if it were a mirror image seen through a plane that intersects the origin.
In [OpenScad](https://en.wikibooks.org/wiki/OpenSCAD_User_Manual/Transformations#mirror)
Introduction to mirror in .

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {0, 0, 5});
transform.mirror(cube1, {-20, -20, -25});
```

## color

> transform library

### Syntax

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

- first parameter
   - `d3object` type
     - The object on which the operation is performed.
-colorname
   - `string` type
     - Specify color name
-rgb
   - `table` type
     - Use rgb to describe color, specify its value in this table.
-rgba
   - `table` type
     - Use rgba to describe color, specify its value in this table.

Displays the object using the specified RGB color + alpha value.

### Example

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

### Syntax

```lua
transform.offset(objects, r);
```

- objects
   - `table` type
     - The object collection of the operation, the object type can be d3object or user_define_obj (need to submit and run user_obj.code(obj))
-r
   - `number` type
     - Offset of the polygon. When negative, the polygon is offset inwards. R specifies the radius of the circle that rotates around the contour (inner or outer). This mode produces rounded corners.

Offset generates a new 2D interior or exterior profile from an existing profile.

### Example

```lua
offset1 = transform.offset({cube1}, 1);
```

## fill

### Syntax

```lua
transform.fill(objects);
```

- objects
   - `table` type
     - The object collection of the operation, the object type can be d3object or user_define_obj (need to submit and run user_obj.code(obj))

Fill removes holes in polygons without changing the outline. For convex polygons, the result is the same as hull().

### Example

```lua
fill1 = transform.fill({cube1});
```

## minkowski

### Syntax

```lua
transform.minkowski(objects);
```

- objects
   - `table` type
     - The object collection of the operation, the object type can be d3object or user_define_obj (need to submit and run user_obj.code(obj))

### Example

```lua
minkowski1 = transform.minkowski({cube1, cube2});
```

## hull

### Syntax

```lua
transform.hull(objects);
```

- objects
   - `table` type
     - The object collection of the operation, the object type can be d3object or user_define_obj (need to submit and run user_obj.code(obj))

### Example
```lua
hull1 = transform.hull({cube1});
```
