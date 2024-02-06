/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-05 14:11:27
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-05 23:48:25
 * @FilePath: /lua-cad/src/datum.c
 * @Description: 
 * 
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved. 
 */


#include <datum.h>
#include <obj_type.h>

#include <math.h>
#include <string.h>

int relative_position( lua_State* L )
{
    datum* src = dynast_cast( datum, lua_touserdata( L, 1 ) );
    if ( !src )
    {
        luaL_error( L, "Object is null!" );
    }
    const char* direction = lua_tostring( L, 2 );
    double offset         = luaL_checknumber( L, 3 );
    // 返回一个基准对象
    unsigned int i_bytes = sizeof( datum );
    datum* current;
    current                    = dynast_cast( datum, lua_newuserdata( L, i_bytes ) );
    current->m_center.m_xyz[0] = src->m_center.m_xyz[0];
    current->m_center.m_xyz[1] = src->m_center.m_xyz[1];
    current->m_center.m_xyz[2] = src->m_center.m_xyz[2];
    if ( !strcmp( direction, "x" ) )
    {
        current->m_center.m_xyz[0] = src->m_center.m_xyz[0] + offset;
    }
    else if ( !strcmp( direction, "y" ) )
    {
        current->m_center.m_xyz[1] = src->m_center.m_xyz[1] + offset;
    }
    else if ( !strcmp( direction, "z" ) )
    {
        current->m_center.m_xyz[2] = src->m_center.m_xyz[2] + offset;
    }
    else
    {
        luaL_error( L, "Unknown direction %s !  --> x ,y ,z", direction );
    }
    return 1;
}

int distance_to_datum( lua_State* L )
{
    datum* current = dynast_cast( datum, lua_touserdata( L, 1 ) );
    vec3 temp;
    const int count = luaL_len( L, 2 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber(L, i + 1);
        lua_gettable(L, 2);
        temp.m_xyz[i] = lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    double dis = distance(temp, current->m_center);
    lua_pushnumber(L, dis);
    return 1;
}

int angle_to_datum( lua_State* L )
{
    datum* current = dynast_cast( datum, lua_touserdata( L, 1 ) );
    vec3 temp;
    const int count = luaL_len( L, 2 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber(L, i + 1);
        lua_gettable(L, 2);
        temp.m_xyz[i] = lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    double ang = angle(temp, current->m_center);
    lua_pushnumber(L, ang);
    return 1;
}

static int to_table( lua_State* L )
{
    datum* currnet = dynast_cast( datum, lua_touserdata( L, 1 ) );
    if ( !currnet )
    {
        luaL_error( L, "Object is null!" );
    }
    lua_newtable( L );
    lua_pushstring( L, "x" );
    lua_pushnumber( L, currnet->m_center.m_xyz[0] );
    lua_settable( L, -3 );
    lua_pushstring( L, "y" );
    lua_pushnumber( L, currnet->m_center.m_xyz[1] );
    lua_settable( L, -3 );
    lua_pushstring( L, "z" );
    lua_pushnumber( L, currnet->m_center.m_xyz[2] );
    lua_settable( L, -3 );
    return 1;
}

static const luaL_Reg datumlib[] = { { "relative", relative_position },
                                     { "distance", distance_to_datum },
                                     { "angle", angle_to_datum },
                                     { "to_table", to_table },
                                     { NULL, NULL } };

LUAMOD_API int luaopen_datum( lua_State* L )
{
    luaL_newlib( L, datumlib );
    return 1;
}
