#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>
#include <cube.h>
#include <cylinder.h>
#include <polyhedron.h>
#include <sphere.h>
#include <datum.h>

int d3object_datum( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    unsigned short index   = luaL_checkinteger( L, 2 );
    vec3 point;
    switch ( current->m_obj_base.m_type )
    {
        case CUBE:
            point = calculate_vertices_cube( L, dynast_cast( cube, current ), index );
            break;
        case CYLINDER:
            point = calculate_vertices_cylinder( L, dynast_cast( cylinder, current ), index );
            break;
        case SPHERE:
            point = calculate_vertices_sphere( L, dynast_cast( sphere, current ), index );
            break;
        case POLYHEDRON:
            point = calculate_vertices_polyhedron( L, dynast_cast( polyhedron, current ), index );
            break;
        default:
            luaL_error( L, "Unkown Object Type!" );
    }
    // 创建一个基准对象
    unsigned int i_bytes = sizeof( datum );
    datum* current_datum;
    current_datum                         = dynast_cast( datum, lua_newuserdata( L, i_bytes ) );
    current_datum->m_center = point;
    return 1;
}

static const luaL_Reg d3objectlib[]
= { { "cube", cube_init },       { "cylinder", cylinder_init },
    { "sphere", sphere_init },   { "polyhedron", polyhedron_init },
    { "datum", d3object_datum }, { NULL, NULL } };

LUAMOD_API int luaopen_d3object( lua_State* L )
{
    luaL_newlib( L, d3objectlib );
    return 1;
}
