sphere1 = d3object.sphere({ r = 10 });
-- or
sphere2 = d3object.sphere({ d = 20 });

code1 = code(sphere1);
code2 = code(sphere2);

print(code1 .. code2);