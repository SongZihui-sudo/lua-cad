d3object = require("d3object");
boolean = require("boolean")
user_define = require("user_define_obj")

local hole = $screw_hole("1/4-20,.5",head="socket",counterbore=5, anchor="TOP")$;
local cylinder1 = d3object.cylinder({h = 1,  r = 2}, true );
local cube1 = d3object.cube({10, 10, 10}, true);

print(code(cylinder1));

difference1 = boolean.difference({cylinder1, cube1, hole});

print(code(difference1));
