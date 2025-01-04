includes("@builtin/xpack")

add_rules("mode.debug", "mode.release")
set_languages("c++latest", "clatest")

-- Set the header file directory
add_includedirs("./lua")
add_includedirs("./src")
add_includedirs("./src/d3object")
add_includedirs("./src/d2object")
add_includedirs("./src/user_object")
add_includedirs("./port/openscad")

target("lua")
    set_kind("static")
    add_files("lua/*.c|onelua.c|lua.c")

-- Compilation settings
target("lua-cad")
    if is_plat("windows") then
        add_deps("lua")
    end
    set_kind("binary")
    add_files("port/openscad/*.c")
    add_files("lua/*.c|onelua.c|lua.c")
    add_files("src/*.c|lua-cad.c")
    add_files("src/d3object/*.c")
    add_files("src/d2object/*.c")
    add_files("src/user_object/*.c")
target_end()

-- Generate an installation package
xpack("lua-cad")
    set_version("1.1.2")
    set_formats("zip", "targz")
    set_title("Lua-cad($(arch)-$(host))")
    set_basename("Lua-cad-v$(version)-$(arch)-$(host)")
    set_homepage("https://github.com/SongZihui-sudo/lua-cad")
    set_author("SongZihui-sudo")
    set_maintainer("1751122876@qq.com")
    set_copyright("Copyright (C) 2024 lua-cad SongZihui-sudo")
    set_license("Gplv3")
    set_licensefile("./LICENSE.txt")
    add_installfiles ("src/user_object/user_obj.lua")
    add_installfiles ("src/chunk.lua")
    add_targets("lua-cad")

-- Unit tests
function test_base() 
    add_files("port/openscad/*.c")
    add_files("lua/*.c|onelua.c|lua.c")
    add_files("src/*.c|lua-cad.c|main.c")
    add_files("src/d3object/*.c")
    add_files("src/d2object/*.c")
    add_files("src/user_object/*.c")
    set_targetdir("tests/bin")
    set_kind("binary")
end

-- test circle
target("circle_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_circle.lua", plain = true, pass_outputs = {"circle(d = 10.000000);\ncircle(r = 10.000000);\n\n"}})
target_end()

-- test plolygon
target("plolygon_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_ploygon.lua", plain = true, pass_outputs = "polygon(points = [ [0.000000, 0.000000],[100.000000, 0.000000],[130.000000, 50.000000],[30.000000, 50.000000]], paths = [ [ 0,1,2,3],[ 2,3],[ 1]], convexity = 0);\n\n"})
target_end()

-- test square
target("square_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_square.lua", plain = true, pass_outputs = "square([10.000000, 10.000000], center = false);\nsquare([10.000000, 10.000000], center = true);\n\n"})
target_end()

-- test cube
target("cube_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_cube.lua", plain = true, pass_outputs = "cube([10.000000, 10.000000, 10.000000], center = false);\ncube([10.000000, 10.000000, 10.000000], center = true);\n\n"})
target_end()

-- test cylinder
target("cyliner_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_cylinder.lua", plain = true, pass_outputs = "cylinder(h = 1.000000, r = 10.000000,   center = true);\ncylinder(h = 1.000000, d = 10.000000,   center = false);\ncylinder(h = 1.000000, r1 = 10.000000, r2 center = true);\ncylinder(h = 1.000000, d1 = 10.000000, d2 center = false);\n\n"})
target_end()

-- test sphere
target("sphere_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_sphere.lua", plain = true, pass_outputs = "sphere(r = 10.000000);\nsphere(d = 20.000000);\n\n"})
target_end()

-- test polyhedron
target("polyhedron_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_polyhedron.lua", plain = true, pass_outputs = "polyhedron( points = [ [ 10.000000, 10.000000, 0.000000 ],[ 10.000000, -10.000000, 0.000000 ],[ -10.000000, -10.000000, 0.000000 ],[ -10.000000, 10.000000, 0.000000 ]], faces = [[ 0,1,4],[ 1,2,4],[ 2,3,4],[ 3,0,4],[ 1,0,3],[ 2,1,3]], convexity = 0);\n\n"})
target_end()

-- test user object
target("user_object_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_user_object.lua", plain = true, pass_outputs = "shoulder_screw( \"english\", 1/2, length = 20 );\n"})
target_end()

-- test datum
target("datum_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_datum.lua"})
target_end()

-- test transform
target("transform_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_transform.lua"})
target_end()

-- test chunk
target("chunk_test")
    test_base()
    add_files("tests/tests.c")
    add_tests("tests", {runargs = "../test_chunk.lua", trim_output = true })
target_end()