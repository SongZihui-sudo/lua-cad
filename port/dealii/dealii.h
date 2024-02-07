/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-07 18:14:45
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-07 20:01:28
 * @FilePath: /lua-cad/port/dealii/dealii.h
 * @Description: 
 * 
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved. 
 */

#pragma once

#include <lua.h>
#include <obj_type.h>

#ifdef __cplusplus

extern "C"
{
#endif
    int dealii_render(OBJ_BASE* obj_base);
#ifdef __cplusplus
}

#endif