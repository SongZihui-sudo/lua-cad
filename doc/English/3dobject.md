# 3d object
- [3d object](#3d-object)
  - [Cube](#cube)
    - [Usage](#Usage)
    - [Example](#example)
  - [Cylinder](#cylinder)
    - [Usage](#Usage-1)
    - [Example](#example-1)
  - [Sphere](#sphere)
    - [Usage](#Usage-2)
    - [Example](#example-2)
  - [Polyhedron](#polyhedron)
    - [Usage](#Usage-3)
    - [Example](#example-3)

## Cube

> d3object library

### Usage

```lua
d3object.cube( { x, y, z }, true/false );
```
- first parameter
   - `table` type
     - The length, width and height of the cube.
- second parameter
   - `boolean` type
     - true The cube is at the center of (0, 0, 0). If the position of the `3d object` of the object is specified through `transform.postion`, then it is at the center of this point.
     - false (default) The base of the cube (the first quadrant of the xoy plane (0, 0)) has one corner at (0, 0, 0). If the position of the `3d object` of the object is specified through `transform.postion`, then This point on the bottom corner of it.

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
-- or
cube2 = d3object.cube({20, 20, 20}, false);
```

## Cylinder

> d3object library

### Usage

```lua
d3object.cylinder({ h = number, r = number, r1 = number, r2 = number, d = number, d1 = number, d2 = number }, true/false );
```

- h
   - `number` type
     - Specify the height of the cylinder
- r
   - `number` type
     - Specifies the radius of the cylinder. If the parameter `r` is entered, the parameters `r1, r2, d1, d2` are no longer accepted.
- d
   - `number` type
     - Specifies the diameter of the cylinder. If the parameter `d` is entered, the parameters `r1, r2, d1, d2` are no longer accepted.
- r1
   - `number` type
     - Specifies the top radius of the cylinder. How to input parameter `r1`, it will continue to read `r2`, and no longer accept parameters `r, d, d1, d2`.
- r2
   - `number` type
     - Specifies the base radius of the cylinder. If parameter `r2` is entered, parameters `r, d, d1, d2` are no longer accepted.
- d1
   - `number` type
     - Specifies the diameter of the top surface of the cylinder. How to input parameter `d1`, it will continue to read `d2`, and no longer accept parameters `r, d, r1, r2`.
- d2
   - `number` type
     - Specifies the base diameter of the cylinder. How to input parameter `d2`, but no longer accept parameters `r, d, r1, r2`.
- last parameter
   - `boolean` type
     - true The cylinder is centered at (0, 0, 0). If the position of the `3d object` of the object is specified through `transform.postion`, then it is at the center of this point.
     - false (default) The base of the cylinder (the first quadrant of the xoy plane (0, 0)) has a corner at (0, 0, 0), if the position of the `3d object` of the object is specified through `transform.postion`, Then this is the point on the bottom corner.

### Example

```lua
local cylinder1 = d3object.cylinder({h = 1, r = 10}, true );
-- or
local cylinder2 = d3object.cylinder({h = 1, d = 20}, false );
-- or
local cylinder3 = d3object.cylinder({h = 1, r1 = 10, r2 = 20}, true );
-- or
local cylinder4 = d3object.cylinder({h = 1, d1 = 20, d2 = 40}, false );
```

## Sphere

> d3object library

### Usage

```lua
d3object.sphere({r = number, d = number});
```

- r
   - `number` type
     - Specifies the radius of the sphere. If `r` is entered, the parameter `d` will no longer be accepted.
- d
   - `number` type
     - Specifies the diameter of the sphere. If `d` is entered, the parameter `r` will no longer be received.

### Example

```lua
sphere1 = d3object.sphere({ r = 10 });
-- or
sphere2 = d3object.sphere({ d = 20 });
```

## Polyhedron

> d3object library

### Usage

```lua
d3object.polyhedron({{x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3},.........},
     {{index1, index2, index3}, {index1, index3, index4, index2} ............});
```

- first parameter points
   - `table` type
     - This table is a two-dimensional array, each `{x, y, z}` represents the coordinates of a point.
- The second parameter faces
   - `table` type
     - This table is a two-dimensional array. The `index` in each `{index1, index2, index3}` is the subscript of the point in the previous `points` table. Such a `table` represents the points contained in a surface. gather.

### Example
```lua
--[[
@description: arg1 points, arg2 faces
@return {*}
--]]
polyhedron1 = d3object.polyhedron({{10, 10, 0}, {10, -10, 0}, {-10, -10, 0}, {-10, 10, 0}}, {{0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, {1, 0, 3}, {2, 1, 3}});
```
