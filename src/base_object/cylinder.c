#include <cylinder.h>
#include <to_openscad_code.h>

#include <stdlib.h>

const char* CYLINDER_ARG1;
const char* CYLINDER_ARG2;

int cylinder_init( lua_State* L )
{
    cylinder* temp = ( cylinder* )malloc( sizeof( cylinder ) );
    cylinder_obj_init( temp );
    // 读参数列表
    temp->base.m_center = lua_toboolean( L, 2 );
    lua_pushstring( L, "h" );
    lua_gettable( L, 1 );
    temp->m_h = luaL_checknumber( L, -1 );
    lua_pushstring( L, "r" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        CYLINDER_ARG1 = "r";
        CYLINDER_ARG2 = "";
        temp->m_r_d_1 = lua_tonumber( L, -1 );
        goto finish;
    }
    lua_pushstring( L, "d" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        CYLINDER_ARG1 = "d";
        CYLINDER_ARG2 = "";
        if ( temp->m_r_d_1 != -1 )
        {
            luaL_error( L, "r or d cannot be configured at the same time!" );
        }
        temp->m_r_d_1 = lua_tonumber( L, -1 ) / 2;
        goto finish;
    }
    lua_pushstring( L, "d1" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        CYLINDER_ARG1 = "d1";
        temp->m_r_d_1 = lua_tonumber( L, -1 ) / 2;
    }
    lua_pushstring( L, "d2" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        char buf[32];
        temp->m_r_d_2 = lua_tonumber( L, -1 );
        sprintf( buf, SINGLE_ARG_RULE1, "d2", temp->m_r_d_2 );
        temp->m_r_d_2 = temp->m_r_d_2 / 2;
        CYLINDER_ARG2 = buf;
        if ( temp->m_r_d_1 != -1 )
        {
            goto finish;
        }
    }
    else if ( temp->m_r_d_1 != -1 )
    {
        luaL_error( L, "d2 cannot be empty!" );
    }
    lua_pushstring( L, "r1" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        if ( temp->m_r_d_1 != -1 || temp->m_r_d_2 != -1 )
        {
            luaL_error( L, "r1 or d1 cannot be configured at the same time!" );
        }
        CYLINDER_ARG1 = "r1";
        temp->m_r_d_1 = lua_tonumber( L, -1 );
    }
    lua_pushstring( L, "r2" );
    lua_gettable( L, 1 );
    if ( !lua_isnil( L, -1 ) )
    {
        if ( temp->m_r_d_2 != -1 )
        {
            luaL_error( L, "r2 or d2 cannot be configured at the same time!" );
        }
        char buf[32];
        temp->m_r_d_2 = lua_tonumber( L, -1 );
        sprintf( buf, SINGLE_ARG_RULE1, "r2", temp->m_r_d_2 );
        CYLINDER_ARG2 = buf;
        if ( temp->m_r_d_1 != -1 )
        {
            goto finish;
        }
    }
finish:
    temp->base.m_obj_base.m_code = NULL;
    temp->base.m_obj_base.m_type = CYLINDER;
    unsigned int i_bytes = sizeof( cylinder );
    cylinder* current;
    current = dynast_cast( cylinder, lua_newuserdata( L, i_bytes ) );
    memcpy( current, temp, sizeof( cylinder ) );
    current->base.m_obj_base.m_type = CYLINDER;
    free( temp );
    return 1;
}

vec3 calculate_vertices_cylinder( lua_State* L, cylinder* self, unsigned short index )
{
    vec3 result;
    vec3_init(&result, 0);
    vec3 sides;
    sides.m_xyz[0] = self->m_h;
    sides.m_xyz[1] = self->m_r_d_1;
    sides.m_xyz[2] = self->m_r_d_2;
    scale( &sides, self->base.m_scale );
    pan( &result, self->base.m_offset );
    if ( self->base.m_center )
    {
        switch ( index )
        {
#define xx( case_num, op, xyz )                                                            \
    case case_num:                                                                         \
        result.m_xyz[xyz] += self->m_h / 2;                                                \
        break;
            xx( 1, +=, 2 ); // 顶
            xx( 2, -=, 2 ); // 底
#undef xx
            default:
                luaL_error( L, "Datum index out of bounds!" );
        }
    }
    else
    {
#define xx( xyz1, xyz2, xyz3 )                                                             \
    result.m_xyz[xyz1] += sides.m_xyz[xyz3];                                               \
    result.m_xyz[xyz2] += sides.m_xyz[xyz3];
        if ( self->m_r_d_2 > 0 )
        {
            xx( 0, 1, 1 )
        }
        else
        {
            xx( 0, 1, 2 )
        }
#undef xx
        switch ( index )
        {
            // 顶
            case 1:
                result.m_xyz[2] += sides.m_xyz[0];
                break;
            // 底
            case 2:
                break;
            default:
                luaL_error( L, "Datum index out of bounds!" );
        }
    }
    rotation( &result, self->base.m_rotate_a, self->base.m_rotate_v );
    return result;
}
