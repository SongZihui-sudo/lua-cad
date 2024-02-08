boolean = require("boolean")
d3object = require("d3object");
package.path = package.path ..';../../../../?.lua';
user_obj_metatable = require("src.lua.user_obj")

hole = $screw_hole("1/4-20,.5",head="socket",counterbore=5, anchor="TOP")$;
hole.postion(hole, {10, 10, 10});
cube1 = d3object.cube({ 10, 10, 10 }, true);

difference1 = boolean.difference({cube1, hole});

print(code(difference1));

export("export.scad", difference1);
