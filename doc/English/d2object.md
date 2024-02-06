# 2D objects

- [2D objects](#2d-objects)
  - [square](#square)
    - [Usage](#usage)
    - [Example](#example)
  - [circle](#circle)
    - [Usage](#usage-1)
    - [Example](#example-1)
  - [Polygon](#polygon)
    - [Usage](#usage-2)
    - [Example](#example-2)
  - [linear\_extrude](#linear_extrude)
    - [Usage](#usage-3)
    - [Example](#example-3)
  - [rotate\_extrude](#rotate_extrude)
    - [Usage](#usage-4)
    - [Example](#example-4)

## square

> d2object

### Usage

```lua
d2object.square({w, l}, true/false);
```

- first parameter
   - `table` type
     - Length and width of square
- second parameter
   - `boolean` type
     - If true, the center of the square is at the origin (0, 0).
     - If false, then the square is in the corner of the first quadrant.

### Example

```lua
local square1 = d2object.square({10, 10}, false);
```

## circle

> d2object

### Usage

```lua
d2object.circle({d = number | r = number});
```

- first parameter
   - `table` type
     - `r` specifies the radius of the circle
     - `d` specifies the diameter of the circle

### Example

```lua
local circle1 = d2object.circle({d = 10});

-- or
local circle2 = d2object.circle({r = 10});
```

## Polygon

> d2object

### Usage

```lua
d2object.polygon( points = {{x1, y1}, {x2, y2}, .........}, paths = {{p1, p2, p3}, {p1, p2, p4}, . ............});
```

- points
   - `table` type
     - Specify the point coordinates of the polygon, {x, y}
- paths
   - `table` type
     - Specifies the point passed by path, type `int`

### Example

```lua
local polygon1 = d2object.polygon({{0, 0}, {100, 0}, {130, 50}, {30, 50}}, {{0, 1, 2, 3}, {2, 3}, {1}});
```

## linear_extrude

> d2object

### Usage

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

Linear extrusion is an operation that takes a 2D object as input and produces a 3D object as the result.

### Example

```lua
d2object.linear_extrude(circle2, {
     height = 10,
     center = true,
     convexity = 10,
     twist = 2,
     slices = 20,
     scale=1.0
});

print(code(circle2))
```

## rotate_extrude

> d2object

### Usage

```lua
d2object.rotate_extrude(circle2, {
     angle = number,
     convexity = number
});
```

Rotational extrusion rotates a 2D shape about the Z-axis, forming a solid with rotational symmetry.

### Example

```lua
d2object.rotate_extrude(circle2, {
     angle = 360,
     convexity = 2
});

print(code(circle2))
```

[openscad documentation](https://en.wikibooks.org/wiki/OpenSCAD_User_Manual/Using_the_2D_Subsystem#linear_extrude) on rotate_extrude and linear_extrude.
