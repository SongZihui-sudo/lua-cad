/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-07 13:36:40
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-07 13:41:53
 * @FilePath: /lua-cad/src/obj_type.c
 * @Description: object type define
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#include <obj_type.h>

bool is_boolean( OBJ_TYPE type )
{
    if ( type < BOOLEAN_END && type > BOOLEAN_BEGIN )
    {
        return true;
    }
    return false;
}

bool is_d3object( OBJ_TYPE type )
{
    if ( type > D3OBJECT_BEGIN && type < D3OBJECT_END )
    {
        return true;
    }
    return false;
}

bool is_d2object( OBJ_TYPE type )
{
    if ( type > D2OBJECT_BEGIN && type < D2OBJECT_END )
    {
        return true;
    }
    return false;
}

bool is_transform( OBJ_TYPE type )
{
    if ( type > TRANSFORM_BEGIN && type < TRANSFORM_END )
    {
        return true;
    }
    return false;
}

bool is_user_obj( OBJ_TYPE type )
{
    if ( type == USER_DEFINE )
    {
        return true;
    }
    return false;
}
