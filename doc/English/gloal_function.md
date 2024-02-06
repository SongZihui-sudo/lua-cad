# global function

- [global function](#global-function)
  - [Code](#code)
    - [Usage](#usage)
    - [Example](#example)
  - [export](#export)
    - [Usage](#usage-1)
    - [Example](#example-1)
    - [Usage](#usage-2)
    - [Example](#example-2)
  - [import](#import)
    - [Usage](#usage-3)
    - [Example](#example-3)
  - [Global variables](#global-variables)


## Code

### Usage

```lua
code(object)
```

- object
   - `d3object` type
     - Object to view

Returns the openscad code for the given object.

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {10, 10, 10});
print(code(cube1));
```

## export

### Usage

```lua
export("filepath", object);

-- or
export("filepath", "code");

```

-filepath
   - `string` type
     - Specify the path to the export file
- object
   - `d3object` type
     - Specify the object to be exported. If object is specified, object will no longer be accepted.
-code
   - `string` type
     - Specifies the string to be exported. If code is specified, object is no longer accepted.

Exports the specified object or string to the specified openscad code file.

### Example

```lua
cube1 = d3object.cube({10, 10, 10}, true);
transform.postion(cube1, {10, 10, 10});
export("export.scad", cube1);

-- or
export("export.scad", code(cube1));
```

##include

### Usage

```lua
include("include_path")
```

- include_path
   - `string` type
     - Specify the path to the openscad file to include

Contains the specified openscad file, returning a string.

### Example

```lus
include_hole = include("hole.scad");
```

## import

### Usage

```lua
import("import_path")
```
-import_path
   - `string` type
     - Specify the path to the stl file to include

Import the specified stl file and return a string.

### Example

```lus
import_obj = include("obj.stl");
```

## Global variables

```lua
output_mode = string
```
This variable sets the output format of the current program. The optional parameters are `openscad` and so on.

Optional parameters:
| output_mode |
| ----- |
| openscad |
| .... |
