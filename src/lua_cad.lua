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
    user_obj.m_offset = pos_list;
    return user_obj;
end

--[[
@description: user_define_obj mirror
@return {*}
--]]
function user_obj_mirror(user_obj, pos_list)
    user_obj.m_mirror = pos_list;
end

--[[
@description: user_define_obj scale
@return {*}
--]]
function user_obj_scale(user_obj, scale_set)
    user_obj.m_scale = scale_set;
end

function user_obj_to_Cstruct()
    
end

--[[
@description: user_define_obj 的变换操作表
@return {*}
--]]
user_define_metatable = {
    __index = {
        postion = user_obj_postion,
        mirror = user_obj_mirror,
        scale = user_obj_scale,
        to_struct = user_obj_to_Cstruct
    }
}

--[[
@description: 将一组 d3object 保存为一个 chunk
@return {*}
--]]
function d3object_to_chunk(obj)
    return {}
end

--[[
@description: 保存对象到标准件库
@return {*}
--]]
function d3object_save(obj)
    
end

--[[
@description: 3d 对象的元表
@return {*}
--]]
d3object_metatable = {
    --[[
    @description: union
    @return {*}
    --]]
    __add = function(obj1, obj2)
        return boolean.union({obj1, obj2});
    end,

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
    end,

    __index = {
        to_table = d3object_to_chunk,
        save = d3object_save
    }
}

-- 继承
setmetatable(user_define_metatable, d3object_metatable);

return user_define_metatable, d3object_metatable;
