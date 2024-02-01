datum = require("datum");
d3object = require("d3object");
transform = require("transform");
boolean = require("boolean");

print("-------------- cylinder --------------")
cylinder1 = d3object.cylinder({h = 10, r = 5}, false);
datum1 = d3object.datum(cylinder1, 1);
print("x: " .. datum.to_table(datum1).x);
print("y: " .. datum.to_table(datum1).y);
print("z: " .. datum.to_table(datum1).z);
print(code(cylinder1));

print("-------------- polyhedron --------------")
polyhedron1 = d3object.polyhedron({{10, 10, 0}, {10, -10, 0}, {-10, -10, 0}, {-10, 10, 0}},
{{0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}, {1, 0, 3}, {2, 1, 3}})
datum2 = d3object.datum(polyhedron1, 1);
print("x: " .. datum.to_table(datum2).x);
print("y: " .. datum.to_table(datum2).y);
print("z: " .. datum.to_table(datum2).z);
print(code(polyhedron1));

print("-------------- cube --------------")
cube1 = d3object.cube({10, 10, 10}, false);
datum3 = d3object.datum(cube1, 1);
print("x: " .. datum.to_table(datum3).x);
print("y: " .. datum.to_table(datum3).y);
print("z: " .. datum.to_table(datum3).z);
print(code(cube1));

print("-------------- sphere --------------")
sphere1 = d3object.sphere({r = 10});
datum4 = d3object.datum(sphere1, 3);
print("x: " .. datum.to_table(datum4).x);
print("y: " .. datum.to_table(datum4).y);
print("z: " .. datum.to_table(datum4).z);
print(code(sphere1));

print("---------- relative postion ----------------")
datum5 = datum.relative(datum4, "x", 10);
print("x: " .. datum.to_table(datum5).x);
print("y: " .. datum.to_table(datum5).y);
print("z: " .. datum.to_table(datum5).z);

print("------------- distance ------------------")
dis = datum.distance(datum4, {1, 2, 3});
print("distance: " .. dis);

print("------------- angle ------------------")
angle = datum.angle(datum4, {1, 2, 3});
print("angle: " .. angle);