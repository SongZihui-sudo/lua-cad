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
    self._isrotate = true;
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
    self._iscolor = true;
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
    if type(self._offset) ~= "nil" then
        local fmt = transform.translate_fmt();
        local temp = string.format(fmt, self._offset[1], self._offset[2], self._offset[3]);
        self[1] = temp .. self[1];
    end
    if type(self._scale) ~= "nil" then
        local fmt = transform.scale_fmt();
        local temp = string.format(fmt, self._scale[1], self._scale[2], self._scale[3]);
        self[1] = temp .. self[1];
    end
    if type(self._mirror) ~= "nil" then
        local fmt = transform.mirror_fmt();
        local temp = string.format(fmt, self._mirror[1], self._mirror[2], self._mirror[3]);
        self[1] = temp .. self[1];
    end
    if self._isrotate then
        local fmt = transform.rotate_fmt();
        local rotate_arg1 = "";
        local rotate_arg2 = "";
        if type(self._rotate_deg_a) ~= "nil"  then
            rotate_arg1 = "a = " .. self._rotate_deg_a .. ",";
            goto next;
        end
        if type(self._rotate_a) ~= "nil" then
            for k, v in pairs(self._rotate_a) do
                rotate_arg1 = rotate_arg1 .. v .. ",";
            end
            string.sub(rotate_arg1, 1, -2);
            rotate_arg1 = "[" .. rotate_arg1 .. "]";
        end
::next::
        if type(self._rotate_v) ~= "nil" then
            for k, v in pairs(self._rotate_v) do
                rotate_arg2 = rotate_arg2 .. v .. ",";
            end
            rotate_arg2 = string.sub( rotate_arg2, 1, -2 );
            rotate_arg2 = "v = [" .. rotate_arg2 .. "]";
        end
        local temp = string.format(fmt, rotate_arg1, rotate_arg2);
        self[1] = temp .. self[1];
    end
    if self._iscolor then
        local fmt = transform.color_fmt();
        local color_arg1 = "";
        local color_arg2 = "";
        if type(self._color) ~= "nil" then
            if type(self._color) == "string" then
                color_arg1 = self._color;
            elseif type(self._color) == "table" then
                for k, v in pairs(self._color) do
                    color_arg1 = color_arg1 .. v .. ",";
                end
                color_arg1 = string.sub( color_arg1, 1, -2 );
                color_arg1 = "c = [" .. color_arg1 .. "]";
            end
        end
        if type(self._color_alpha) ~= "nil" then
            color_arg2 = ", alpha = " .. self._color_alpha;
        end
        local temp = string.format(fmt, color_arg1, color_arg2);
        self[1] = temp .. self[1];
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
