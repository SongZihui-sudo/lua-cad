require('class')

gmsh_point = class()
gmsh_point_count = 0;

function gmsh_point:ctor(postion, ...)
    local arg = {...};
    if #postion < 3 then
        print("The coordinates of the point are {x, y, z}!")
        return -1;
    end
    self.x = postion[1];
    self.y = postion[2];
    self.z = postion[3];
    self.lc = -1;
    if arg[1] ~= nil then
        self.lc = arg[1];
    end
    gmsh_point_count = gmsh_point_count + 1;
    self.index = gmsh_point_count;
end

function gmsh_point:index()
    return self.index;
end

function gmsh_point:xyz()
    return {self.x, self.y, self.z};
end

function gmsh_point:lc()
    return self.lc;
end

function gmsh_point:dump()
    return {
        x = self.x,
        y = self.y,
        z = self.z,
        lc = self.lc
    }
end

function gmsh_dump_to_point(object)
    if type(object) ~= "userdata" then
        return -1;
    end
end

gmsh = {
    dump_point = gmsh_dump_to_point
}
