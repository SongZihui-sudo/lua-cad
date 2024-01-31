datum = require("datum");
d3object = require("d3object");
transform = require("transform");
boolean = require("boolean");

cube1 = d3object.cube({10, 10, 10}, true);
datum1 = d3object.datum(cube1, 1);
pos1 = datum.relative(datum1, "x", 10);
cube2 = d3object.cube({5,5,5}, true);
transform.postion(cube2, pos1);
union1 = boolean.union({cube1, cube2});

print(code(union1));