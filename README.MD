# LUA-CAD

Example1: basic objects
```lua
local cube = require("cube")
local boolean = require("boolean")

local cube1 = cube.new({ 10, 10, 10 }, true);
local cube2 = cube.new({ 10, 10, 10 }, false);

-- 打印长，宽，高
print("height: " .. cube.height(cube1) .. " mm");
print("width: " .. cube.width(cube1) .. " mm");
print("length: " .. cube.length(cube1) .. " mm");

-- 设置位置
print("Current position: ")
cube.postion(cube1, { 0, 0, 0 });
local point = cube.anchor(cube1, 10);
for k, v in pairs(point) do
    print(k, v)
end

-- 正方体顶点坐标
for i = 1, 14, 1 do
    print("point" .. i .. ": ")
    -- 返回一个顶点
    local point = cube.anchor(cube1, i);
    for k, v in pairs(point) do
        print(k, v)
    end
end

local difference1 = boolean.difference({cube1, cube2});
local difference2 = boolean.difference({difference1, cube1});
local difference3 = boolean.difference({cube1, cube2, difference2});
local union1 = boolean.union({difference1, difference2});
local intersection1 = boolean.intersection({union1, difference3});

print("difference1 code1 : \n" .. code(intersection1));

export("./export.scad", intersection1);
```
Example2: User-defined objects can directly reuse openscad code and convert them into lua tables.
```lua
user_define = require("user_define_obj")

function print_info(data)
    for key, value in pairs(data) do      
        print(key, value);
    end
end

-- test1
test1 = $shoulder_screw( "english", 1/2, length = 20 )$;

test1 = user_define.postion(test1, {10, 10, 10});
print("obj_type: "..test1[1]);
print("offset")
print("x: "..test1["offset"]["x"]);
print("x: "..test1["offset"]["y"]);
print("x: "..test1["offset"]["z"]);
print("test1")
print_info(test1);

-- test2
test2 = $screw( "#6-32", head="flat undercut",length=12)$;
print("test2")
print("obj_type: "..test2[1]);
print_info(test2);

```
