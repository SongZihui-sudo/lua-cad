/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-06 00:44:59
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 11:23:26
 * @FilePath: /lua-cad/src/d2object/polygon.c
 * @Description:
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#include <polygon.h>
#include <to_openscad_code.h>

char POLYGON_ARG1[200];
char POLYGON_ARG2[200];

int polygon_init( lua_State* L )
{
    // 读 points 表
    vec2 points[64];
    POLYGON_ARG1[0]        = ' ';
    POLYGON_ARG2[0]        = ' ';
    const int points_count = luaL_len( L, 1 );
    for ( int i = 0; i < points_count; i++ )
    {
        char buffer[100];
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        vec2 temp;
        const int counter = luaL_len( L, -1 );
        for ( int j = 0; j < counter; j++ )
        {
            lua_pushnumber( L, j + 1 );
            lua_gettable( L, -2 );
            temp.m_xy[j] = lua_tonumber( L, -1 );
            lua_pop( L, 1 );
        }
        points[i] = temp;
        sprintf( buffer, POINT2_RULE, temp.m_xy[0], temp.m_xy[1] );
        strcat( POLYGON_ARG1, buffer );
        POLYGON_ARG1[strlen( POLYGON_ARG1 )] = ',';
        lua_pop( L, 1 );
    }
    POLYGON_ARG1[strlen( POLYGON_ARG1 ) - 1] = '\0';
    // 读 paths 表
    int* paths[64];
    const int paths_count = luaL_len( L, 2 );
    int counter;
    int total_paths_size = 0;
    for ( int i = 0; i < paths_count; i++ )
    {
        char buffer[100];
        buffer[0] = '[';
        buffer[1] = ' ';
        buffer[2] = '\0';
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        counter  = luaL_len( L, -1 );
        paths[i] = dynast_cast( int, malloc( sizeof( int ) * counter ) );
        total_paths_size += counter;
        for ( int j = 0; j < counter; j++ )
        {
            char buffer2[100];
            buffer2[0] = '\0';
            lua_pushnumber( L, j + 1 );
            lua_gettable( L, -2 );
            paths[i][j] = lua_tointeger( L, -1 );
            sprintf( buffer2, "%s%d,", buffer, paths[i][j] );
            strcpy( buffer, buffer2 );
            lua_pop( L, 1 );
        }
        buffer[strlen( buffer ) - 1] = ']';
        strcat( POLYGON_ARG2, buffer );
        POLYGON_ARG2[strlen( POLYGON_ARG2 )] = ',';
        memset( buffer, 0, strlen( buffer ) );
        lua_pop( L, 1 );
    }
    POLYGON_ARG2[strlen( POLYGON_ARG2 ) - 1] = '\0';
    // 创建一个多边形对象
    unsigned int i_bytes = sizeof( polygon );
    polygon* current;
    current = dynast_cast( polygon, lua_newuserdata( L, i_bytes ) );
    D3OBJECT_BASE_INIT( &current->base );
    current->m_convexity = lua_tonumber(L, 3);
    memcpy( current->m_paths, paths, sizeof( int ) * total_paths_size );
    current->m_paths_count  = paths_count;
    memcpy( current->m_points, points, sizeof( vec3 ) * points_count );
    current->m_points_count = points_count;
    current->base.m_obj_base.m_type = POLYGON;
    current->base.m_obj_base.m_code = NULL;
    return 1;
}
