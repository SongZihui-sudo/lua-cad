output_mode = "openscad"
package.path = package.path ..';../../../../?.lua';
user_obj_metatable = require("src.lua.user_obj")

-- test1
local test1 = $shoulder_screw( "english", 1/2, length = 20 )$;
test1.postion(test1, {10, 10, 10});
print("test1");
test1.print(test1);

-- test2
local test2 = $screw( "#6-32", head="flat undercut",length=12)$;
print("test2")
test2.print(test2);
