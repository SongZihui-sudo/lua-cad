#include <sphere.h>
#include <to_openscad_code.h>

#include <stdlib.h>

int sphere_init( lua_State* L )
{
    char sphere_arg = ' ';
    double r_or_d = -1;
    lua_pushstring( L, "r" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        sphere_arg = 'r';
        r_or_d       = lua_tonumber( L, -1 );
    }
    lua_pushstring( L, "d" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        if ( r_or_d != -1 )
        {
            luaL_error( L, "r and d cannot be configured at the same time!" );
            return -1;
        }
        sphere_arg = 'd';
        r_or_d       = lua_tonumber( L, -1 );
    }
    unsigned int i_bytes = sizeof( sphere );
    sphere* current;
    current                         = dynast_cast( sphere, lua_newuserdata( L, i_bytes ) );
    sphere_obj_init(current);
    current->arg                    = sphere_arg;
    current->m_r_or_d               = r_or_d;
    current->base.m_obj_base.m_code = NULL;
    current->base.m_obj_base.m_type = SPHERE;
    return 1;
}

vec3 calculate_vertices_sphere( lua_State* L, sphere* self, unsigned short index )
{
    vec3 result;
    vec3_init(&result, 0);
    vec3 sides;
    sides.m_xyz[0] = self->m_r_or_d;
    scale( &sides, self->base.m_scale );
    pan( &result, self->base.m_offset );
    switch ( index )
    {
#define xx( case_num, xyz, op )                                                            \
    case case_num:                                                                         \
        result.m_xyz[xyz] op sides.m_xyz[0];                                               \
        break;
        xx( 1, 2, += ) // top
        xx( 2, 2, -= ) // bottom
        xx( 3, 1, -= ) // left
        xx( 4, 1, += ) // right
        xx( 5, 0, += ) // front
        xx( 6, 0, -= ) // back
#undef xx
        default : luaL_error( L, "Datum index out of bounds!" );
    }
    rotation( &result, self->base.m_rotate_a, self->base.m_rotate_v );
    return result;
}

static const luaL_Reg spherelib[] = { { "new", sphere_init }, { NULL, NULL } };
