add_rules("mode.debug", "mode.release")

add_includedirs("./lua")
add_includedirs("./src")
add_includedirs("./to_code")

target("lua-cad")
    set_kind("binary")
    add_files("to_code/*.c")
    add_files("lua/*.c|onelua.c|lua.c")
    add_files("src/*.c|lua-cad.c")
target_end()
