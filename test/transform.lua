transform = require("transform");
d3object = require("d3object");

cube1 = d3object.cube({10, 10, 10}, false);

transform.postion(cube1, {0, 0, 0});

print(code(cube1));

cube1 = d3object.cube({10, 10, 10}, true);

transform.scale(cube1, {10, 10, 10});
print(code(cube1));

transform.rotate(cube1, {4, 5, 6});
print(code(cube1));

transform.rotate(cube1, {1, 2, 3}, {4, 5, 6});
print(code(cube1));

transform.rotate(cube1, 1, {4, 5, 6});
print(code(cube1));

transform.mirror(cube1, {1, 2, 3});
print(code(cube1));

fill1 = transform.fill({cube1});
print(code(fill1));

hull1 = transform.hull({cube1});
print(code(hull1));

minkowski1 = transform.minkowski({cube1});
print(code(minkowski1));

offset1 = transform.offset({cube1}, 1);
print(code(offset1));

offset1 = transform.offset({cube1}, 2);
print(code(offset1));

transform.color(cube1, "xxx");
print(code(cube1));

transform.color(cube1, "xxx", 1);
print(code(cube1));

transform.color(cube1, {1,2,3}, 1);
print(code(cube1));

transform.color(cube1, {1,2,3,4}, 1);
print(code(cube1));

transform.color(cube1, "xxx", {1,2,3});
print(code(cube1));
