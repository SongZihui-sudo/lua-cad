#include <boolean.h>
#include <to_openscad_code.h>
#include <transform.h>

#include <stdlib.h>
#include <string.h>

char ROTATE_EXPORT_ARG1[64];
char ROTATE_EXPORT_ARG2[64];
char COLOR_EXPORT_ARG1[64];
char COLOR_EXPORT_ARG2[64];

void append_transform_openscad_code( lua_State* L, D3OBJECT_BASE* obj, enum TYPES type )
{
    D2OBJECT_BASE* self1;
    char temp[128];
    switch ( type )
    {
        case TRANSLATE:
            sprintf( temp,
                     TRANSLATE_EXPORT_RULE,
                     obj->m_offset.m_xyz[0],
                     obj->m_offset.m_xyz[1],
                     obj->m_offset.m_xyz[2] );
            break;
        case SCALE:
            sprintf( temp,
                     SCALE_EXPORT_RULE,
                     obj->m_scale.m_xyz[0],
                     obj->m_scale.m_xyz[1],
                     obj->m_scale.m_xyz[2] );
            break;
        case ROTATE:
            sprintf( temp, ROTATE_EXPORT_RULE, ROTATE_EXPORT_ARG1, ROTATE_EXPORT_ARG2 );
            break;
        case MIRROR:
            sprintf( temp,
                     MIRROR_EXPORT_RULE,
                     obj->m_mirror.m_xyz[0],
                     obj->m_mirror.m_xyz[1],
                     obj->m_mirror.m_xyz[2] );
            break;
        case COLOR:
            sprintf( temp, COLOR_EXPORT_RULE, COLOR_EXPORT_ARG1, COLOR_EXPORT_ARG2 );
            break;
        case LINEAR_EXTRUDE:
            self1 = dynast_cast( D2OBJECT_BASE, obj );
            sprintf( temp,
                     LINEAR_EXTRUDE_EXPORT_RULE,
                     self1->linear_extrude.height,
                     IS_CENTER( self1->m_center ),
                     self1->linear_extrude.convexity,
                     self1->linear_extrude.twist,
                     self1->linear_extrude.slices,
                     self1->linear_extrude.scale );
            break;
        case ROTATE_EXTRUDE:
            self1 = dynast_cast( D2OBJECT_BASE, obj );
            sprintf( temp,
                     ROTATE_EXTRUDE_EXPORT_RULE,
                     self1->rotate_extrude.angle,
                     self1->rotate_extrude.convexity );
            break;
        default:
            luaL_error( L, "Unknown transform type!" );
    }
    char* buffer
    = dynast_cast( char, malloc( sizeof( char ) * ( strlen( obj->m_obj_base.m_code ) + strlen( temp ) ) ) );
    sprintf( buffer, "%s%s", temp, obj->m_obj_base.m_code );
    strcpy( obj->m_obj_base.m_code, buffer );
    free( buffer );
}

int transform( lua_State* L, enum TYPES type, D3OBJECT_BASE* obj )
{
    // 读输入的参数
    const int count    = 3;
    const char* xyz[3] = { "x", "y", "z" };
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        double temp_num = lua_tonumber( L, -1 );
        if ( !temp_num )
        {
            lua_pop( L, 1 );
            lua_pushstring( L, xyz[i] );
            lua_gettable( L, 2 );
            temp_num = lua_tonumber( L, -1 );
        }
        switch ( type )
        {
            case TRANSLATE:
                obj->m_offset.m_xyz[i] = temp_num;
                break;
            case SCALE:
                obj->m_scale.m_xyz[i] = temp_num;
                break;
            case MIRROR:
                obj->m_mirror.m_xyz[i] = temp_num;
                break;
            default:
                luaL_error( L, "Unknown transform type!" );
        }
        lua_pop( L, 1 );
    }
    return 1;
}

int transform_postion( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error( L, "Object is null!" );
    }
    transform( L, TRANSLATE, current );
    current->m_op_stack[++current->m_op_stack[0]] = TRANSLATE;
    return 1;
}

int transform_scale( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error( L, "Object is null!" );
    }
    transform( L, SCALE, current );
    current->m_op_stack[++current->m_op_stack[0]] = SCALE;
    return 1;
}

int transform_rotate( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error( L, "Object is null!" );
    }
    // 读输入的参数
    const int count = 3;
    if ( lua_isnumber( L, 2 ) )
    {
        current->m_rotate_a.m_xyz[0] = luaL_checknumber( L, 2 );
        sprintf( ROTATE_EXPORT_ARG1, SINGLE_ARG_RULE1, "a ", current->m_rotate_a.m_xyz[0] );
        if ( !lua_istable( L, 3 ) )
        {
            ROTATE_EXPORT_ARG2[0] = '\0';
            goto finish;
        }
    }
    else
    {
        for ( int i = 0; i < count; i++ )
        {
            lua_pushnumber( L, i + 1 );
            lua_gettable( L, 2 );
            double temp_num              = lua_tonumber( L, -1 );
            current->m_rotate_a.m_xyz[i] = temp_num;
            lua_pop( L, 1 );
        }
        sprintf( ROTATE_EXPORT_ARG1,
                 "[ %f, %f, %f ]",
                 current->m_rotate_a.m_xyz[0],
                 current->m_rotate_a.m_xyz[1],
                 current->m_rotate_a.m_xyz[2] );
    }
    if ( !lua_isnil( L, 3 ) && lua_istable( L, 3 ) )
    {
        for ( int i = 0; i < count; i++ )
        {
            lua_pushnumber( L, i + 1 );
            lua_gettable( L, 3 );
            double temp_num              = lua_tonumber( L, -1 );
            current->m_rotate_v.m_xyz[i] = temp_num;
            lua_pop( L, 1 );
        }
        sprintf( ROTATE_EXPORT_ARG2,
                 ", v = [ %f, %f, %f ]",
                 current->m_rotate_v.m_xyz[0],
                 current->m_rotate_v.m_xyz[1],
                 current->m_rotate_v.m_xyz[2] );
    }
finish:
    current->m_op_stack[++current->m_op_stack[0]] = ROTATE;
    return 1;
}

int transform_mirror( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error( L, "Object is null!" );
    }
    transform( L, MIRROR, current );
    current->m_op_stack[++current->m_op_stack[0]] = MIRROR;
    return 1;
}

int color( lua_State* L )
{
    D3OBJECT_BASE* current = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !current )
    {
        luaL_error( L, "Object is null!" );
    }
    if ( lua_istable( L, 2 ) )
    {
        int count = luaL_len( L, 2 );
        if ( count > 4 )
        {
            luaL_error( L, "To many args in table!" );
        }
        for ( int i = 0; i < count; i++ )
        {
            lua_pushnumber( L, i + 1 );
            lua_gettable( L, 2 );
            double temp_num         = lua_tonumber( L, -1 );
            current->m_color_arr[i] = temp_num;
            lua_pop( L, 1 );
        }
        if ( count == 3 )
        {
            sprintf( COLOR_EXPORT_ARG1,
                     "[%f, %f, %f]",
                     current->m_color_arr[0],
                     current->m_color_arr[1],
                     current->m_color_arr[2] );
        }
        else
        {
            sprintf( COLOR_EXPORT_ARG1,
                     "[%f, %f, %f, %f]",
                     current->m_color_arr[0],
                     current->m_color_arr[1],
                     current->m_color_arr[2],
                     current->m_color_arr[3] );
            COLOR_EXPORT_ARG2[0] = '\0';
            goto finish;
        }
    }
    else if ( lua_isstring( L, 2 ) )
    {
        sprintf( current->m_color_str, "\"%s\"", lua_tostring( L, 2 ) );
        sprintf( COLOR_EXPORT_ARG1, "%s", current->m_color_str );
    }
    else
    {
        luaL_error( L, "Error Type! arg 2!" );
    }
    if ( lua_isnumber( L, 3 ) )
    {
        current->m_color_alpha = lua_tonumber( L, 3 );
        sprintf( COLOR_EXPORT_ARG2, SINGLE_ARG_RULE1, ", alpha", current->m_color_alpha );
    }
    else
    {
        COLOR_EXPORT_ARG2[0] = '\0';
    }
finish:
    current->m_op_stack[++current->m_op_stack[0]] = COLOR;
    return 1;
}

LUA_CAD_API get_translate_openscad_fmt( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        lua_pushstring( L, TRANSLATE_EXPORT_RULE );
    }
    else
    {
        lua_pushstring( L, "" );
    }
    return 1;
}

LUA_CAD_API get_mirror_openscad_fmt( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        lua_pushstring( L, MIRROR_EXPORT_RULE );
    }
    else
    {
        lua_pushstring( L, "" );
    }
    return 1;
}

LUA_CAD_API get_scale_openscad_fmt( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        lua_pushstring( L, SCALE_EXPORT_RULE );
    }
    else
    {
        lua_pushstring( L, "" );
    }
    return 1;
}

LUA_CAD_API get_rotate_openscad_fmt( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        lua_pushstring( L, ROTATE_EXPORT_RULE );
    }
    else
    {
        lua_pushstring( L, "" );
    }
    return 1;
}

LUA_CAD_API get_color_openscad_fmt( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        lua_pushstring( L, COLOR_EXPORT_RULE );
    }
    else
    {
        lua_pushstring( L, "" );
    }
    return 1;
}

static const luaL_Reg transformlib[] = { { "postion", transform_postion },
                                         { "scale", transform_scale },
                                         { "rotate", transform_rotate },
                                         { "mirror", transform_mirror },
                                         { "fill", fill },
                                         { "hull", hull },
                                         { "minkowski", minkowski },
                                         { "offset", offset },
                                         { "color", color },
                                         { "translate_fmt", get_translate_openscad_fmt },
                                         { "mirror_fmt", get_mirror_openscad_fmt },
                                         { "scale_fmt", get_scale_openscad_fmt },
                                         { "rotate_fmt", get_rotate_openscad_fmt },
                                         { "color_fmt", get_color_openscad_fmt },
                                         { NULL, NULL } };

LUAMOD_API int luaopen_transform( lua_State* L )
{
    luaL_newlib( L, transformlib );
    return 1;
}
