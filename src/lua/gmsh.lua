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
gmsh_point = class(gmsh_obj_base);

function gmsh_point:ctor(postion, ...)
    local arg = {...};
    if #postion < 3 then
        print("The coordinates of the point are {x, y, z}!")
        return -1;
    end
    self.index = -1;
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
    if self.index == -1 then
        self.index = cgmsh.addPoint(self);
    end
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
    self.index = -1;
end

function gmsh_line:add()
    self.start_point:add();
    self.end_point:add();
    if self.index == -1 then
        print("11111");
        self.index = cgmsh.addLine(self.start_point, self.end_point);
    end
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
gmsh_circle_arc = class(gmsh_obj_base);

function gmsh_circle_arc:ctor(start_point, center_point, end_point, ...)
    local args = {...};
    if #args == 1 then
       self.center = args[1]
    else
        self.center = false;
    end
    self.index = -1;
    self.start_point = start_point;
    self.center_point = center_point;
    self.end_point = end_point;
end

function gmsh_circle_arc:add()
    self.start_point:add();
    self.center_point:add();
    self.end_point:add();
    if self.index == -1 then
        self.index = cgmsh.addCircleArc(self.start_point, self.center_point, self.end_point, self.center);
    end
end

-- ******************************************************************************************
--[[
@description: EllipseArc
--]]
gmsh_ellipse_arc = class(gmsh_obj_base);

function gmsh_ellipse_arc:ctor(start_point, center_point, major_point, end_point)
    self.index = -1;
    self.start_point = start_point;
    self.center_point = center_point;
    self.major_point = major_point;
    self.end_point = end_point;
end

function gmsh_ellipse_arc:add()
    self.start_point:add();
    self.center_point:add();
    self.major_point:add();
    self.end_point:add();
    if self.index == -1 then
        self.index = cgmsh.addEllipseArc(self.start_point, self.center_point, self.major_point, self.end_point);
    end
end

-- ******************************************************************************************
--[[
@description: Spline
--]]
gmsh_spline = class(gmsh_obj_base);

function gmsh_spline:ctor(points, tangents)
    self.points = points;
    self.tangents = tangents;
    self.index = -1;
end

function gmsh_spline:add()
    if self.index == -1 then
        self.index = cgmsh.addSpline(self);
    end
end

-- ******************************************************************************************
--[[
@description: BSpline
--]]
gmsh_bspline = class(gmsh_obj_base);

function gmsh_bspline:ctor(points)
    self.points = points;
    self.index = -1;
end

function gmsh_bspline:add()
    if self.index == -1 then
        self.index = cgmsh.addBSpline(self);
    end
end

-- ******************************************************************************************
--[[
@description: Bezier
--]]
gmsh_bezier = class(gmsh_bspline);

function gmsh_bezier:add()
    if self.index == -1 then
        self.index = cgmsh.addBezier(self);
    end
end

-- ******************************************************************************************
--[[
@description: CurveLoop
--]]
gmsh_curveloop = class(gmsh_bspline);

function gmsh_curveloop:add()
    if self.index == -1 then
        self.index = cgmsh.addCurveLoop(self);
    end
end

-- ******************************************************************************************
--[[
@description: Plane Surface
--]]
gmsh_plane_surface = class(gmsh_bspline);

function gmsh_plane_surface:add()
    if self.index == -1 then
        self.index = cgmsh.addPlaneSurface(self);
    end
end

-- ******************************************************************************************
--[[
@description: Surface Filling
--]]
gmsh_surface_filling = class(gmsh_bspline);

function gmsh_surface_filling:ad()
    if self.index == -1 then
        self.index = cgmsh.addSurfaceFilling(self);
    end
end

-- ******************************************************************************************
--[[
@description: Surface Loop
--]]
gmsh_surface_loop = class(gmsh_obj_base);

function gmsh_surface_loop:ctor(sewing, points)
    self.index = -1;
    self.sewing = sewing;
    self.points = points;
end

function gmsh_surface_loop:add()
    if self.index == -1 then
        self.index = cgmsh.addSurfaceLoop(self);
    end
end

-- ******************************************************************************************
--[[
@description: Volume
--]]

gmsh_volume = class(gmsh_obj_base);

function gmsh_volume:ctor(wire, degree, numPointsOnCurves, numIter, anisotropic, tol2d, tol3d, tolAng, tolCurv, maxDegree, maxSegments, points)
    self.wire = wire;
    self.degree = degree;
    self.numPointsOnCurves = numPointsOnCurves;
    self.numIter = numIter;
    self.anisotropic = anisotropic;
    self.tol2d = tol2d;
    self.tol3d = tol3d;
    self.tolAng = tolAng;
    self.tolCurv = tolCurv;
    self.maxDegree = maxDegree;
    self.maxSegments = maxSegments;
    self.points = points;
    self.index = -1;
end

function gmsh_volume:add()
    if self.index == -1 then
        self.index = cgmsh.addVolume(self);
    end
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
