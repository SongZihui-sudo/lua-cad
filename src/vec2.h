/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-05 23:49:41
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-05 23:51:06
 * @FilePath: /lua-cad/src/vec2.h
 * @Description: vector 2d
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

typedef struct vec2
{
    double m_xy[2];
} vec2;

static void vec2_init(vec2* self, int c)
{
    self->m_xy[0] = c;
    self->m_xy[1] = c;
}
