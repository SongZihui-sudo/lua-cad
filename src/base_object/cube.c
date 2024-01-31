/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-31 12:12:40
 * @FilePath: /lua-cad/src/base_object/cube.c
 * @Description: 立方体对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <cube.h>
#include <stdlib.h>
#include <string.h>
#include <to_code.h>
#include <vec3.h>

int cube_init( lua_State* L )
{
    // 读输入的参数
    const int count = 3;
    vec3* temp_vec  = dynast_cast( vec3, malloc( sizeof( vec3 ) ) );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        double temp_num    = lua_tonumber( L, -1 );
        temp_vec->m_xyz[i] = temp_num;
        lua_pop( L, 1 );
    }
    bool is_center = lua_toboolean( L, 2 );
    // 创建一个立方体对象
    unsigned int i_bytes = sizeof( cube );
    cube* current;
    current                         = dynast_cast( cube, lua_newuserdata( L, i_bytes ) );
    current->base.m_obj_base.m_type = CUBE;
    current->m_w_l_h                = temp_vec;
    current->base.m_center          = is_center;
    current->base.m_obj_base.m_code = NULL;
    cube_to_code( L, current );
    return 1;
}

vec3 calculate_vertices_cube( lua_State* L, cube* self, unsigned short index )
{
    vec3 result;
    vec3* sides = self->m_w_l_h;
    scale(sides, self->base.m_scale);
    pan(&result, self->base.m_offset);
    if ( self->base.m_center )
    {
        switch ( index )
        {
            // 顶
            case 1:
                result.m_xyz[2] += sides->m_xyz[2] / 2; // z
                break;
            // 底
            case 2:
                result.m_xyz[2] -= sides->m_xyz[2] / 2; // z
                break;
            // 左
            case 3:
                result.m_xyz[1] -= sides->m_xyz[1] / 2; // y
                break;
            // 右
            case 4:
                result.m_xyz[1] += sides->m_xyz[1] / 2; // y
                break;
            // 前
            case 5:
                result.m_xyz[0] += sides->m_xyz[0] / 2; // x
                break;
            // 后
            case 6:
                result.m_xyz[0] -= sides->m_xyz[0] / 2; // x
                break;
            default:
                luaL_error(L, "Datum index out of bounds!");
                break;
        }
    }
    else
    {
        switch ( index )
        {
            // 顶
            case 1:
                result.m_xyz[0] += sides->m_xyz[0] / 2; // x
                result.m_xyz[1] += sides->m_xyz[1] / 2; // y
                result.m_xyz[2] += sides->m_xyz[2];     // z
                break;
            // 底
            case 2:
                result.m_xyz[0] += sides->m_xyz[0] / 2; // x
                result.m_xyz[1] += sides->m_xyz[1] / 2; // y
                break;
            // 左
            case 3:
                result.m_xyz[0] += sides->m_xyz[0] / 2; // x
                result.m_xyz[2] += sides->m_xyz[2] / 2; // z
                break;
            // 右
            case 4:
                result.m_xyz[0] += sides->m_xyz[0] / 2 ; // x
                result.m_xyz[1] += sides->m_xyz[1];     // y
                result.m_xyz[2] += sides->m_xyz[2] / 2; // z
                break;
            // 前
            case 5:
                result.m_xyz[0] += sides->m_xyz[0];     // x
                result.m_xyz[1] += sides->m_xyz[1] / 2; // y
                result.m_xyz[2] += sides->m_xyz[2] / 2; // z
                break;
            // 后
            case 6:
                result.m_xyz[1] += sides->m_xyz[1] / 2; // y
                result.m_xyz[2] += sides->m_xyz[2] / 2; // z
                break;
            default:
                luaL_error(L, "Datum index out of bounds!");
                break;
        }
    }
    rotation(&result, self->base.m_rotate_a, self->base.m_rotate_v);
    return result;
}
