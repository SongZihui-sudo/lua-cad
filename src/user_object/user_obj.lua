local TRANSFORM_TYPE = {
    TRANSLATE = 17,
    SCALE = 18,
    ROTATE = 19,
    MIRROR = 20,
    COLOR = 21
};

function user_obj_postion(self, parameters)
    self._offset = parameters;
end

function user_obj_scale(self, parameters)
    self._scale = parameters;
end

function user_obj_mirror(self, parameters)
    self._mirror = parameters;
end

function user_obj_rotate(self, parameters)
end

function user_obj_color(self, parameters)
end

user_obj_metatable = {
    __index = {
        op_stack = {},
        postion = user_obj_postion,
        scale = user_obj_scale,
        mirror = user_obj_mirror,
        rotate = user_obj_rotate,
        color = user_obj_color
    }
}
