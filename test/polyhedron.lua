d3object = require("d3object");
boolean = require("boolean");

--[[
@description: arg1 points, arg2 faces
@return {*}
--]]
polyhedron1 = d3object.polyhedron({{10, 10, 0}, {10, -10, 0}, {-10, -10, 0}, {-10, 10, 0}},
    {{0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, {1, 0, 3}, {2, 1, 3}});

print(code(polyhedron1));

cube1 = d3object.cube({10, 10, 10}, false);

difference1 = boolean.difference({polyhedron1, cube1});

export("export.scad", difference1);
