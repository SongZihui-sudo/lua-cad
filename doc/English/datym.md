# Baseline

- [Benchmark](#Benchmark)
   - [method](#method)
     - [d3object.datum](#d3objectdatum)
       - [usage](#usage)
       - [Example](#Example)
     - [relative](#relative)
       - [usage](#usage-1)
       - [Example](#Example-1)
     - [distance](#distance)
       - [usage](#usage-2)
       - [Example](#Example-2)
     - [angle](#angle)
       - [usage](#usage-3)
       - [Example](#Example-3)
     - [to\_table](#to_table)
       - [usage](#usage-4)
       - [Example](#Example-4)


## method

### d3object.datum

#### Usage

```lua
d3object.datum(object, index);
```

- object
   - `d3object` type
     - The object to obtain the datum from.
-index
   - `int` type, datum index
     - Returns the specified datum.

Returns the datum vector of the given object.

#### Example

```lua
print("-------------- cylinder --------------")
cylinder1 = d3object.cylinder({h = 10, r = 5}, false);
datum1 = d3object.datum(cylinder1, 1);
print("x: " .. datum.to_table(datum1).x);
print("y: " .. datum.to_table(datum1).y);
print("z: " .. datum.to_table(datum1).z);
print(code(cylinder1));

print("------------- polyhedron --------------")
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

print("------------- sphere ---------------")
sphere1 = d3object.sphere({r = 10});
datum4 = d3object.datum(sphere1, 3);
print("x: " .. datum.to_table(datum4).x);
print("y: " .. datum.to_table(datum4).y);
print("z: " .. datum.to_table(datum4).z);
print(code(sphere1));
```

### relative

#### Usage

```lua
datum.relative(darum_obj, "direction", distance);
```

- darum_obj
   - `datum` type
     - gives the current relative baseline
-direction
   - `string` type
     - point out the direction
-distance
   - `number` type
     - Point out the distance

Returns a datum that is a specified distance from this datum in the given direction.

#### Example
```lua
datum5 = datum.relative(datum4, "x", 10);
print("x: " .. datum.to_table(datum5).x);
print("y: " .. datum.to_table(datum5).y);
print("z: " .. datum.to_table(datum5).z);
```

### distance

#### Usage

```lua
datum.distance(darum_obj, {x, y, z});
```

- darum_obj
   - `datum` type
     - gives the current relative baseline
- {x, y, z}
   - `table` type
     - gives the vector from which the distance is to be calculated

Calculates the distance between the current datum and the given vector.

#### Example
```lua
dis = datum.distance(datum4, {1, 2, 3});
print("distance: " .. dis);
```

### angle

#### Usage

```lua
datum.angle(datum4, {x, y, z});
```

- darum_obj
   - `datum` type
     - gives the current relative baseline
- {x, y, z}
   - `table` type
     - gives the vector from which the angle is to be calculated

Calculates the angle between the current datum and the given vector, here two vectors.

#### Example

```lua
angle = datum.angle(datum4, {1, 2, 3});
print("angle: " .. angle);
```

### to_table

#### Usage

```lua
datum.to_table(datum_obj)
```

-datum_obj
   - `datum` object
     - The object to be converted.

Convert datum to a table.

#### Example

```lua
cylinder1 = d3object.cylinder({h = 10, r = 5}, false);
datum1 = d3object.datum(cylinder1, 1);
print("x: " .. datum.to_table(datum1).x);
print("y: " .. datum.to_table(datum1).y);
print("z: " .. datum.to_table(datum1).z);
```
