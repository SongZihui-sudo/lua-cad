boolean = require("boolean");
transform = require("transform");
d3object = require("d3object");
user_define_obj = require("user_define_obj");
package.path = package.path .. ';../?.lua'

--[[
@description: 设置 user_define 对象的位置
@return {*}
--]]
function user_obj_postion(user_obj, pos_list)
    old_code = user_obj[1];
    translate_code = to_openscad_code.to_translate(pos_list);
    new_code = translate_code..old_code;
    user_obj[1] = new_code;
    user_obj.offset = pos_list;
    return user_obj;
end

--[[
@description: user_define_obj mirror
@return {*}
--]]
function user_obj_mirror(user_obj, pos_list)
    
end

--[[
@description: user_define_obj scale
@return {*}
--]]
function user_obj_scale(user_obj, scale_set)
    
end

--[[
@description: user_define_obj 的变换操作表
@return {*}
--]]
user_define_metatable = 
{
    postion = user_obj_postion,
    mirror = user_obj_mirror,
    scale = user_obj_scale
}

--[[
@description: 3d 对象的元表
@return {*}
--]]
d3object_metatable = 
{
    --[[
    @description: union
    @return {*}
    --]]    
    __add = function(obj1, obj2)
        return boolean.union({obj1, obj2});
    end
    ,
    
    --[[
    @description: difference
    @return {*}
    --]]    
    __sub = function(obj1, obj2)
        return boolean.difference({obj1, obj2});
    end,

    --[[
    @description: intersection
    @return {*}
    --]]    
    __mul = function(obj1, obj2)
        return boolean.intersection({obj1, obj2});
    end
}

-- 继承
setmetatable(user_define_metatable, d3object_metatable);

transform = {}

function transform.tranlate(obj, pos_list)
    if type(obj) == userdata then
        transform.postion(obj, pos_list);
    else
        user_define_metatable.postion(obj, pos_list);
    end
end

return transform
