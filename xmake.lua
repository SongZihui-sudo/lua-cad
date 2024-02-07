includes("@builtin/xpack")

add_rules("mode.debug", "mode.release")

add_includedirs("./lua")
add_includedirs("./src")
add_includedirs("./src/d2object")
add_includedirs("./src/d3object")
add_includedirs("./src/user_object")
add_includedirs("./port/openscad")
add_includedirs("./port/dealii")
add_includedirs("/home/songzihui/dealii-9.5.2/dealii_lib/include/")

target("lua-cad")
    before_build(function (target) 
        function get_subdirectories(root_path)
            local dirs = {}
            local i = 0;
            for _, dir in ipairs(os.dirs(root_path)) do
                print("[%d] Add include dir: " .. dir, i)
                table.insert(dirs, dir);
                i = i + 1
            end
            target:add("includedirs", dirs);
        end
        -- 要添加头文件目录的文件夹路径
        local folder_path = "/home/songzihui/dealii-9.5.2/dealii_lib/include/**"
        -- 获取所有子目录
        get_subdirectories(folder_path)        
    end)
    add_linkdirs("/home/songzihui/dealii-9.5.2/dealii_lib/lib/")
    add_links("libdeal_II.so")
    set_kind("binary")
    add_files("port/openscad/*.c")
    add_files("lua/*.c|onelua.c|lua.c")
    add_files("src/*.c|lua-cad.c")
    add_files("src/d3object/*.c")
    add_files("src/d2object/*.c")
    add_files("src/user_object/*.c")
    add_files("port/dealii/*.cpp")
target_end()

-- 生成安装包
xpack("lua-cad")
    set_version("1.0.1")
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
    add_installfiles ("src/lua_class/class.lua")
    add_targets("lua-cad")

