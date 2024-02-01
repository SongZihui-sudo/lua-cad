to_openscad_code = {}

local translate_rule = "translate([%f, %f, %f])\n";

function to_openscad_code.to_translate(xyz)
    if #xyz < 3 then
        print("Error, length is less than 3!");
        return "";
    end
    return string.format(translate_rule, xyz[1], xyz[2], xyz[3]);
end

return to_openscad_code;