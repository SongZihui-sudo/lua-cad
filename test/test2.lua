user_define = require("user_define_obj")

function print_info(data)
    for key, value in pairs(data) do      
        print(key, value);
    end
end

-- test1
test1 = $shoulder_screw( "english", 1/2, length = 20 )$;

test1 = user_define.postion(test1, {10, 10, 10});
print("obj_type: "..test1[1]);
print("offset")
print("x: "..test1["offset"]["x"]);
print("x: "..test1["offset"]["y"]);
print("x: "..test1["offset"]["z"]);
print("test1")
print_info(test1);

-- test2
test2 = $screw( "#6-32", head="flat undercut",length=12)$;
print("test2")
print("obj_type: "..test2[1]);
print_info(test2);
