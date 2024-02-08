/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-08 23:40:47
 * @FilePath: /lua-cad/port/gmsh/gmsh.c
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <gmsh.h>
#include <lua_table.h>

#include <stdlib.h>

char* get_obj_table_gmsh_code( lua_State* L )
{
    int index = get_table_field_int_value( L, "index", 1 );
    double x  = get_table_field_int_value( L, "x", 1 );
    double y  = get_table_field_int_value( L, "y", 1 );
    double z  = get_table_field_int_value( L, "z", 1 );
    double lc = get_table_field_int_value( L, "lc", 1 );
    char* result = (char*)malloc(sizeof(char) * 64);
    if ( lc != -1 )
    {
        sprintf( result, POINT_EXPORT_RULE1, index, x, y, z, lc );
    }
    else
    {
        sprintf( result, POINT_EXPORT_RULE2, index, x, y, z );
    }
    return result;
}

void obj_to_gmsh_code( lua_State* L, D3OBJECT_BASE* obj )
{
    switch ( obj->m_obj_base.m_type )
    {
        case CUBE:
            break;
        case CYLINDER:
            break;
        case SPHERE:
            break;
        case POLYHEDRON:
            break;
        default:
            luaL_error( L, "Unsupported 3d object type!" );
    }
}

void boolean_to_gmsh_code( lua_State* L, D3OBJECT_BASE* obj ) {}