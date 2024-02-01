--[[
@description: 为 d3object 和 user_define_obj 设置元表以此可以简化操作
@return {*}
--]] 
boolean = require("boolean");
transform = require("transform");
d3object = require("d3object");
user_define_obj = require("user_define_obj");
package.path = package.path .. ';../?.lua'
to_openscad_code = require("port.openscad.to_openscad_code")

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
@description: user_define_obj 的方法
@return {*}
--]]
user_obj_funcs = {
    postion = user_obj_postion
}

--[[
@description: user_define_obj 的元表
@return {*}
--]]
user_define_metatable = 
{
    __index = user_obj_funcs;
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