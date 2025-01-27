cube1 = d3object.cube({ 10, 10, 10 }, false);

set_openscad("D:/Openscad/openscad.exe");

render("stl", cube1, { scad_path = "render2.scad", stl_path = "render2.stl", use_hob3l = "false" });