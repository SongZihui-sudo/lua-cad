output_mode = "openscad"
package.path = package.path ..';../../../../?.lua';
user_obj_metatable = require("src.user_object.user_obj")

test1 = $shoulder_screw( "english", 1/2, length = 20 )$;
test1.postion(test1, {10, 10, 10});
test1.scale(test1, {10, 10, 10});
test1.mirror(test1, {10, 10, 10});
test1.rotate(test1, 1, {10, 10, 10});
test1.rotate(test1, {4, 5, 6});
test1.rotate(test1, {1, 2, 3}, {4, 5, 6});
test1.rotate(test1, 1, {4, 5, 6});
test1.print(test1);
test1.color(test1, {1, 2, 3});
print(test1.code(test1));
