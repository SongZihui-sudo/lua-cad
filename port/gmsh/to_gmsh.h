/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-10 21:52:45
 * @FilePath: /lua-cad/port/gmsh/to_gmsh.h
 * @Description:
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <obj_type.h>

enum GMSH_CURVE
{
    GMSH_SPLINE = 0,
    GMSH_BSPLINE,
    GMSH_BEZIER,
    GMSH_POLYLINE,
    GMSH_COMPOUNDSPLINE,
    GMSH_CONPOUNDBSPLINE,
    GMSH_CURVELOOPS,
    GMSH_PLANESURFACE,
    GMSH_SURFACELOOP,
    GMSH_VOLUME,
    GMSH_CURVELOOP
};

#ifdef __cplusplus

extern "C"
{
#endif
#include <lauxlib.h>
#include <lua.h>
#include <lua_table.h>
#include <square.h>

    void object_to_gmsh( lua_State* L );
    void square_to_gmsh( square* obj );
    void d2object_to_gmsh( D2OBJECT_BASE* obj );
     void d3object_to_gmsh( D3OBJECT_BASE* obj );
    void gmsh_save( lua_State* L );
    LUAMOD_API int luaopen_gmsh( lua_State* L );

#ifdef __cplusplus
}
#endif