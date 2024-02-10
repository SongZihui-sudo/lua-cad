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
