d3object = require("d3object");
boolean = require("boolean")

sphere1 = d3object.sphere({ r = 10 });
cube1 = d3object.cube({10, 10, 10}, false);
difference1 = boolean.difference({sphere1, cube1});

print(code(sphere1));

print(code(difference1));
