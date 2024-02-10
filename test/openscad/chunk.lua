transform = require("transform");
d3object = require("d3object");
boolean = require("boolean");
d3object = require("d3object");
package.path = package.path ..';../../../../?.lua';
user_obj_metatable = require("src.user_object.user_obj")
chunk = require("src.chunk")

shoulder_screw_include = include("shoulder_screw");

test1 = $shoulder_screw( "english", 1/2, length = 20 )$;
test1.postion(test1, {10, 11, 12});
test1.scale(test1, {10, 10, 10});
test1.mirror(test1, {10, 10, 10});
test1.print(test1);
test1.rotate(test1, 2.5, {10, 10, 10})
test1.print(test1);
test1.color(test1, {1, 2, 3});
test1.print(test1);
test1.code(test1);
cube1 = d3object.cube({10, 10, 10}, true);
difference1 = boolean.difference({cube1, test1});
chunk1 = {shoulder_screw_include, difference1};
setmetatable(chunk1, chunk);
print(chunk1.code(chunk1));
