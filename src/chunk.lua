function chunk_tocode(self)
    local buf_code = "";
    for k, v in pairs(self) do
        local current_code;
        if type(v) == "userdata" then
            current_code = code(v);
        else
            current_code = v;
        end
        buf_code = buf_code .. current_code;
    end
    return buf_code;
end

chunk = 
{
    __index = {
        code = chunk_tocode
    }
}

return chunk;
