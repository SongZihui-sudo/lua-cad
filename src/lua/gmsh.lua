require('class')

-- ******************************************************************************************
-- 基类
gmsh_obj_base = class();

function gmsh_obj_base:ctor()
end

function gmsh_obj_base:get_index()
    return self.index;
end

function gmsh_obj_base:dump()
end

function gmsh_obj_base:add()

end

-- ******************************************************************************************
--[[
@description: GMSH 中的 POINT 对象
--]]
gmsh_point = class(gmsh_obj_base)

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
    self.type = "Point";
    if arg[1] ~= nil then
        self.lc = arg[1];
    end
end

function gmsh_point:add()
    self.index = cgmsh.addPoint(self);
end

function gmsh_point:get_xyz()
    return {self.x, self.y, self.z};
end

function gmsh_point:get_lc()
    return self.lc;
end

function gmsh_point:dump()
    return {
        index = self.index,
        x = self.x,
        y = self.y,
        z = self.z,
        lc = self.lc
    }
end
-- ******************************************************************************************
--[[
@description: Line
--]]
gmsh_line = class(gmsh_obj_base);

function gmsh_line:ctor(start_point, end_point)
    self.type = "Line";
    self.start_point = start_point;
    self.end_point = end_point;
end

function gmsh_line:add()
    self.index = cgmsh.addLine(self.start_point, self.end_point);
end

function gmsh_line:get_start_point()
    return self.start_point;
end

function gmsh_line:get_end_line()
    return self.end_point;
end

-- ******************************************************************************************
--[[
@description: CircleArc
@return {*}
--]]
gmsh_circle_arc = class(gmsh_obj_base)

function gmsh_circle_arc:ctor(start_point, center_point, end_point, ...)
    local args = {...}
    if #args == 3 then
        self.nx = args[1];
        self.ny = args[1];
        self.nz = args[1];
    else
        self.nx = 0;
        self.ny = 0;
        self.nz = 0;
    end
    self.start_point = start_point;
    self.center_point = center_point;
    self.end_point = end_point;
end

function gmsh_circle_arc:add()
    self.index = cgmsh.addCircleArc(self.start_point, self.center_point, self.end_point, self.nx, self.ny, self.nz)
end

-- ******************************************************************************************
--[[
@description: EllipseArc
--]]
gmsh_ellipse_arc = class(gmsh_obj_base)

function gmsh_ellipse_arc:ctor(start_point, center_point, major_point, end_point, ...)
    local args = {...}
    if #args == 3 then
        self.nx = args[1];
        self.ny = args[1];
        self.nz = args[1];
    else
        self.nx = 0;
        self.ny = 0;
        self.nz = 0;
    end
    self.start_point = start_point;
    self.center_point = center_point;
    self.major_point = major_point;
    self.end_point = end_point;
end

function gmsh_ellipse_arc:add()
    self.index = cgmsh.addEllipseArc(self.start_point, self.center_point, self.major_point, self.end_point, self.nx,
        self.ny, self.nz)
end

-- ******************************************************************************************
local gmsh = {
    initialize = cgmsh.init,
    finalize = cgmsh.finalize,
    generate = cgmsh.generate,
    add = cgmsh.add,
    synchronize = cgmsh.syn,
    model = {
        Point = gmsh_point,
        Line = gmsh_line,
        CircleArc = gmsh_circle_arc,
        EllipseArc = gmsh_ellipse_arc
    }
}

return gmsh;
