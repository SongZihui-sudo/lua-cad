/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-06 00:21:43
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 14:47:46
 * @FilePath: /lua-cad/src/d2object/circle.c
 * @Description:
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#include <circle.h>

int circle_init( lua_State* L )
{
    char flag;
    double value;
    // 读取半径或者直径
    lua_pushstring( L, "r" );
    lua_gettable(L, 1);
    if ( !lua_isnil( L, -1 ) )
    {
        flag  = 'r';
        value = lua_tonumber( L, -1 );
        goto finish;
    }
    lua_pop(L, 1);
    lua_pushstring( L, "d" );
    lua_gettable(L, 1);
    if ( !lua_isnil( L, -1 ) )
    {
        flag  = 'd';
        value = lua_tonumber( L, -1 );
    }
    lua_pop(L, 1);
finish:
    unsigned int i_bytes = sizeof( circle );
    circle* current;
    current                         = dynast_cast( circle, lua_newuserdata( L, i_bytes ) );
    current->base.m_obj_base.m_type = CIRCLE;
    current->m_r_d = flag;
    current->m_value = value;
    current->base.m_obj_base.m_code = NULL;
    D3OBJECT_BASE_INIT(&current->base);
    return 1;
}
