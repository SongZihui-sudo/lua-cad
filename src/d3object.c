#include <d3object.h>

#include <cube.h>
#include <cylinder.h>
#include <polyhedron.h>
#include <sphere.h>

static const luaL_Reg d3objectlib[] = { { "cube", cube_init },
                                        { "cylinder", cylinder_init },
                                        { "sphere", sphere_init },
                                        { "polyhedron", polyhedron_init },
                                        { NULL, NULL } };

LUAMOD_API int luaopen_d3object( lua_State* L )
{
    luaL_newlib( L, d3objectlib );
    return 1;
}
