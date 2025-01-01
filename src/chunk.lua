function chunk_tocode(self)
    local buf_code = "";
    for k, v in pairs(self) do
        local current_code = "";
        if type(v) == "userdata" then
            current_code = code(v);
        elseif type(v) == "table" then
            current_code = v[1];
        else
            current_code = v;
        end
        buf_code = buf_code .. current_code;
    end
    -- delete \0
    local temp = '';
    for name in string.gmatch(buf_code,"[^%z]") do
        temp = temp..name;
    end
    return temp;
end

chunk = 
{
    __index = {
        code = chunk_tocode
    }
}

return chunk;
