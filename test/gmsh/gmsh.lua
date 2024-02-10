package.path = package.path .. ';../../../../src/lua/?.lua';
gmsh = require("gmsh")
output_mode = "gmsh"

gmsh.initialize();
gmsh.add("t1");

local point1 = gmsh.model.Point.new({10, 10, 10}, 1);
local point2 = gmsh.model.Point.new({10, 20, 10}, 2);
local point3 = gmsh.model.Point.new({10, 20, 20}, 1);
local point4 = gmsh.model.Point.new({20, 20, 90}, 1);

local line1 = gmsh.model.Line.new(point1, point2);
local circle_arc1 = gmsh.model.CircleArc.new(point1, point2, point3);
local ellipse_arc1 = gmsh.model.EllipseArc.new(point1, point2, point3, point4);

square1 = d2object.square({10, 10}, true);

gmsh.generate(3);
gmsh.synchronize();
export("export.msh", square1);
gmsh.finalize();
