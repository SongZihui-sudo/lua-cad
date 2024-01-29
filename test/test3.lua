boolean = require("boolean")
cube = require("cube");
user_define = require("user_define_obj");

local hole = $screw_hole("1/4-20,.5",head="socket",counterbore=5, anchor="TOP")$;

function print_info(data)
    for key, value in pairs(data) do      
        print(key, value);
    end
end

hole = user_define.postion(hole, {10, 10, 10});
cube1 = cube.new({ 10, 10, 10 }, true);

difference1 = boolean.difference({cube1, hole})

print("Offset:")
print("x = "..hole.offset.x);
print("y = "..hole.offset.y);
print("z = "..hole.offset.z);
print_info(hole)

print(code(difference1));

export("export.scad", difference1);
