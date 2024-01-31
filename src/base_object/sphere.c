#include <sphere.h>
#include <to_code.h>

#include <stdlib.h>

const char* SPHERER_ARG1;

int sphere_init(lua_State* L)
{
    double r_or_d = -1;
    lua_pushstring(L, "r");
    lua_gettable(L, 1);
    if (!lua_isnil(L, -1)) {
        SPHERER_ARG1 = "r";
        r_or_d = lua_tonumber(L, -1);
    }
    lua_pushstring(L, "d");
    lua_gettable(L, 1);
    if (!lua_isnil(L, -1)) {
        if (r_or_d != -1) {
            luaL_error(L, "r and d cannot be configured at the same time!");
            return -1;
        }
        SPHERER_ARG1 = "d";
        r_or_d = lua_tonumber(L, -1);
    }
    unsigned int i_bytes = sizeof( sphere );
    sphere* current;
    current                         = dynast_cast( sphere, lua_newuserdata( L, i_bytes ) );
    current->base.m_center = lua_toboolean(L, 2);
    current->m_r_or_d = r_or_d;
    current->base.m_obj_base.m_code = NULL;
    current->base.m_obj_base.m_type = SPHERE;
    sphere_to_code(L, current);
    return 1;
}

vec3 calculate_vertices_sphere( lua_State* L, sphere* self, unsigned short index )
{
    vec3 result;
    vec3 sides;
    sides.m_xyz[0] = self->m_r_or_d;
    scale( &sides, self->base.m_scale );
    pan( &result, self->base.m_offset );
    TODO完成球体基准面的计算:
    if(self->base.m_center)
    {

    }
    else {
    
    }
    rotation(&result, self->base.m_rotate_a, self->base.m_rotate_v);
    return result;
}

static const luaL_Reg spherelib[] = { { "new", sphere_init }, { NULL, NULL } };
