cylinder = require("cylinder");
boolean = require("boolean")
cube = require("cube")
user_define = require("user_define_obj")

local hole = $screw_hole("1/4-20,.5",head="socket",counterbore=5, anchor="TOP")$;
local cylinder1 = cylinder.new({h = 1, r = 2, r1 = 3, r2 = 4, d1 = 5, d2 = 6}, true );
local cube1 = cube.new({10, 10, 10}, true);

print(code(cylinder1));

difference1 = boolean.difference({cylinder1, cube1, hole});

print(code(difference1));
