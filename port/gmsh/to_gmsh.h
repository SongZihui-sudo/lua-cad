/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-10 14:26:23
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
#include <lauxlib.h>
#include <lua.h>
#include <lua_table.h>

    void gmsh_save(lua_State* L);
    LUAMOD_API int luaopen_gmsh( lua_State* L );

#endif
#ifdef __cplusplus
}
#endif