transform = require("transform");
d3object = require("d3object");

cube1 = d3object.cube({10, 10, 10}, false);

transform.postion(cube1, {0, 0, 0});

print(code(cube1));
