function user_obj_postion(self, parameters)
    self._offset = parameters;
end

function user_obj_scale(self, parameters)
    self._scale = parameters;
end

function user_obj_mirror(self, parameters)
    self._mirror = parameters;
end

function user_obj_rotate(self, ...)
    local arg = {...}
    local i = 0;
    for k, v in pairs(arg) do
        if i == 0 then
            if type(v) == "number" then
                self._rotate_deg_a = v;
            elseif type(v) == "table" then
                self._rotate_a = v;
            else
                print("Arg 1 Type Error!");
                return;
            end
        elseif i == 1 then
            if type(v) == "table" then
                self._rotate_v = v;
            else
                print("Arg 2 Type Error!");
                return;
            end
        else
            print("Too many arg!");
            return;
        end
        i = i + 1;
    end
end

function user_obj_color(self, ...)
    local arg = {...}
    local i = 0;
    for k, v in pairs(arg) do
        if i == 0 then
            if type(v) == "string" or type(v) == "table" then
                self._color = v;
            else
                print("Arg 1 Type Error!");
                return;
            end
        elseif i == 1 then
            if type(v) == "number" then
                self._color_alpha = v;
            else
                print("Arg 2 Type Error!");
                return; 
            end
        else
            print("Too many arg!");
            return;
        end
        i = i + 1;
    end
end

function user_obj_to_code(self)
    local temp;
    if type(self._offset) ~= "nil" then
        local fmt = transform.translate_fmt();
        temp = string.format(fmt, self._offset[1], self._offset[2], self._offset[3]);
        self[1] = temp .. self[1] .. "\n";
    end
    if type(self._scale) ~= "nil" then
        local fmt = transform.scale_fmt();
        temp = string.format(fmt, self._scale[1], self._scale[2], self._scale[3]);
        self[1] = temp .. self[1] .. "\n";
    end
    if type(self._mirror) ~= "nil" then
        local fmt = transform.mirror_fmt();
        temp = string.format(fmt, self._mirror[1], self._mirror[2], self._mirror[3]);
        self[1] = temp .. self[1] .. "\n";
    end
    return self;
end

user_obj_metatable = {
    __index = {
        postion = user_obj_postion,
        scale = user_obj_scale,
        mirror = user_obj_mirror,
        rotate = user_obj_rotate,
        color = user_obj_color,
        print = function(self)
            for k, v in pairs(self) do
                print(k, v);
            end
        end,
        code = user_obj_to_code
    }
}

return user_obj_metatable;
