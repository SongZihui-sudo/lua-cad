user_define = require("user_define_obj")
user_define_tables = {};

function print_info(data)
    for key, value in pairs(data) do      
        print(key, value);
    end
end

test1 = $shoulder_screw( nil, "english", 1/2, length = 20 )$;
table.insert(user_define_tables, test1);
name = user_define.obj_name(0);
print(name)

print_info(test1);

test2 = $screw(nil, "#6-32", head = "flat undercut",length=12)$;
table.insert(user_define_tables, test2);
name = user_define.obj_name(1);
print(name)

print_info(test2);
