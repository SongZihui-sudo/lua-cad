polygon1 = d2object.polygon({{0, 0}, {100, 0}, {130, 50}, {30, 50}}, {{0, 1, 2, 3}, {2, 3}, {1}});
transform.postion(polygon1, {20, 20, 20});
transform.scale(polygon1, {10, 2, 1});
transform.mirror(polygon1, {10, 2, 1});
transform.rotate(polygon1, 1, {4, 5, 6});
print(code(polygon1));
