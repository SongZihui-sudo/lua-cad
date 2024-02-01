/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-31 19:31:05
 * @FilePath: /lua-cad/src/base_object/cube.c
 * @Description: 立方体对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <cube.h>
#include <stdlib.h>
#include <string.h>
#include <to_openscad_code.h>
#include <vec3.h>

int cube_init( lua_State* L )
{
    // 读输入的参数
    const int count = 3;
    vec3 temp_vec;
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        double temp_num   = lua_tonumber( L, -1 );
        temp_vec.m_xyz[i] = temp_num;
        lua_pop( L, 1 );
    }
    bool is_center = lua_toboolean( L, 2 );
    // 创建一个立方体对象
    unsigned int i_bytes = sizeof( cube );
    cube* current;
    current = dynast_cast( cube, lua_newuserdata( L, i_bytes ) );
    cube_obj_init( current );
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
    vec3_init(&result, 0);
    vec3 sides = self->m_w_l_h;
    scale( &sides, self->base.m_scale );
    pan( &result, self->base.m_offset );
    if ( self->base.m_center )
    {
        switch ( index )
        {
#define xx( case_num, op, xyz )                                                            \
    case case_num:                                                                         \
        result.m_xyz[xyz] op sides.m_xyz[xyz] / 2;                                         \
        break;
            xx( 1, +=, 2 ) // 顶
            xx( 2, -=, 2 ) // 底
            xx( 3, -=, 1 ) // 左
            xx( 4, +=, 1 ) // 右
            xx( 5, +=, 0 ) // 前
            xx( 6, -=, 0 ) // 后
#undef xx
            default : luaL_error( L, "Datum index out of bounds!" );
        }
    }
    else
    {
        switch ( index )
        {
#define xx( case_num, xyz1, xyz2 )                                                         \
    case case_num:                                                                         \
        result.m_xyz[xyz1] += sides.m_xyz[xyz1] / 2;                                       \
        result.m_xyz[xyz2] += sides.m_xyz[xyz2] / 2;
            xx( 1, 0, 1 ) result.m_xyz[2] += sides.m_xyz[2];
            break;               // 顶
            xx( 2, 0, 1 ) break; // 底
            xx( 3, 0, 2 ) break; // 左
            xx( 4, 0, 2 ) result.m_xyz[1] += sides.m_xyz[1];
            break; // 右
            xx( 5, 1, 2 ) result.m_xyz[0] += sides.m_xyz[0];
            break;               // 前
            xx( 6, 1, 2 ) break; // 后
#undef xx
            default:
                luaL_error( L, "Datum index out of bounds!" );
        }
    }
    rotation( &result, self->base.m_rotate_a, self->base.m_rotate_v );
    return result;
}
