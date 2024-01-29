#include <cylinder.h>
#include <to_code.h>

#include <stdlib.h>

static int cylinder_init( lua_State* L ) 
{ 
    unsigned int i_bytes = sizeof( cylinder );
    cylinder* temp = (cylinder*)malloc(sizeof(cylinder));
    // 读参数列表
    temp->base.m_center = lua_toboolean(L, 2);
    lua_pushstring(L, "h");
    lua_gettable(L, 1);
    temp->h = lua_tonumber(L, -1);
    lua_pushstring(L, "r");
    lua_gettable(L, 1);
    temp->r = lua_tonumber(L, -1);
    lua_pushstring(L, "r1");
    lua_gettable(L, 1);
    temp->r1 = lua_tonumber(L, -1);
    lua_pushstring(L, "r2");
    lua_gettable(L, 1);
    temp->r2 = lua_tonumber(L, -1);
    lua_pushstring(L, "d1");
    lua_gettable(L, 1);
    temp->d1 = lua_tonumber(L, -1);
    lua_pushstring(L, "d2");
    lua_gettable(L, 1);
    temp->d2 = lua_tonumber(L, -1);
    temp->base.m_offset          = dynast_cast( vec3, malloc( sizeof( vec3 ) ) );
    cylinder_to_code(L, temp);
    cylinder* current;
    current                         = dynast_cast( cylinder, lua_newuserdata( L, i_bytes ) );
    memcpy(current, temp, sizeof(cylinder));
    free(temp);
    return 1; 
}

vec3 calculate_vertices_cylinder( cylinder* self, unsigned short index )
{
    vec3 result;
    return result;
}

static const luaL_Reg cylinderlib[] = { { "new", cylinder_init }, { NULL, NULL } };

LUAMOD_API int luaopen_cylinder( lua_State* L )
{
    luaL_newlib( L, cylinderlib );
    return 1;
}
