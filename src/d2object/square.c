/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-05 23:46:37
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 00:42:03
 * @FilePath: /lua-cad/src/d2object/square.c
 * @Description: square object
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#include <square.h>

int square_init( lua_State* L )
{
    vec2 read_buf;
    vec2_init( &read_buf, 0 );
    const int count = luaL_len( L, 1 );
    if ( count > 2 )
    {
        luaL_error( L, "Too many args" );
    }
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        double temp      = lua_tonumber( L, -1 );
        read_buf.m_xy[i] = temp;
        lua_pop( L, 1 );
    }
    bool is_center       = lua_toboolean( L, 2 );
    unsigned int i_bytes = sizeof( square );
    square* current;
    current                         = dynast_cast( square, lua_newuserdata( L, i_bytes ) );
    current->w_l                    = read_buf;
    current->base.m_center          = is_center;
    current->base.m_obj_base.m_code = NULL;
    current->base.m_obj_base.m_type = SQUARE;
    return 1;
}
