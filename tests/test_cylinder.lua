cylinder1 = d3object.cylinder({h = 1,  r = 10}, true );
-- or
cylinder2 = d3object.cylinder({h = 1,  d = 20}, false );
-- or
cylinder3 = d3object.cylinder({h = 1,  r1 = 10, r2 = 20}, true );
-- or
cylinder4 = d3object.cylinder({h = 1,  d1 = 20, d2 = 40}, false );

code1 = code(cylinder1);
code2 = code(cylinder2);
code3 = code(cylinder3);
code4 = code(cylinder4);

print(code1 .. code2 .. code3 .. code4);