sphere = require("sphere")
cube = require("cube");
boolean = require("boolean")

sphere1 = sphere.new({ r = 10 });
cube1 = cube.new({10, 10, 10}, false);
difference1 = boolean.difference({sphere1, cube1});

print(code(sphere1));

print(code(difference1));
