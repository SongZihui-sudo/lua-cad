cube1 = d3object.cube({ 10, 10, 10 }, false);

set_openscad("openscad");
set_hob3l("/root/project/lua-cad/tools/hob3l/hob3l.x");

render("stl", cube1, { scad_path = "render1.scad", stl_path = "render1.stl", use_hob3l = "true" });
render("stl", cube1, { scad_path = "render2.scad", stl_path = "render2.stl", use_hob3l = "false" });