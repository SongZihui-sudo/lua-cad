user_obj = require("user_obj")

circle1 = d2object.circle({
    d = 10
}, true);
transform.postion(circle1, {20, 20, 20});
transform.scale(circle1, {10, 2, 1});
transform.mirror(circle1, {10, 2, 1});
transform.rotate(circle1, 1, {4, 5, 6});
print(code(circle1));
circle2 = d2object.circle({
    r = 10
}, true);
d2object.linear_extrude(circle2, {
    height = 10,
    center = true,
    convexity = 10,
    twist = 2,
    slices = 20,
    scale = 1.0
});
d2object.rotate_extrude(circle2, {
    angle = 360,
    convexity = 2
});
print(code(circle2))
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

test1 = $shoulder_screw( "english", 1/2, length = 20 )$;

test1.postion(test1, {10, 10, 10});

test1.scale(test1, {10, 10, 10});

test1.mirror(test1, {10, 10, 10});

test1.rotate(test1, 1, {10, 10, 10});

test1.rotate(test1, {4, 5, 6});

test1.rotate(test1, {1, 2, 3}, {4, 5, 6});

test1.rotate(test1, 1, {4, 5, 6});

test1.color(test1, {1, 2, 3});

print(test1.cobin(test1));

print(code(test1));