/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-05 23:40:53
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 14:22:49
 * @FilePath: /lua-cad/src/d2object.c
 * @Description:
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#include <circle.h>
#include <lauxlib.h>
#include <polygon.h>
#include <square.h>

void get_field_table(lua_State* L, double* value, const char* field, short index)
{
    lua_pushstring( L, field );
    lua_gettable(L, index);
    if ( !lua_isnil( L, -1 ) )
    {
        *value = lua_tonumber( L, -1 );
    }
    else
    {
        luaL_error( L, "%s Field is Null!", field );
    }
    lua_pop(L, 1);
}

/**
 * @description: Linear Extrusion is an operation that takes a 2D object as input and generates a 3D object as a result.
 * @param {lua_State*} L
 * @return {*}
 */
static int transform_linear_extrude( lua_State* L )
{
    // d2object
    D2OBJECT_BASE* current = lua_touserdata( L, 1 );
    // 读 height
    get_field_table(L, &current->linear_extrude.height, "height", 2);
    // 读 center
    lua_pushstring( L, "center" );
    lua_gettable(L, 2);
    if ( !lua_isnil( L, -1 ) )
    {
        current->linear_extrude.center = lua_toboolean( L, -1 );
    }
    else
    {
        current->linear_extrude.center = false;
        luaL_error( L, "%s Field is Null!", "center" );
    }
    lua_pop(L, 1);
    // 读 convexity
    get_field_table(L, &current->linear_extrude.convexity, "convexity", 2);
    get_field_table(L, &current->linear_extrude.twist, "twist", 2);
    get_field_table(L, &current->linear_extrude.scale, "scale", 2);
    get_field_table(L, &current->linear_extrude.slices, "slices", 2);
    current->m_op_stack[++current->m_op_stack[0]] = LINEAR_EXTRUDE;
    return 1;
}

/**
 * @description: Rotational extrusion spins a 2D shape around the Z-axis to form a solid which has rotational symmetry.
 * @param {lua_State*} L
 * @return {*}
 */
static int transform_rotate_extrude( lua_State* L ) 
{
    // d2object
    D2OBJECT_BASE* current = lua_touserdata( L, 1 );
    get_field_table(L, &current->rotate_extrude.angle, "angle", 2);
    get_field_table(L, &current->rotate_extrude.convexity, "convexity", 2);
    current->m_op_stack[++current->m_op_stack[0]] = ROTATE_EXTRUDE;
    return 1;
}

static const luaL_Reg d2objectlib[] = { { "square", square_init },
                                        { "circle", circle_init },
                                        { "polygon", polygon_init },
                                        { "linear_extrude", transform_linear_extrude },
                                        { "rotate_extrude", transform_rotate_extrude },
                                        { NULL, NULL } };

LUAMOD_API int luaopen_d2object( lua_State* L )
{
    luaL_newlib( L, d2objectlib );
    return 1;
}
